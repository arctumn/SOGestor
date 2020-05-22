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