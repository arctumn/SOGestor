#include <stdio.h>
#include "gestorImplementation.h"
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>
#include <fcntl.h>
#include <string.h>
//              nome:fdp
//              pid:666
//              ppid:69
//              prioridade:1
//              tempoVida:15
//              PC:40
//              fim
//              M 100
//              C 2    duas instruçoes pos fork
//              A 19
//              S 5 
//              T

typedef struct processo{
    char *nome;     // nome do processo
    int pid;        //identificador de processo gestor pid = 0
    int ppid;       //pai da pid, se este for filho
    int prioridade; //prioridade de execucao 1 > 2 > 3
    int tempoVida;  // tempo que tem de ser executado
    int PC;         // numero de instruções
    int processValue;   //valor do processo
} processo;

typedef struct programa
{
    processo infoProcesso;
    char ** listaDeIntrucoes;
}programa;

void atribuidorDeInstrucoes(char *nomeFich,char **arrayFinalStrings, processo *processoAtual);
