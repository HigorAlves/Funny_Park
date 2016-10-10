#include "geral.h"

posCar saveCar[18]; //Salva o carro, eixo de inserção, cood x,y.
int qnt = 0;
int menor_sequencia = 541;

void pega_flag(int argc, char **argv, char parg[100], char earg[100], int *h, int *b, int *v){
    int verbose;
    opterr = 0;

    while((verbose = getopt(argc,argv,"v:m:HBV")) != -1){
        switch(verbose){
        case 'v':
            strcpy(parg,optarg);
            break;
        case 'm':
            strcpy(earg,optarg);
            break;
        case 'H':
            *h = 1;
            break;
        case 'B':
            *b = 1;
            break;
        case 'V':
            *v = 1;
            break;
        case '?':
            if (optopt == 'v'){
                printf("Opcao \"%c\" falta de argumentos!\n", optopt);
            }
            else if( optopt == 'm' ){
                printf("Opcao \"%c\" falta de argumentos!\n", optopt);
            }else{
                printf("Opcao \"%c\" opção desconhecida!\n",optopt);
            }
            return;
        }
    }
    
}

/*-----VERIFICADORES------*/
int verifyCar(char nome){
    /*Verificamos se o carro existe*/
    int i;

    for(i = 0; i < qnt; i++){
        if(nome == saveCar[i].nome){
            return i;
        }
    }
    return -1;
}

void addCar(char nome, int id, char eixo, int x, int y){
    /*Adicionamos um carro na lista*/
    saveCar[qnt].id = id;
    saveCar[qnt].nome = nome;
    saveCar[qnt].x = x;
    saveCar[qnt].y = y;
    saveCar[qnt].eixo = eixo;
    qnt++;
}

void insert_veiculo(char matriz[6][6],char nome, int id, char eixo, int x, int y){
    /*Coloca o carro na matriz estacionamento*/
    x --;
    y = 6 - y;
    int A,B;

    if(verifyCar(nome) != -1){
        printf("O carro existe! (%c %d %c X%dY%d)\n",nome,id,eixo,x+1,6-y);
        return;
    }

    /*Se for inserir no eixo X*/
    if(eixo == 'X' || eixo == 'x'){
        eixo = 'X';
        A = matriz[y][x] == padrao && matriz[y][x+1] == padrao;
        B = matriz[y][x+2] == padrao;

        if(((id == 2) && (x>=0) && (x<5) && (y>=0) && (y<=5)) || ((id == 3) && (x>=0) && (x<4) && (y>=0) && (y<=5))){  //Se não extrapolar os limites do estacionamento:
            if((A && B) || (!(id == 3) && A)){  //Se não houver nenuma colisão insira.
                matriz[y][x] = nome;
                matriz[y][x+1] = nome;
                if(id == 3)matriz[y][x+2] = nome;
            }else{
                printf("Carro sobreposto: %c %d %c X%dY%d\n",nome,id,eixo,x+1,6-y);
                return;
            }
        }else{
            printf("Limite do estacionamento: %c %d %c X%dY%d\n",nome,id,eixo,x+1,6-y);
            return;
        }
    }else if(eixo=='Y' || eixo=='y'){
        eixo = 'Y';
        A = matriz[y][x] == padrao && matriz[y-1][x] == padrao;
        B = matriz[y-2][x] == padrao;
        
        /*Caso estrapole os limites do estacionamento*/
        if(((id == 2) && (x>=0) && (x<=5) && (y>0) && (y<=5)) || ((id == 3) && (x>=0) && (x<=5) && (y>1) && (y<=5))){
            /*Caso não haja colisões*/
            if((A && B) || (!(id == 3) && A)){
                matriz[y][x] = nome;
                matriz[y-1][x] = nome;
                if(id == 3)matriz[y-2][x] = nome;
            }else{
                printf("Carro sobreposto: %c %d %c X%dY%d\n",nome,id,eixo,x+1,6-y);
                return;
            }
        }else{
            printf("Limite do estacionamento: %c %d %c X%dY%d\n",nome,id,eixo,x+1,6-y);
            return;
        }
    }else{
        printf("Nao existe o eixo %c!(%c %d %c X%dY%d)\n",eixo,nome,id,eixo,x+1,6-y);
        return;
    }

    addCar(nome, id, eixo, x, y);
}

