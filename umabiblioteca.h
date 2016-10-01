#ifndef UMABIBLIOTECA_H
#define UMABIBLIOTECA_H

/* DECLARAÇÃO DAS BIBLIOTECAS */
#include <stdio.h>
#include <string.h>
#include <malloc.h>
/*----------------------------*/

#define DELIMITER "\n"

typedef struct veiculo{ //estrutura para definir onde cada carro começa
  char nome [2];
  char tipo [2]; // 2 = carro, 3 = caminhão
  char paralelo[2];
  char inicio_x [2];
  int fim_x;
  char inicio_y [2];
  int fim_y;
  int meio;
} _veiculo;

/*----------------------------*/
void verifica_carros(_veiculo *carros, int *n);
int prencher_matriz(_veiculo *carros, int *n);

#endif
