#include "verificador.h"

posCar saveCar[20];
int qnt = 0;

/*Verificamos se existe algum carro */
int verifyCar(char nome){
    int i;
    for(i = 0; i<qnt; i++){
        if(nome == saveCar[i].nome){
            return i;
        }
    }
    return -1;
}

/*Adicionar um carro */
void addCar(char nome, int id, char eixo, int x, int y){
    saveCar[qnt].eixo = eixo;
    saveCar[qnt].id = id;
    saveCar[qnt].nome = nome;
    saveCar[qnt].y = y;
    saveCar[qnt].x = x;
    qnt++;
}

/*Coloca carro na matriz*/
void insert_veiculo(char matriz[6][6],char nome, int id, char eixo, int x, int y){
    x --;
    y = 6 - y;
    int A,B;

    if(verifyCar(nome) != -1){
        printf("Existe o carro, (%c %d %c X%dY%d)\n",nome,id,eixo,x+1,6-y);
        return;
    }

    /*Insere no eixo x*/
    if(eixo=='X' || eixo=='x'){
        eixo = 'X';

        A = matriz[y][x] == padrao && matriz[y][x+1] == padrao;
        B = matriz[y][x+2] == padrao;

        /*Ta nos limites do estacionamento? | Teve colisão?*/
        if(((id == 2) && (x>=0) && (x<5) && (y>=0) && (y<=5)) || ((id == 3) && (x>=0) && (x<4) && (y>=0) && (y<=5))){  
            if((A && B) || (!(id == 3) && A)){
                matriz[y][x] = nome;
                matriz[y][x+1] = nome;

                if(id == 3)matriz[y][x+2] = nome;
            }
            else{
                printf("Colisão");
                return;
            }
        }
        else{
            printf("Passou os limites do estacionamento.");
            return;
        }
    /* Inserir no sentido Y*/
    }else if(eixo=='Y' || eixo=='y'){
        eixo = 'Y';
        A = matriz[y][x] == padrao && matriz[y-1][x] == padrao;
        B = matriz[y-2][x] == padrao;
        if(((id == 2) && (x>=0) && (x<=5) && (y>0) && (y<=5)) || ((id == 3) && (x>=0) && (x<=5) && (y>1) && (y<=5))){
            if((A && B) || (!(id == 3) && A)){
                matriz[y][x] = nome;
                matriz[y-1][x] = nome;
                if(id == 3)matriz[y-2][x] = nome;
            }
            else{
                printf("Colisãos");
                return;
            }
        }
        else{
            printf("Passou dos limites do estacionamento.");
            return;
        }
    }
    /*Não existe o eixo*/
    else{
        printf("Nao existe eixo");
        return;
    }

    addCar(nome, id, eixo, x, y);
}
/*Zera a matriz*/
void zera_mat(char mat[6][6]){
    int i,j;
    for(i=0; i<6; i++){
        for(j=0; j<6; j++){
            mat[i][j] = padrao;
        }
    }
}

/*Remover um carro*/
void rmCar_estac(char mat[6][6],int id){
    int x = saveCar[id].x;
    int y = saveCar[id].y;
    if(saveCar[id].eixo == 'X'){
        mat[y][x] = padrao;
        mat[y][x+1]=padrao;
        if(saveCar[id].id == 3)mat[y][x+2]=padrao;
    }
    else{
        mat[y][x] = padrao;
        mat[y-1][x]=padrao;
        if(saveCar[id].id == 3)mat[y-2][x]=padrao;
    }
}
/*Remove um carro do estacionamento*/
void mvCar_estac(char mat[6][6],int id, char axis, int mvt){
    rmCar_estac(mat,id);
    saveCar[id].x += (axis == 'X'? mvt:0);
    saveCar[id].y -= (axis == 'Y'? mvt:0);
    int x = saveCar[id].x;
    int y = saveCar[id].y;
    char nome = saveCar[id].nome;
    if(saveCar[id].eixo == 'X'){
        mat[y][x] = nome;
        mat[y][x+1]=nome;
        if(saveCar[id].id == 3)mat[y][x+2]=nome;
    }
    else{
        mat[y][x] = nome;
        mat[y-1][x]=nome;
        if(saveCar[id].id == 3)mat[y-2][x]=nome;
    }
}

/*Verifica se bateu*/
int colider(char mat[6][6],int id, char axis, int moviment){
    int a,b,c;
    int x = saveCar[id].x;
    int y = saveCar[id].y;
    int i;

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
            }
            else if(saveCar[id].eixo == 'X' && (a || b || c)){
                return 1;
            }
        }
    }
    else if(axis == 'Y' || axis == 'y'){
        if((saveCar[id].eixo == 'X' && (y - moviment<0 || y - moviment>5)) || (saveCar[id].eixo == 'Y' && (y - moviment>5 || ((saveCar[id].id == 2 && y - moviment<1) || (saveCar[id].id == 3 && y - moviment<2))))){
            return 1;
        }
        for(i=moviment; i>0 || i<0; (moviment>0? i-- : i++)){
            a = (mat[y-i][x] != padrao && mat[y-i][x] != saveCar[id].nome);
            b = (mat[y-1-i][x] != padrao && mat[y-1-i][x] != saveCar[id].nome);
            c = (saveCar[id].id == 3 && mat[y-2-i][x] != padrao && mat[y-2-i][x] != saveCar[id].nome);

            if(saveCar[id].eixo == 'X' && (mat[y-i][x]!=padrao || mat[y-i][x+1]!=padrao || (saveCar[id].id == 3 && mat[y-i][x+2] !=padrao))){
                return 1;
            }
            else if(saveCar[id].eixo == 'Y' && (a || b || c)){
                return 1;
            }
        }
    }
    return 0;
}

int verificador(char *src_carros, char *src_movimento){
    int id;   
    char nome;
    char estac[6][6];
    char axis;
    int coodx,coody;

    FILE *entrada = fopen(src_carros,"r");
    FILE *movimnt= fopen(src_movimento,"r");

    zera_mat(estac);

    if(entrada == NULL || movimnt == NULL){
        printf("Não foi possivel ler os arquivos.\n");
        return 0;
    }

    while(!feof(entrada)){
        fscanf(entrada,"%c %d %c X%dY%d\n",&nome,&id,&axis,&coodx,&coody);
        insert_veiculo(estac,nome,id,axis,coodx,coody);
    }
    while(!feof(movimnt)){
        fscanf(movimnt,"%c %c %d\n",&nome,&axis,&id);
        if(colider(estac,verifyCar(nome),axis,id)){
            printf("Manobras invalidas\n");
            return 0;
        }
        else{
            mvCar_estac(estac,verifyCar(nome),axis,id);
        }
    }
    id = verifyCar('Z');
    if(saveCar[id].eixo == 'X' && saveCar[id].x == 4 && saveCar[id].y == 2 && saveCar[id].id == 2){
        printf("Manobras Validas\n");
    }else{
        printf("manobras invalidas\n");
    }

    return 1;

    fclose(entrada);
    fclose(movimnt);
}
