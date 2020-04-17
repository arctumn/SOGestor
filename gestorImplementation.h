#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
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

void atribuidorDeInstrucoes(char *nomeFich,char **arrayFinalStrings, processo *processoAtual){ // DEVOLVER OQUE?
    FILE *fp1 = fopen(nomeFich,"r");
    char *arraydestrings[90];
    char string[20];
    int i = 0,c = 0,structChecker = 0;
    if (fp1 == NULL){
        perror("NAO EXISTE O FICHEIRO\n");
        return;
    }
    while(fgets(string,sizeof(string),fp1) != 0){
        arraydestrings[i] = strndup(string,sizeof(string));
        printf("%s",arraydestrings[i]);
        i++;
    }
    fclose(fp1);
    i=0;
    printf("\n----------INICIO DO PARSING DO FICHEIRO---------\n");
    while(arraydestrings[i] != NULL){
        printf("%s",arraydestrings[i]);
        if(!(strncmp(arraydestrings[i],"nome:",5))){
            char *nome = strtok(arraydestrings[i],":");
            processoAtual->nome = nome;
            structChecker++; 
        }
        if(!(strncmp(arraydestrings[i],"processValue:",strlen("processValue:")))){
            char *processValue = strtok(arraydestrings[i],"processValue:");
            processoAtual->processValue = atoi(processValue);
            structChecker++; 
        }
        if(!(strncmp(arraydestrings[i],"pid:",4))){
            char *npid = strtok(arraydestrings[i],"pid:");
            processoAtual->pid = atoi(npid);
            structChecker++;
        }
        if(!(strncmp(arraydestrings[i],"ppid:",5))){
            char *nppid = strtok(arraydestrings[i],"ppid:");
            processoAtual->ppid = atoi(nppid);
            structChecker++;
        }
        if(!(strncmp(arraydestrings[i],"prioridade:",strlen("prioridade:")))){
            char *prioridade = strtok(arraydestrings[i],"prioridade:");
            processoAtual->prioridade = atoi(prioridade);
            structChecker++;
        }
       if(!(strncmp(arraydestrings[i],"tempoVida:",strlen("tempoVida:")))){
            char *tVida = strtok(arraydestrings[i],"tempoVida:");
            processoAtual->tempoVida = atoi(tVida);
            structChecker++; 
        } 
        if(!(strncmp(arraydestrings[i],"PC:",strlen("PC:")))){
            char *PC = strtok(arraydestrings[i],"PC:");
            processoAtual->PC = atoi(PC);
            structChecker++;
        }
        if(!(strncmp(arraydestrings[i],"I:",strlen("I:")))){
            char *I = strtok(arraydestrings[i],"I:");
            arrayFinalStrings[c] = I;
            c++;
        }
        i++;
    }
    if (structChecker != 7){
        printf("Programa Invalido\n");
        return;
    }
}