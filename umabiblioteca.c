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
  }

}

int prencher_matriz(_veiculo *carros, int *n){
  int matriz[7][7], i = 0, j = 0, aux = 1, aux2 = 0, aux3 = 0;

  for (aux = 1; aux <= *n; aux++){
    i = atoi(carros[aux].inicio_x);
    j = atoi(carros[aux].inicio_y);
    matriz[i][j] = 33;
  }
  return 0;
}
