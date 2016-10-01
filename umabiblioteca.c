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

int prencher_matriz(_veiculo *carros){
  int matriz[5][5], i = 2, j = 0;
  for (i = 0; i <= 5; i++){
    for (j = 0; j <= 5; i++){
      
    }
  }
}
