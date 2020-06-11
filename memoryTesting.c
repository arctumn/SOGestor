#include "gestor.h"


int tamOcupado(int *b){
  int c = 0;
  for(int i = 0; b[i] != 0;i++) c++;
  return c;
}

void memoryTest(){
  int MEMORYTEST = 1000;
  struct mem_Space *headTest = calloc(1,sizeof(struct mem_Space));
  int c = 0;
  int  *pidsEMUSO = calloc(10000,sizeof(int));

  int randALLOC = 0, randDEALLOC = 0;
  srand(2);

  int verify_alloc = 0,verify_dealloc = 0;
  int count1_success = 0,count1_fail = 0,count2_success = 0,count2_fail = 0;

  int frag = 0;
  
  headTest = createList(MEMORYTEST, headTest);
  
  for(int i = 1; i < 10000+1; i++){
    //alocBLOCK
    randALLOC = rand() % 3;
    verify_alloc = alocate_memTest(i, randALLOC, headTest);
    if(verify_alloc != -1) {count1_success++; pidsEMUSO[i] = randALLOC;}
    else count1_fail++;

    frag += fragment_count(headTest);
    //dealocBLOCK
     //caso onde não foram feitos allocs
    
  }
  while(c < count1_success){
    randDEALLOC = (rand() % count1_success)+1;

    verify_dealloc = deallocate_mem(randDEALLOC, headTest);
    if(verify_dealloc == -1) count2_fail++;
    else {
      count2_success++;
      frag += fragment_count(headTest);
      }
    
    c++; 
  }
  

  printf("\n\n-----------------TABELA-----------------\n\n");
  printf("Sucessos a alocar memoria:%d\tFalhas a alocar memoria:%d\n",count1_success,count1_fail);
  printf("Sucessos a dealocar memoria:%d\tFalhas a dealocar memoria:%d\n",count2_success,count2_fail);
  printf("Numero de fragmentos:%d",frag);
  printf("\n\n-----------------FIMTABELA-----------------\n\n");
  //PrintList(headTest);
  //free(pidsEMUSO);
  free(headTest);
}

/*
Gere 10.000 solicitações usando o componente de geração de solicitações e, para cada solicitação, chame a função apropriada do componente de Memória para cada técnica de alocação / de-alocação de memória. Após cada solicitação, atualize os três parâmetros de desempenho para cada uma das técnicas.
O componente de relatório estatístico imprimirá o valor dos três parâmetros para todas as quatro técnicas no final.
*/