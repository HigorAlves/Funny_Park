#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define limite 100
#define padrao '+'

#define limpa system("Limpa");

#ifndef ESTRUTURAS
#define ESTRUTURAS


typedef struct s_passos{
    int id;
    /*Direção usando os pontos cardiais.*/
    char direcao;
    char eixo;
    int mov;
    struct s_passos *proximo;
}passos;

typedef struct s_posCar
{
    char nome;
    char eixo;
    int id;
    int x;
    int y;
} posCar;

typedef struct s_descritor{
    passos *topo;
    int tam;
}descritor;


#endif 

void pega_flag(int argc, char **argv, char parg[100], char earg[100], int *h, int *b, int *v);
