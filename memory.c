#include "gestor.h"

struct mem_Space *createList(int n,struct mem_Space *stdnode){
    struct mem_Space *fnNode, *tmp;
    int num = 0, i;
    stnode =malloc(sizeof(struct mem_Space));
    n = memory;
    if(stnode == NULL){
        printf(" Memory can not be allocated.");
    }
    else{
        stnode->num = num;      
        stnode->nextptr = NULL;
        tmp = stnode;
        for(i=2; i<=n; i++){
            fnNode = (struct mem_Space *)malloc(sizeof(struct mem_Space));
            if(fnNode == NULL){
                printf(" Memory can not be allocated.");
                break;
            }
            else{
                fnNode->num = num;
                fnNode->nextptr = NULL;
                tmp->nextptr = fnNode;
                tmp = tmp->nextptr; 
            }
        }
    }
    return stdnode;
}
void PrintList(struct mem_Space *stdnode){
    int i = 1;
    struct mem_Space *tmp;
    if(stnode == NULL){
      printf(" List is empty.");
    }
    else{
        tmp = stnode;
        while(tmp != NULL){
            printf(" ProcessoID:%d posicao:%d\n", tmp->num,i);
            tmp = tmp->nextptr;
            i++;
        }
    }
}
int alocate_mem (int process_id, int num_units,struct mem_Space *mem){
    struct mem_Space *aux;
    if(mem->nextptr == NULL){
      printf("Algo correu mal\n");
      return -1;
    }
    aux = mem;
    int nodes = 0;
    int counter = 0;
    while(aux != NULL && counter < num_units+1){
      if(aux->num == 0){
        aux->num = process_id;
        counter++;
        printf("counter:%d e process_id:%d\n",counter,aux->num);
      }
      nodes++;
      printf("nodes:%d\n",nodes);
      if(aux->nextptr == NULL){
        printf("Ultimo elemento\n");
      }
      aux = aux->nextptr;
  }
  if(counter == num_units){ 
    mem = aux;
    return nodes;
  }
  return -1;
}

int deallocate_mem(int process_id,struct mem_Space *mem){
  struct mem_Space *aux;
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
int fragment_count (struct mem_Space *mem){
  struct mem_Space *aux = mem;
  int counter = 0,flag_frag = 0;
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