void zera_mat(char mat[6][6]){
    /* Zeramos a matriz inserindo valores padrões */
    int i,j;
    for(i=0; i<6; i++){
        for(j=0; j<6; j++){
            mat[i][j] = padrao;
        }
    }
}

void rmCar_estac(char mat[6][6],int id){
    /*Remover um carro do estacinamento*/
    int x = saveCar[id].x;
    int y = saveCar[id].y;

    if(saveCar[id].eixo == 'X'){
        mat[y][x] = padrao;
        mat[y][x+1]=padrao;
        if(saveCar[id].id == 3)mat[y][x+2]=padrao;
    }else{
        mat[y][x] = padrao;
        mat[y-1][x]=padrao;
        if(saveCar[id].id == 3){
            mat[y-2][x]=padrao;
        }
    }
}

void mvCar_estac(char mat[6][6],int id, char axis, int mvt){
    /*Remover o carro da matriz */
    rmCar_estac(mat,id);
    saveCar[id].x += (axis == 'X'? mvt:0);
    saveCar[id].y -= (axis == 'Y'? mvt:0);

    int x = saveCar[id].x;
    int y = saveCar[id].y;
    char nome = saveCar[id].nome;

    if(saveCar[id].eixo == 'X'){
        mat[y][x] = nome;
        mat[y][x+1]=nome;
        if(saveCar[id].id == 3){
            mat[y][x+2]=nome;
        }
    }else{
        mat[y][x] = nome;
        mat[y-1][x]=nome;
        if(saveCar[id].id == 3){
            mat[y-2][x]=nome;
        }
    }
}

int colider(char mat[6][6],int id, char axis, int moviment){
    /*Verifica se tem colisão com a parede*/
    int i;
    int a,b,c;
    int x = saveCar[id].x;
    int y = saveCar[id].y;

    if(axis == 'X' || axis == 'x'){
        if(((saveCar[id].eixo == 'Y') && (x + moviment<0 || x + moviment>5)) || (saveCar[id].eixo == 'X' && (x + moviment<0 || ((saveCar[id].id == 2 && x + moviment>4) || (saveCar[id].id == 3 && x + moviment>3))))){
            return 1;
        }

        for(i=moviment; i>0 || i<0; (moviment>0? i-- : i++)){
            a = (mat[y][x+i] != padrao && mat[y][x+i] != saveCar[id].nome);
            b = (mat[y][x+i+1] != padrao && mat[y][x+i+1] != saveCar[id].nome);
            c = (saveCar[id].id == 3 && mat[y][x+i+2] != padrao && mat[y][x+i+2] != saveCar[id].nome);

            if(saveCar[id].eixo == 'Y' && (mat[y][x+i]!=padrao || mat[y-1][x+i]!=padrao || (saveCar[id].id == 3 && mat[y-2][x+i]!=padrao))){
                return 1;
            }else if(saveCar[id].eixo == 'X' && (a || b || c)){
                return 1;
            }
        }
    }else if(axis == 'Y' || axis == 'y'){
        if((saveCar[id].eixo == 'X' && (y - moviment<0 || y - moviment>5)) || (saveCar[id].eixo == 'Y' && (y - moviment>5 || ((saveCar[id].id == 2 && y - moviment<1) || (saveCar[id].id == 3 && y - moviment<2))))){
            return 1;
        }

        for(i=moviment; i>0 || i<0; (moviment>0? i-- : i++)){
            a = (mat[y-i][x] != padrao && mat[y-i][x] != saveCar[id].nome);
            b = (mat[y-1-i][x] != padrao && mat[y-1-i][x] != saveCar[id].nome);
            c = (saveCar[id].id == 3 && mat[y-2-i][x] != padrao && mat[y-2-i][x] != saveCar[id].nome);

            if(saveCar[id].eixo == 'X' && (mat[y-i][x]!=padrao || mat[y-i][x+1]!=padrao || (saveCar[id].id == 3 && mat[y-i][x+2] !=padrao))){
                return 1;
            }else if(saveCar[id].eixo == 'Y' && (a || b || c)){
                return 1;
            }
        }
    }
    return 0;
}

