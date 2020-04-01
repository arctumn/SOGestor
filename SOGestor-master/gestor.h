#include <stdio.h>
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
    int variavel;   //valor do processo
} processo;

char ** atribuidorDeInstrucoes(char * nomeFich, processo * processoAtual);

char ** atribuidorDeInstrucoes(char *nomeFich, processo * processoAtual){ // DEVOLVER OQUE?
    FILE *fp1 = fopen(nomeFich,"r");
    processo * atual = NULL;
    char string[20];
    char *arraydestrings[90];
    int i = 0;
    if (fp1 == NULL){
        perror("NAO EXISTE O FICHEIRO\n");
        return NULL;
    }
    while(fgets(string,sizeof(string),fp1) != 0){
        arraydestrings[i] = string;
        i++;
    }
    fclose(fp1);
    i=0;
    while(!strcmp(arraydestrings[i],"T")){
        if(!(strncmp(arraydestrings[i],"nome:",5))){
            char *nome = strtok(arraydestrings[i],"nome");
            processoAtual->nome = nome;
            i++;
            continue;  
        }
        if(!(strncmp(arraydestrings[i],"pid:",4))){
            char * npid = strtok(arraydestrings[i],"pid:");
            processoAtual->pid = atoi(npid);
            i++;
            continue;  
        }
        if(!(strncmp(arraydestrings[i],"ppid:",5))){
            char * nppid = strtok(arraydestrings[i],"ppid:");
            processoAtual->ppid = atoi(nppid);
            i++;
            continue;  
        }
        if(!(strncmp(arraydestrings[i],"prioridade:",strlen("prioridade:")))){
            char * prioridade = strtok(arraydestrings[i],"prioridade:");
            processoAtual->prioridade = atoi(prioridade);
            i++;
            continue;  
        }
       if(!(strncmp(arraydestrings[i],"tempoVida:",strlen("tempoVida:")))){
            char * tVida = strtok(arraydestrings[i],"tempoVida:");
            processoAtual->tempoVida= atoi(tVida);
            i++;
            continue;  
        } 
        if(!(strncmp(arraydestrings[i],"PC:",strlen("PC:")))){
            char * PC = strtok(arraydestrings[i],"PC:");
            processoAtual->PC = atoi(PC);
            i++;
            continue;  
        }
        if(!(strncmp(arraydestrings[i],"M:",strlen("M:")))){
            char * M = strtok(arraydestrings[i],"M:");
            
            i++;
            continue;  
        }
        if(!(strncmp(arraydestrings[i],"C:",strlen("C:")))){
            char * C = strtok(arraydestrings[i],"C:");
            
            i++;
            continue;  
        }
        if(!(strncmp(arraydestrings[i],"A:",strlen("A:")))){
            char * A = strtok(arraydestrings[i],"A:");
            
            i++;
            continue;  
        }
        if(!(strncmp(arraydestrings[i],"S:",strlen("S:")))){
            char * S = strtok(arraydestrings[i],"S:");
            
            i++;
            continue;  
        }
    }
}
