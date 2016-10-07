#include "geral.h"


int verifyCar(char nome);
void addCar(char nome, int id, char eixo, int x, int y);
void insert_veiculo(char matriz[6][6],char nome, int id, char eixo, int x, int y);
void zera_mat(char mat[6][6]);
void rmCar_estac(char mat[6][6],int id);
void mvCar_estac(char mat[6][6],int id, char axis, int mvt);
int colider(char mat[6][6],int id, char axis, int moviment);
int verificador(char *src_carros, char *src_movimento);