int verificador(char *src_carros, char *src_movimento){
    char nome; //Nome do veículo
    int id;    //Identificador de veículo: carro ou caminhão
    char axis; //Inserir no eixo X ou Y
    int coodx; //Posição no eixo X
    int coody; //Posição no eixo Y
    FILE *entrada = fopen(src_carros,"r"); //Arquivo do conjunto de carros
    FILE *movimnt= fopen(src_movimento,"r");//Arquivo do conjunto de movimento
    char estac[6][6]; //Matriz que simboliza o estacionamento
    zera_mat(estac);

    if(entrada == NULL || movimnt == NULL){
        printf("Não foi possivel abrir os arquivos!\n");
        return 0;
    }

    while(!feof(entrada)){  ///Leitura dos veículos
        fscanf(entrada,"%c %d %c X%dY%d\n",&nome,&id,&axis,&coodx,&coody);
        insert_veiculo(estac,nome,id,axis,coodx,coody); //Insere todos os carros que são lidos de forma genuína, sem colisão contra paredes ou veículos.
    }
    while(!feof(movimnt)){
        fscanf(movimnt,"%c %c %d\n",&nome,&axis,&id);
        if(colider(estac,verifyCar(nome),axis,id)){
            printf("Não pode realizar os conjuntos de manobras!\n");
            return 0;
        }
        else{
            mvCar_estac(estac,verifyCar(nome),axis,id);
        }
    }
    id = verifyCar('Z');
    if(saveCar[id].eixo == 'X' && saveCar[id].x == 4 && saveCar[id].y == 2 && saveCar[id].id == 2){
        printf("Manobras Validas!\n");
    }else{
        printf("Manobras validas!\n");
    }

    return 1;

    fclose(entrada);
    fclose(movimnt);
}

/*-----------HEURISTICA---------*/

int heuristica(char input[100]){
    int sentido = 1;
    int contagem = 0;
    /*Identidade do veiculo*/
	int id;
    /*Nome do Veiculo*/
    char nome;
    /*Qual eixo inserir*/
	char axis;
    /*Posição no eixo*/
	int coodx;
	int coody;

    /*Abertura do arquivo*/
	FILE *entrada = fopen(input,"r");
	FILE *saida = fopen("movimentos.txt","w");
	
    /*Matriz simbolica estacinamento*/
    char estac[6][6];

    if(entrada == NULL){
        printf("Não foi possivel abrir os arquivos!\n");
        return 0;
    }

	zera_mat(estac);

    /*Leitura do arquivo*/
	while(!feof(entrada)){
		fscanf(entrada,"%c %d %c X%dY%d\n",&nome,&id,&axis,&coodx,&coody);
        /*Insere os veiculos ja sabendo que eles nao colidem com a parede*/
		insert_veiculo(estac,nome,id,axis,coodx,coody);
    }

    id = verifyCar('Z');

    if(!(saveCar[id].eixo == 'X') || !(saveCar[id].id == 2)){
        fclose(saida);
        return 0;
    }

    coodx = 0;

    for(contagem = 0; contagem <100; contagem++){
        if(saveCar[id].x == 4 && saveCar[id].y == 2){
            fclose(saida);
            return 1;
        }

        if(saveCar[id].y == 5 || saveCar[id].y == 0){
            sentido = 1 - sentido;
        }

        if(!colider(estac,id,'X',1) && coodx == 0){
            fprintf(saida,"Z X 1\n");
            mvCar_estac(estac,id,'X',1);
            continue;
        }
        coodx = 0;

        if(!colider(estac,id,'Y',1) && (saveCar[id].y >0) && sentido == 1){
            fprintf(saida,"Z Y 1\n");
            mvCar_estac(estac,id,'Y',1);
            continue;
        }

        if(!colider(estac,id,'Y',-1) && (saveCar[id].y <5) && sentido == 0){
            fprintf(saida,"Z Y -1\n");
            mvCar_estac(estac,id,'Y',-1);
            continue;
        }

        if(!colider(estac,id,'X',-1)){
            coodx = 1;
            fprintf(saida,"Z X -1\n");
            mvCar_estac(estac,id,'X',-1);
        }
    }
    
    fclose(entrada);
    fclose(saida);
    
    printf("Não obteve resposta!\n");
    saida = fopen("movimentos.txt","w");
    
    /*Fechamento do arquivo*/
    fclose(saida);

return 0;
}

