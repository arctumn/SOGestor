#include "gestor.h"

//----------------------------------------------------------------------------------------------------------------------------------------
//Authors: Pedro Lopes, Luís do Espirito Santo, Pedro Carrasco, Afonso Simões
//Program that simmulates Escalonation of processes
//The program is in the portuguese language as it was part of the University course:"Sistemas Operativos"(Operative Systems) Second Semmester
//The Documentation is also in portuguese
//----------------------------------------------------------------------------------------------------------------------------------------
int memory = 100;
// AINDA NÃO ESTA IMPLEMENTADO
// PARA TESTAR ALGO COMENTAR NA FORMA /**/  ESTE MAIN 
int main(){
  int verify = 0;
  struct mem_Space *head = malloc(sizeof(struct mem_Space));
  head = createList(memory,head);
  PrintList(head);
  if(head->nextptr == NULL){
    printf("ERRO NA LISTA\n");
  }
  verify = alocate_mem(5, 30, head);
  if(verify != -1){
    printf("Percorreu%d nos\n",verify);
    PrintList(head);
  }
  else printf("Erro a alocar memoria\n");
  

  
}
/*
int main(){
    int option;
    printf("Escolha um metodo para percorrer os programas\n");
    printf("1 -> Metodo FIFO\n");
    printf("2 -> Metodo Priority (Preemptive) \n");
    scanf("%d",&option);
    switch (option){
    case 1:
       fifo("lista.txt");
        break;
    case 2:
        priority("lista.txt");// por implementar
    default: //qualquer outra tecla  fecha o programa o exit fora deste switch não tem sentido
        exit(0);
        break;
    }
    //exit(0); isto era inutil porque o default nunca iria permitir que isto va acontecer
}
*/