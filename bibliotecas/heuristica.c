#include "heuristica.h"

/* VARIAVEIS */
posCar saveCar[18];
int qnt;

int heuristica(char input[100]){
    int sentido = 1;
    int contagem = 0;
    char nome; 
	int id;    
	char axis; 
	int coodx; 
	int coody;
	char estac[6][6];

    /* ABERTURA DOS ARQUIVOS */
	FILE *entrada = fopen(input,"r");
	FILE *saida = fopen("movimentos.txt","w");


    if(entrada == NULL){
        printf("Não foi possivel abrir o arquivo!\n");
        return 0;
    }

	zera_mat(estac);

    /* Leitura dos veiculos */
	while(!feof(entrada)){
		fscanf(entrada,"%c %d %c X%dY%d\n",&nome,&id,&axis,&coodx,&coody);

        /* Insere os carros sem erros (verifca se bateu ou não)*/
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

    /* FCHAMENTO DOS ARQUIVOS */
    fclose(entrada);
    fclose(saida);

    printf("Não foi possivel obter uma resposta!\n");
    
    saida = fopen("movimentos.txt","w");
    fclose(saida);
return 0;
}
