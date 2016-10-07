#include "backtrack.h"

posCar saveCar[18];
int qnt;
int menor_sequencia = 541;


void zera_vet(int vet[], int tam, int valor){
    int i;
    for(i = 0; i < tam; i++){
        vet[i] = valor;
    }
}

int geraPassoIt(char estac[6][6]){
    /*Quantidade de movimentos * quantidade de carros == tamanho da chave de contagem*/
    int i,j, contador = 0;
    int lim = 4*qnt;
    int *gerador = (int*)calloc(sizeof(int),limite*qnt);
    posCar *savCar = (posCar*)calloc(sizeof(posCar),qnt);
    int *limCar = (int*)calloc(sizeof(int),qnt);
    char auxEstac[6][6];

    for(j = 0; j < qnt; j++){savCar[j] = saveCar[j];}
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

        /* Copia uma matriz na outra */
        for(j = 0; j < 36; j++){auxEstac[(int)j/6][j%6] = estac[(int)j/6][j%6];}
        for(j = 0; j < qnt; j++){saveCar[j] = savCar[j];}
        for(i = 0; (i < limite*qnt) && gerador[i] != -1; i++){
            limCar[(int)gerador[i]/4]++;
            /* Caso não ultrapassou o limite de movimento */
            if(limCar[(int)gerador[i]/4] <= limite){
                /* Para cima */
                if(gerador[i]%4 == 0 && !colider(auxEstac,gerador[i]/4,'Y',1)){
                    mvCar_estac(auxEstac,(int)gerador[i]/4,'Y',1);
                }
                /* Caso para esquerda */
                if(gerador[i]%4 == 3 && !colider(auxEstac,(int)gerador[i]/4,'X',-1)){
                    mvCar_estac(auxEstac,(int)gerador[i]/4,'X',-1);
                }
                /* Para baixo */
                if(gerador[i]%4 == 2 && !colider(auxEstac,(int)gerador[i]/4,'Y',-1)){
                    mvCar_estac(auxEstac,(int)gerador[i]/4,'Y',-1);
                }
                /* Para direita */
                if(gerador[i]%4 == 1 && !colider(auxEstac,(int)gerador[i]/4,'X',1)){
                    mvCar_estac(auxEstac,(int)gerador[i]/4,'X',1);
                }
            }
        }
    }
    return 0;
}

void backtrack(char input[100]){
    /* Insere no eixo x ou y */
	char axis;
    /* Posicção no eixo X */
	int coodx;
    /* Nome Veiculo */
    char nome; 
    /*Tipo do veiculo */
	int id;
    /* Posicao no eixo Y */
	int coody;
	FILE *entrada = fopen(input,"r");
    /*Matriz Estacionamento */
	char estac[6][6];

	if(entrada == NULL){
        printf("Não ha arquivos de entrada!\n");
        return;
    }

	zera_mat(estac);

    /*Leitura dos arquivos */
	while(!feof(entrada)){
		fscanf(entrada,"%c %d %c X%dY%d\n",&nome,&id,&axis,&coodx,&coody);

        /*Vamos isnerir os veiculos sem colisão*/
		insert_veiculo(estac,nome,id,axis,coodx,coody);
    }

    if(!geraPassoIt(estac)){
        printf("Não obteve solução!");
    }
    fclose(entrada);
}
