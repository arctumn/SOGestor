#include "gestor.h"

LL_proc *createList(int n,LL_proc *head){
  LL_proc *fnNode, *tmp;
  head = calloc(1,sizeof(LL_proc));

  if(!head)
    printf(" Memory can not be allocated.\n");
  
  else {
    tmp = head;
    for(size_t i = 2; i <= n; i++){
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
  printf("\n\n\nVOU MOSTRAR A LISTA\n\n\n");
  if(!stdnode)
    printf("\n\n\nNao mostrei a lista\n\n\n");
  else{
    tmp = stdnode;
    for(size_t i = 1; tmp ;i++) {
      printf(" ProcessoID:%d posicao:%ld\n", tmp->num, i);
      tmp = tmp->nextptr;
    }
    printf("\n\n\nFIM\n\n\n\n");
  }
}

int alocate_mem(int process_id, int num_units,LL_proc *stdnode){
  size_t nodes = 0;
  LL_proc *tmp;
  if(!stdnode){
    //printf(" List is empty.");
    nodes = -1;
    }
  else{
    tmp = stdnode;
    int z = 0;
    for(size_t i = 1; tmp && nodes < MEMORY+1 ; i++, nodes++, tmp = tmp->nextptr){
      
      if(tmp->num == 0 && z < num_units){
        tmp->num = process_id;
        z++;
      }

      //printf(" num:%d i:%ld\n", tmp->num, i);
      }
      if (!tmp && z < num_units){
        deallocate_mem(process_id, stdnode);
        return -1;
      }
  }

  return nodes;
}
int alocate_memTest(int process_id, int num_units,LL_proc *stdnode){
  size_t nodes = 0;
  LL_proc *tmp;
  if(!stdnode){
    //printf(" List is empty.");
    nodes = -1;
    }
  else{
    tmp = stdnode;
    int z = 0;
    for(size_t i = 1; tmp && nodes < 1000+1 ; i++, nodes++, tmp = tmp->nextptr){
      
      if(tmp->num == 0 && z < num_units){
        tmp->num = process_id;
        z++;
      }

      //printf(" num:%d i:%ld\n", tmp->num, i);
      }
      if (!tmp && z < num_units){
        deallocate_mem(process_id, stdnode);
        return -1;
      }
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
  if(!test){ 
    return -1;}
  return 1;
}


// retorna o número de furos (fragmentos de tamanhos 1 ou 2 unidades).

int fragment_count(LL_proc* processes) {
  int holes = 0, counter = 0;
  LL_proc* tmp = processes;
  if(!tmp) return holes;

  for(; tmp; tmp = tmp->nextptr) {
    if(!tmp->num && tmp->nextptr) {
      if(tmp->nextptr->nextptr && !tmp->nextptr->nextptr->num){
        counter++;
        continue;
      }
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