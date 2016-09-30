#ifndef UMABIBLIOTECA_H
#define UMABIBLIOTECA_H

/* DECLARAÇÃO DAS BIBLIOTECAS */
#include <stdio.h>
#include <string.h>
/*----------------------------*/

#define DELIMITER "\n"

typedef struct veiculo{ //estrutura para definir onde cada carro começa
  char nome [2];
  char tipo [2]; // 2 = carro, 3 = caminhão
  char paralelo[2];
  char inicio_x [2];
  char inicio_y [2];
} _veiculo;

/*----------------------------*/

#endif
