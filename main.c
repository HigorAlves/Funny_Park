/* Todas as declarações sobre bibliotecas foram feitas no arquivo umabiblioteca.h */
#include "umabiblioteca.h"
/*------------------------*/

int main (){
  char word1[2],word2[2],word3[2],word4[5];
  int i = 1, n = 1, j = 1;
  /* Abrimos o arquivo e verificamos se realmente conseguimos abri-lo */
  FILE *IN_carros = fopen ("carros.txt", "r");

  if (IN_carros == NULL){
    printf("Não foi possivel ler o arquivo de configuração dos carros\n");
    return 0;
  }

  /* Declaramos a quantidade de carros */
  _veiculo carros[n];

  /* Pegar os dados do arquivo */
  while ((fscanf (IN_carros, "%s %s %s %s", word1, word2, word3, word4)) != EOF){
    printf("WORD: %s\n", word1);
    strcpy(carros[i].nome, word1);
    n++;
    i++;
  }
  i = 1;
  printf("\nFora do Loop:%s\n",carros[i].nome);

  return 0;
}