/*------------Backtrack--------------*/
void zera_vet(int vet[], int tam, int valor){
    int i;
    for(i = 0; i < tam; i++){
        vet[i] = valor;
    }
}

int geraPassoIt(char estac[6][6]){
    int i,j, contador = 0;
    /*Quantidade de moviemntos * quantidade de veiculos = chave de contagem*/
    int lim = 4*qnt;
    int *gerador = (int*)calloc(sizeof(int),limite*qnt);
    posCar *savCar = (posCar*)calloc(sizeof(posCar),qnt);
    int *limCar = (int*)calloc(sizeof(int),qnt);
    char auxEstac[6][6];

    /*Faz backup*/
    for(j = 0; j < qnt; j++){
        savCar[j] = saveCar[j];
    }

    zera_vet(gerador,limite*qnt,-1);

    while(contador < limite*qnt ){
        if(saveCar[verifyCar('Z')].x == 4 && saveCar[verifyCar('Z')].y == 2){
            FILE *movimnt = fopen("movimentos.txt","w");

            for(i = 0; i < limite*qnt && gerador[i] != -1;i++){
                fprintf(movimnt,"%c ",saveCar[(int)gerador[i]/4].nome);
                if(gerador[i]%4 == 0){fprintf(movimnt,"Y 1\n");}
                if(gerador[i]%4 == 1){fprintf(movimnt,"X 1\n");}
                if(gerador[i]%4 == 2){fprintf(movimnt,"Y -1\n");}
                if(gerador[i]%4 == 3){fprintf(movimnt,"X -1\n");}
            }

            fclose(movimnt);
            return 1;
        }

        gerador[0]++;
        contador = 0;
        
        for(i = 0; i < limite*qnt && gerador[i] != -1; i++){
            if(gerador[i] >= lim){gerador[i] =0; gerador[i+1]++;}
            if(gerador[i] == lim-1){contador++;}
        }
        zera_vet(limCar,qnt,0);

        /*Faz compia da matriz*/
        for(j = 0; j < 36; j++){
            auxEstac[(int)j/6][j%6] = estac[(int)j/6][j%6];
        } 

        for(j = 0; j < qnt; j++){
            saveCar[j] = savCar[j];
        }

        for(i = 0; (i < limite*qnt) && gerador[i] != -1; i++){
            limCar[(int)gerador[i]/4]++;
            /*Se ultrapassar o limite de movimentos*/
            if(limCar[(int)gerador[i]/4] <= limite){
                /*Pra cima*/
                if(gerador[i]%4 == 0 && !colider(auxEstac,gerador[i]/4,'Y',1)){
                    mvCar_estac(auxEstac,(int)gerador[i]/4,'Y',1);
                }
                /*Pra direita*/
                if(gerador[i]%4 == 1 && !colider(auxEstac,(int)gerador[i]/4,'X',1)){
                    mvCar_estac(auxEstac,(int)gerador[i]/4,'X',1);
                }
                /*Pra baixo*/
                if(gerador[i]%4 == 2 && !colider(auxEstac,(int)gerador[i]/4,'Y',-1)){
                    mvCar_estac(auxEstac,(int)gerador[i]/4,'Y',-1);
                }/*Pra esquerda*/
                if(gerador[i]%4 == 3 && !colider(auxEstac,(int)gerador[i]/4,'X',-1)){
                    mvCar_estac(auxEstac,(int)gerador[i]/4,'X',-1);
                }
            }
        }
    }

    return 0;
}

void backtrack(char input[100]){
    char nome;
	int id;
	char axis;
	int coodx;
	int coody;

    /*Abertura dos arquivos*/
	FILE *entrada = fopen(input,"r");
	char estac[6][6];

	if(entrada == NULL){
        printf("Não foi possivel abrir os arquivos!\n");
        return;
    }

	zera_mat(estac);

    /*Leitura de veiculos*/
	while(!feof(entrada)){
		fscanf(entrada,"%c %d %c X%dY%d\n",&nome,&id,&axis,&coodx,&coody);
        /*Ja insere sem nenhum carro batendo na parede*/
		insert_veiculo(estac,nome,id,axis,coodx,coody);
    }

    if(!geraPassoIt(estac)){
        printf("Não teve solução!\n");
    }
    fclose(entrada);
}

