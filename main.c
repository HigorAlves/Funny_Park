#include "bibliotecas/heuristica.h"
#include "bibliotecas/backtrack.h"
#include "bibliotecas/verificador.h"
#include "bibliotecas/geral.h"

int main(int argc, char **argv){
    int v = 0, b = 0, h = 0, i;

    char *veiculo = (char*)calloc(sizeof(char),100);
    char *movimnt = (char*)calloc(sizeof(char),100);
    
    posCar *aux = (posCar*)calloc(sizeof(posCar),1);

    pega_flag(argc,argv,veiculo,movimnt,&h,&b,&v);
    printf("%s %s %d %d %d\n",veiculo,movimnt,h,b,v);

    if(v == 1){
        qnt = 0;
        verificador(veiculo,movimnt);
    }
    if(b == 1){
        qnt = 0;
        backtrack(veiculo);
    }
    if(h == 1){
        qnt = 0;
        heuristica(veiculo);
    }

return 0;
}
