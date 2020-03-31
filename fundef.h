#include "gestor.h"

int atribuidorDeInstrucoes(char *nomeFich){ // DEVOLVER OQUE?
    FILE *fp1 = fopen(nomeFich,"r");
    processo atual = NULL;
    if (fp1 == NULL){
        perror("NAO EXISTE O FICHEIRO\n");
        return -1;
    }

    while(char atual = fgetc(fp1)!= 'T'){ //M A S B T C L
        if (atual = 'M'){
            
            continue;
        }
    }
}