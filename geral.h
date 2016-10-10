/*Bibliotoecas*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/resource.h>
#include <sys/time.h>
/*---------------------*/

/*Defines*/
#define padrao '+'
#define limite 100

/*Structs*/
#ifndef ESTRUTURAS
#define ESTRUTURAS

typedef struct s_posCar{
    char nome;
    char eixo;
    int id;
    int x;
    int y;
} posCar;

typedef struct s_passos{
    int id;
    /*Direção usando os pontos cardeais*/
    char direcao;
    char eixo;
    int mov;
    struct s_passos *proximo;
}passos;

typedef struct s_descritor{
    passos *topo;
    int tam;
}descritor;

#endif // ESTRUTURAS
/*-------------------------*/

/*FUNÇÕES*/
void pega_flag(int argc, char **argv, char parg[100], char earg[100], int *h, int *b, int *v);

int verifyCar(char nome);
void addCar(char nome, int id, char eixo, int x, int y);
void insert_veiculo(char matriz[6][6],char nome, int id, char eixo, int x, int y);
void zera_mat(char mat[6][6]);
void rmCar_estac(char mat[6][6],int id);
void mvCar_estac(char mat[6][6],int id, char axis, int mvt);
int colider(char mat[6][6],int id, char axis, int moviment);
int verificador(char *src_carros, char *src_movimento);

int heuristica(char input[100]);

void zera_vet(int vet[], int tam, int valor);
int geraPassoIt(char estac[6][6]);
void backtrack(char entrada[100]);