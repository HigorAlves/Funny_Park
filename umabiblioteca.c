#include "umabiblioteca.h"

void verifica_carros(_veiculo *carros, int *n){
  int i, j;

  for (i = 1; i <= *n; i++){
    for (j = 1; j <= i; j++){
      /* Verifica se tem dois carros com o mesmo nome */
      if (strcmp (carros[i].nome, carros[j].nome) == 0){
        if (i != j){

          printf("Dois carros com mesmo nome!\n");
          exit(1);

        }
      }
    }
    /* Verifica se algum veiculo ultrapassou os limites do estacionamento no eixo Y */
    if (strcmp(carros[i].paralelo, "Y") == 0){
      if (strcmp(carros[i].tipo, "2") == 0){
        if (atoi(carros[i].inicio_y) + 1 > 6 || atoi(carros[i].inicio_y) > 6){
          printf("Carro ultrapassando o limite do estacionamento\n");
        }
      }else if (strcmp(carros[i].tipo, "3") == 0){
        if (atoi(carros[i].inicio_y) + 2 > 6 || atoi(carros[i].inicio_y) > 6){
          printf("Carro ultrapassando o limite do estacionamento\n");
        }
      }
    }else{
      /* Verifica se algum veiculo ultrapassou os limites do estacionamento no eixo X */
      if (strcmp(carros[i].tipo, "2") == 0){
        if (atoi(carros[i].inicio_x) + 1 > 6 || atoi(carros[i].inicio_x) > 6){
          printf("Carro ultrapassando o limite do estacionamento\n");
        }
      }else if (strcmp(carros[i].tipo, "3") == 0){
        if (atoi(carros[i].inicio_x) + 2 > 6 || atoi(carros[i].inicio_x) > 6){
          printf("Carro ultrapassando o limite do estacionamento\n");
        }
      }
    }
  }
}

int prencher_matriz(_veiculo *carros, int *n){
  int matriz[7][7], i = 0, j = 0, aux = 1, aux2 = 0, aux3 = 0;

  /* Zerando a matriz */
  for (i = 0; i <= 7; i++){
    for (j = 0; j <= 7; j++){
      matriz[i][j] = 0;
    }
  }

  /* prenchendo a matriz vazia */
  for (aux = 1; aux <= *n; aux++){
    i = atoi(carros[aux].inicio_y);
    j = atoi(carros[aux].inicio_x);
    /*Verifica se o carro é paralelo a X ou a Y*/
    if (strcmp(carros[aux].paralelo, "X") == 0){
      /* Verifica se ao redor esta vazio e qual o tipo de veiculo */
      if (matriz[i][j] == 0 && matriz[i+1][j] == 0 && strcmp(carros[aux].tipo, "2") == 0){
        matriz[i][j] = 1;
        matriz[i][j+1] = 1;
      }else if (matriz[i][j] == 0 && matriz[i+1][j] == 0 && strcmp(carros[aux].tipo, "3") == 0){
        matriz[i][j] = 1;
        matriz[i][j+1] = 1;
        matriz[i][j+2] = 1;
      }else{
        printf("Colisão de Carros\n");
        return 1;
      }
    }else {
      /* Verifica se ao redor esta vazio e qual o tipo de veiculo */
      if (matriz[i][j] == 0 && matriz[i+1][j] == 0 && strcmp(carros[aux].tipo, "2") == 0){
        matriz[i][j] = 1;
        matriz[i+1][j] = 1;
      }else if (matriz[i][j] == 0 && matriz[i+1][j] == 0 && strcmp(carros[aux].tipo, "3") == 0){
        matriz[i][j] = 1;
        matriz[i+1][j] = 1;
        matriz[i+2][j] = 1;
      }else{
        printf("Colisão de Carros\n");
        return 1;
      }
    }
  }
  //SO imprimi a matriz nada de mais
  for (i = 6; i >= 1; i--){
    for (j = 1; j <= 6; j++){
      printf("%d ",matriz[i][j]);
    }
    printf("\n");
  }
  return 0;
}
