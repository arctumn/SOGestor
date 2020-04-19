#include "gestor.h"

int main(){
    char ** leitura =(char **)malloc(80*sizeof(char *));
    int i = 0;
    processo A;
    programa *AB = (programa *)malloc(sizeof(programa));
    atribuidorDeInstrucoes("teste.txt",leitura,&A);
    AB = juntor(A,leitura);
    printf("\n");
    printf("Info do processo ->\n");
    printf("%s %d %d %d %d %d %d %d\n",A.nome,A.pid,A.ppid,A.prioridade,A.tempoVida,A.PC,A.processValue,A.quantidadeDeIntrucoes);
    printf("Execução do processo ->\n");
    percorrerIntrucoes(AB);
    printf("Counter: %d \n FIM\n",AB->infoProcesso.PC);
}