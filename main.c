#include "gestor.h"

int main(){
    char ** leitura =(char **)malloc(80*sizeof(char *));
    int i = 0;
    processo A;
    atribuidorDeInstrucoes("teste.txt",leitura,&A);
    printf("\n");
    printf("Info do processo ->\n");
    printf("%s %d %d %d %d %d %d\n",A.nome,A.pid,A.ppid,A.prioridade,A.tempoVida,A.PC,A.processValue);
    printf("Intruçoes do processo ->\n");
    while(leitura[i] != NULL){
        printf("%d: %s",i,leitura[i]);
        i++;
    }   
}