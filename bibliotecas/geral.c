#include "geral.h"

void pega_flag(int argc, char **argv, char parg[100], char earg[100], int *h, int *b, int *v){
    int verbose;

    opterr = 0;
    
    while((verbose = getopt(argc,argv,"v:m:HBV")) != -1){
        switch(verbose){
        case 'v':
            strcpy(parg,optarg);
            break;
        case 'm':
            strcpy(earg,optarg);
            break;
        case 'H':
            *h = 1;
            break;
        case 'B':
            *b = 1;
            break;
        case 'V':
            *v = 1;
            break;
        case '?':
            if (optopt == 'v'){
                printf("Opcao \"%c\" necessita de mais argumentos!\n", optopt);
            }
            else if( optopt == 'm' ){
                printf("Opcao \"%c\" necessita de mais argumentos!\n", optopt);
            }else{
                printf("Opcao \"%c\" desconhecida!\n",optopt);
            }
            return;
        }
    }
}
