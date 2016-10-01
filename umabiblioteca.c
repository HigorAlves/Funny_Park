#include "umabiblioteca.h"

void verifica_carros(_veiculo *carros, int *n){
  int i, j;

  for (i = 1; i <= *n; i++){
    for (j = 1; j <= i; j++){
      if (strcmp (carros[i].nome, carros[j].nome) == 0 || strcmp (carros[i].inicio_x, carros[j].inicio_y) == 0){
        if (i != j){
          printf("Dois carros com mesmo valor verifique o seu arquivo!\n");
          return 1;
        }
      }
    }
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
    i = atoi(carros[aux].inicio_x);
    j = atoi(carros[aux].inicio_y);
    matriz[i][j] = 33;
    if (strcmp (carros[aux].paralelo, "Y") == 0){
      if (strcmp (carros[aux].tipo, "2") == 0){
        matriz[i+1][j] = 33;
      }else if (strcmp (carros[aux].tipo, "3") == 0){
        matriz[i][j+1] = 33;
        matriz[i][j+2] = 33;
      }
    }
  }
  return 0;
}
