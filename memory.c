#include "gestor.h"

LL_proc *createList(int n,LL_proc *head){
  LL_proc *fnNode, *tmp;
  head = calloc(1,sizeof(LL_proc));

  if(!head)
    printf(" Memory can not be allocated.\n");
  
  else {
    tmp = head;
    for(size_t i = 2; i <= MEMORY; i++){
      fnNode = calloc(1,sizeof(LL_proc));

      if(!fnNode){
        printf(" Memory can not be allocated.\n");
        break;
      } else {
        tmp->nextptr = fnNode;
        tmp = tmp->nextptr; 
      }
    }
  }

  return head;
}

void PrintList(LL_proc *stdnode){
  LL_proc *tmp;
  if(!stdnode)
    printf(" List is empty.");
  else{
    tmp = stdnode;
    for(size_t i = 1; tmp ;i++) {
      printf(" ProcessoID:%d posicao:%ld\n", tmp->num, i);
      tmp = tmp->nextptr;
    }
  }
}

int alocate_mem(int process_id, int num_units,LL_proc *stdnode){
  size_t nodes = 0;
  LL_proc *tmp;
  if(!stdnode)
    printf(" List is empty.");
  else{
    tmp = stdnode;
    for(size_t i = 1; tmp && nodes < MEMORY+1 ; i++, nodes++, tmp = tmp->nextptr)
      printf(" num:%d i:%ld\n", tmp->num, i);
  }

  return nodes;
}

int deallocate_mem(int process_id,LL_proc *mem){
  LL_proc *aux;
  aux = mem;
  int test = 0;
  while(aux != NULL){
    if(aux->num == process_id){
      aux->num = 0;
      test++;
    }
    aux = aux->nextptr;
  }
  if(!test) return -1;
  return 1;
}

int fragment_count (LL_proc *mem){
  LL_proc *aux = mem;
  int counter = 0, flag_frag = 0;
  while(aux != NULL){
    if (flag_frag){
      if(aux->num == 0){
        counter++;
        aux = aux->nextptr;
      }
      else {
        flag_frag = 0;
        aux = aux->nextptr;
      }
    }
    if(aux->num != 0){
      flag_frag = 1;
      aux = aux ->nextptr;
    }
  }
  return counter;
}

// retorna o número de furos (fragmentos de tamanhos 1 ou 2 unidades).

int fragger(LL_proc* processes) {
  int holes = 0, counter = 0;
  LL_proc* tmp = processes;
  if(!tmp) return holes;

  for(; tmp; tmp = tmp->nextptr) {
    if(!tmp->num) {
      counter++;
      continue;
    }
    if(counter) {
      counter = 0;
      holes++;
    }
  }

  return holes;
}

// process_id 1 1 1 1 1 0 0 0 1 2 2 2 2 0 0 0
// mem_slot   1 2 3 4 5 6 7 8 9 10 ...
// 