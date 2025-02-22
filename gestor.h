#ifndef _ai_ui_
#define _ai_ui_

#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>

#define MEMORY 100

// STRUCT PROCESSO
//nome -> nome do processo
//pid -> identificador de processo gestor pid = 0
//ppid -> pai da pid, se este for filho
//prioridade -> prioridade de execucao 1 > 2 > 3
//tempoVida -> tempo que tem de ser executado
//PC -> numero de instruções
//processValue -> valor do processo
//quantidadeDeIntrucoes -> numero de Intruções do progama
typedef struct processo{
    char *nome;     
    int pid;        
    int ppid;    
    int prioridade;   
    int tempoVida;  
    int PC;         
    int processValue;   
    int quantidadeDeIntrucoes;
    int programMemory;
} processo;

// STRUCT PROGRAMA
// nomeProg -> nome do programa
// processo -> struct com informações do programa
// listaDeInstrucoes -> lista com as operações do programa
// estado -> RUNNING 0 / PARADO 1 / MORTO 2
typedef struct programa{
    char *nomeProg;
    processo infoProcesso;
    char ** listaDeIntrucoes;
    int estado;
    int arrivalTime;
}programa;


//Pega num ficheiro e da parse dele separando em instruçoes e na estrutura que o define
void atribuidorDeInstrucoes(char *nomeFich,char **arrayFinalStrings, processo *processoAtual);
//Unifica numa estrutura as intruções de um programa e a informações sobre o programa
programa juntor(int arrivalTime,processo info,char ** listaDeIntrucoesInfo);

//Precorre as instruções de um programa
void percorrerIntrucoes(programa *progAPercorrer);

//Cria um programa filho igual ao pai
void filho(programa pai);

//Precorre todo o programa Serve para o FIFO
void programaRunnerFifo(char *nomeDoPrograma);

//Precorre em fifo
void fifo(const char *listaDeProgramas);

//Precorre em SJF
void priority(char *listaDeProgramas);

//strlen mas para strings menores
int Strlen(const char *string);

//Encontra a posição do caracter na string
void strfind(const char*string,char charProcuravel,int *pos);

//Executar em SJF
void percorrerIntrucoesPriority(programa *progAPercorrer);

void programaRunnerPriority(programa *listaDeProgramas,int counter);

void *filhoThread(void *pai);

void percorrerIntrucoesThread(programa *progAPercorrer);

//variavel que é responsavel pela memoria dos programas


typedef struct mem_Space {
    int num;
    struct mem_Space *nextptr;
} LL_proc;

typedef struct ideia {
  LL_proc* head;
  LL_proc* end;
  size_t total;
} LL_wrapper;

//createlist
struct mem_Space *createList(int n,struct mem_Space *stdnode);

//printlist
void PrintList(struct mem_Space *stdnode);
//aloc
int alocate_mem (int process_id, int num_units,struct mem_Space *mem);
//dealoc
int deallocate_mem(int process_id,struct mem_Space *mem);
// contador de fragmentos
int fragment_count (struct mem_Space *mem);
//procura um elemento no array devovle a psição
int procuraPidLista(int b, int *lista);
//Teste
void memoryTest();
//alocate teste
int alocate_memTest(int process_id, int num_units,LL_proc *stdnode);

void SJF(char *listaDeProgramas);

void programaRunnerSJF(programa *listaDeProgramas, int count);

#endif