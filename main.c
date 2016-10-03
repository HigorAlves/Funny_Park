/* Todas as declarações sobre bibliotecas foram feitas no arquivo umabiblioteca.h */
#include "umabiblioteca.h"
#include "heuristica.h"
/*------------------------*/


int main (){
  char word [2]; //Somente para guardar o lixo do arquivo
  int i = 1, n = 0, aux = 0;
  /*---------------------------LEITURA ARQUIVO-------------------------*/
  /* Abrimos o arquivo e verificamos se realmente conseguimos abri-lo */
  FILE *IN_carros = fopen ("/Users/lidimarsantos/Documents/faculdade/AEDS 3/tp2/tp2/Funny_Park_inc/carros.txt", "r");

  if (IN_carros == NULL){
    printf("Não foi possivel ler o arquivo de configuração dos carros\n");
    return 1;
  }

  while ((fscanf (IN_carros, "%m[^"DELIMITER"]%*["DELIMITER"]", word)) != EOF){
    n++;
  }
  rewind(IN_carros);

  /* Declaramos a quantidade de carros */
  _veiculo carros[n];

  /* Pegar os dados do arquivo e prencher toda a struct*/
  while ((fscanf (IN_carros, "%s %s %s %c%c%c%c", carros[i].nome, carros[i].tipo, carros[i].paralelo, word, carros[i].inicio_x, word, carros[i].inicio_y)) != EOF){
    if (strcmp (carros[i].paralelo, "Y") == 0){
      if (strcmp (carros[i].tipo, "2") == 0){
        carros[i].fim_y = atoi(carros[i].inicio_y) + 2;
        carros[i].meio = carros[i].fim_y - 1;
      }else if (strcmp (carros[i].tipo, "3") == 0){
        carros[i].fim_y = atoi(carros[i].inicio_y) + 2;
        carros[i].meio = carros[i].fim_y - 1;
      }else{
        printf("Tipo do carro é invalido\n");
      }
    }else if (strcmp (carros[i].tipo, "X") == 0){
      if (strcmp (carros[i].tipo, "2") == 0){
        carros[i].fim_x = atoi(carros[i].inicio_x) + 2;
        carros[i].meio = carros[i].fim_x - 1;
      }else if (strcmp (carros[i].tipo, "3") == 0){
        carros[i].fim_x = atoi(carros[i].inicio_x) + 2;
        carros[i].meio = carros[i].fim_x - 1;
      }else{
        printf("Tipo do carro é invalido\n");
      }
    }
    i++;
  }
  fclose(IN_carros);
  /*---------------------------------------------------------------------*/
  verifica_carros(&carros, &n);
  prencher_matriz(&carros, &n);

  return 0;
}
