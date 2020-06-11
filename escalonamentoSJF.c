#include"gestor.h"
int exTime=0;

pthread_t thread1,thread2;
int procuraPidLista(int b, int *lista){
  int i;
  for(i = 0; lista[i] != 0; i++){
    if(lista[i] == b)
      return i;
    }
  return -1;
}

void percorrerIntrucoesPriority(programa *progAPercorrer){
    int forkjump = 0;
    int forkFlag = 0;
    int pos = 0;
    printf("sou a string:%s",progAPercorrer->listaDeIntrucoes[progAPercorrer->infoProcesso.PC]);
    if(progAPercorrer->listaDeIntrucoes[progAPercorrer->infoProcesso.PC+1] == NULL){
      progAPercorrer->estado = 2;
      return;
    }
	    	if(!(strncmp(progAPercorrer->listaDeIntrucoes[progAPercorrer->infoProcesso.PC],"M",strlen("M")))){
      
            printf(" Entrei numa instruçao M \n");
            progAPercorrer->infoProcesso.processValue = atoi(strtok(progAPercorrer->listaDeIntrucoes[progAPercorrer->infoProcesso.PC],"M "));
            printf(" Valor do processo: %d\n",progAPercorrer->infoProcesso.processValue); 
        }
		else if(!(strncmp(progAPercorrer->listaDeIntrucoes[progAPercorrer->infoProcesso.PC],"A",strlen("A")))){

            printf(" Entrei numa instruçao A \n");
            progAPercorrer->infoProcesso.processValue += atoi(strtok(progAPercorrer->listaDeIntrucoes[progAPercorrer->infoProcesso.PC],"A "));
            printf(" Valor do processo: %d\n",progAPercorrer->infoProcesso.processValue);
        }
		else if(!(strncmp(progAPercorrer->listaDeIntrucoes[progAPercorrer->infoProcesso.PC],"S",strlen("S")))){

            printf(" Entrei numa instruçao S \n");
            progAPercorrer->infoProcesso.processValue -= atoi(strtok(progAPercorrer->listaDeIntrucoes[progAPercorrer->infoProcesso.PC],"S "));
            printf(" Valor do processo: %d\n",progAPercorrer->infoProcesso.processValue);
        }
            //EXECV()
		else if(!(strncmp(progAPercorrer->listaDeIntrucoes[progAPercorrer->infoProcesso.PC],"L",strlen("L")))){

            printf(" Entrei numa instruçao L \n");
            char *nome = strtok(progAPercorrer->listaDeIntrucoes[progAPercorrer->infoProcesso.PC],"L ");
            strfind(nome,'\n',&pos);
            if(nome[pos-1] == '\r') nome[pos-1] = '\0';
            else nome[pos] = '\0';   
            printf(" Novo nome:%s",nome);
            progAPercorrer->infoProcesso.nome = nome;
            progAPercorrer->nomeProg = progAPercorrer->infoProcesso.nome;
            //CASO SEJA UM PROCESSO FILHO
            if(progAPercorrer->infoProcesso.ppid != 1){ 
            int aux = progAPercorrer->infoProcesso.pid;
            atribuidorDeInstrucoes(nome,progAPercorrer->listaDeIntrucoes,&progAPercorrer->infoProcesso);
            progAPercorrer->infoProcesso.ppid = aux;
            }
            //NÂO SEJA FILHO
            else  atribuidorDeInstrucoes(progAPercorrer->infoProcesso.nome,progAPercorrer->listaDeIntrucoes,&progAPercorrer->infoProcesso);
        }
        
            //FORK()
        else if(!(strncmp(progAPercorrer->listaDeIntrucoes[progAPercorrer->infoProcesso.PC],"C",strlen("C")))){

            printf(" Entrei numa instruçao C \n");
            forkjump = atoi(strtok(progAPercorrer->listaDeIntrucoes[progAPercorrer->infoProcesso.PC],"C "));
            forkFlag = 1;
            printf("valor do forkjump:%d\n",forkjump);
            //filho(*progAPercorrer);
            pthread_create(&thread1,NULL,filhoThread,(void *)progAPercorrer);
            progAPercorrer->infoProcesso.PC += forkjump;
            
            exTime+= forkjump;
        }   //WAITING()
        else if(!(strncmp(progAPercorrer->listaDeIntrucoes[progAPercorrer->infoProcesso.PC],"B",strlen("B")))){

            printf(" Entrei numa instruçao B \n");
            progAPercorrer->estado = 1; //PARADO
        }
        else progAPercorrer->estado = 2;
        if (forkFlag) forkFlag = 0;
        else {progAPercorrer->infoProcesso.PC++;exTime++;}
        printf(" PC:%d\n",progAPercorrer->infoProcesso.PC);
      



}
void programaRunnerPriority(programa *listaDeProgramas, int count){ // falta isto comparar o programa com os programas na lista de waiting
//1-processo 3.... 2-processo 1.... 3-processo 4
  int i=0;
  int j=0;
  int z = 0;
  int h = 0;
  int t;
  int b;
  int que;
  int memovalues = 0;
  int pidsEmUso[1000];
  int alias=rand()%100;
  programa espera[80];


  struct mem_Space *head = calloc(1,sizeof(struct mem_Space));
  head = createList(MEMORY, head);

   int verify = alocate_mem(listaDeProgramas[0].infoProcesso.pid, listaDeProgramas[0].infoProcesso.programMemory, head);
    if(verify == -1) printf("\n\n------------------\nErro a alocar memoria\n------------------\n\n");
    pidsEmUso[0] = listaDeProgramas[0].infoProcesso.pid;
    memovalues++;
  printf("valor do count:%d\n",count);

  while(listaDeProgramas[i].nomeProg != NULL){
    printf("\n\n\n\nSou o programa:%s\n\nmemovalues:%d\n\n",listaDeProgramas[i].nomeProg,memovalues);
    
   



    if(procuraPidLista(listaDeProgramas[i].infoProcesso.pid, pidsEmUso) == -1){
    memovalues++;
     verify = alocate_mem(listaDeProgramas[i].infoProcesso.pid, listaDeProgramas[i].infoProcesso.programMemory, head);
    if(verify == -1) printf("\n\n------------------\nErro a alocar memoria\n------------------\n\n");
    pidsEmUso[memovalues] = listaDeProgramas[i].infoProcesso.pid;
    //break;
    }
    if(listaDeProgramas[i+1].arrivalTime == exTime){

      verify = alocate_mem(listaDeProgramas[i+1].infoProcesso.pid, listaDeProgramas[i+1].infoProcesso.programMemory, head);
    if(verify == -1) printf("\n\n------------------\nErro a alocar memoria\n------------------\n\n");
    pidsEmUso[memovalues] = listaDeProgramas[memovalues].infoProcesso.pid;

      if(listaDeProgramas[i].infoProcesso.prioridade < listaDeProgramas[i+1].infoProcesso.prioridade || (listaDeProgramas[i].nomeProg==NULL && espera[0].nomeProg!=NULL) ){

      printf("-----------------\nMenor prioridade\n-----------------\n");


        if(listaDeProgramas[i].nomeProg!=NULL)
          espera[t] = listaDeProgramas[i];
        
          while(listaDeProgramas[h].nomeProg !=NULL) {
            
            printf("\nEntrei no avançar\n");

            printf("Antes nome:%s\n",listaDeProgramas[h].nomeProg);
            listaDeProgramas[h] = listaDeProgramas[h+1];
            printf("Depois nome:%s\n",listaDeProgramas[h].nomeProg);

            h++;
            }
            
             z = 0;
            
        while(espera[z].nomeProg != NULL){

          printf("\nentrei no while do espera\n");
          printf("z=%d\n",z);
          printf("lista de espera %s\n",espera[z].nomeProg);

            if(espera[z].infoProcesso.prioridade>listaDeProgramas[i].infoProcesso.prioridade){

              //printf("pus o programa em espera a executar\n");

              programa p = listaDeProgramas[i];
              listaDeProgramas[i]=espera[z];
              espera[z]=p;
              b = 0;

              while(listaDeProgramas[b].nomeProg != NULL){
                 printf("\nPrograma:%s na pos:%d\n",listaDeProgramas[b].nomeProg,b);
                 b++;
              }
            }

           z++;
          }
          t++;
        } // depois disto percorrer as instruções de i+1
       else{
          espera[z]=listaDeProgramas[i+1];
          while(listaDeProgramas[h].nomeProg !=NULL) {
          listaDeProgramas[h] = listaDeProgramas[h+1];
          h++;
          }
        }
      }
      b = 0;

      if(listaDeProgramas[i+1].nomeProg == NULL){
        if(listaDeProgramas[i].infoProcesso.prioridade > espera[0].infoProcesso.prioridade){
          programa aux = espera[0];
          espera[0] = listaDeProgramas[i];
          listaDeProgramas[i] = aux;
        }
      }
      if(alias>70) {
        printf("Sou o programa na lista de espera:%s\n",espera[0].nomeProg);
        percorrerIntrucoesPriority(&espera[0]);
        exTime += espera[0].infoProcesso.PC;
        
        //dealloc
        if(espera[0].estado == 2){
          que = procuraPidLista(listaDeProgramas[i].infoProcesso.pid,pidsEmUso);
          if(que != -1) pidsEmUso[que] = -30;
          verify = -50;
          verify = deallocate_mem(espera[0].infoProcesso.pid, head);
          if(verify == -1) 
            printf("\n\nErro a desalocar memoria lista de espera\n\n");
        }
      }

      b = 0;
      
      while(1){
        printf("\n\nmemovalues = %d\nvalor de i = %d\n",memovalues,i);
        //fragment counter
        int fragment = fragment_count(head);
        printf("\n---------------\nnumero de fragmentos aqui: %d\n---------------\n\n",fragment);
        
        //continuacao
        if(memovalues > 0){
          if(procuraPidLista(listaDeProgramas[i].infoProcesso.pid,pidsEmUso) == -1){
            
            //alloc
            verify = -50;
            verify = alocate_mem(
              listaDeProgramas[i].infoProcesso.pid,
              listaDeProgramas[i].infoProcesso.quantidadeDeIntrucoes,
              head);
            if(verify == -1) 
              printf("Erro a alocar memoria no programa %s\n",listaDeProgramas[i].nomeProg);
            pidsEmUso[memovalues] = listaDeProgramas[i].infoProcesso.pid;
          }
        }
          
        

        printf("Sou o programa:%s\n",listaDeProgramas[i].nomeProg);   
        if(listaDeProgramas[i].estado == 2){

          //dealloc
          que = procuraPidLista(listaDeProgramas[i].infoProcesso.pid,pidsEmUso);
          printf("Valor de que:%d\n",que);
          if(pidsEmUso[que] != listaDeProgramas[i].infoProcesso.pid){
            printf("\n---ERRO---\n");
          }
          if(que != -1) pidsEmUso[que] = -30;
          
           
          verify = deallocate_mem(listaDeProgramas[i].infoProcesso.pid, head);
          if(verify == -1) printf("\n------------------\nErro a desalocar memoria\n------------------\n");

          //continuacao
          if(listaDeProgramas[i+1].nomeProg == NULL){
            while(espera[0].estado != 2 && espera[0].nomeProg != NULL) {
              printf("Sou o programa:%s\n",espera[0].nomeProg);
              percorrerIntrucoesPriority(&espera[0]);
            }
            
            //dealloc
            if(!head) printf("FIM DA LISTA\n");

        
            que = procuraPidLista(espera[0].infoProcesso.pid, pidsEmUso);
            pidsEmUso[que] = -30;
            
              
        
            printf("Acabei o programa %s",espera[0].nomeProg);

            verify = -50;
            printf("valor do pid:%d\n",espera[0].infoProcesso.pid);
            verify = deallocate_mem(espera[0].infoProcesso.pid, head);
            if(verify == -1) 
              printf("\n\n------------------\nErro a desalocar memoria\n------------------\n\n");

            
          }
          //adicionar caso em que o programo morre aos 4 seg mas o outro so chega aos 7 , temos de ir ver a lista de espera
          printf("\nAcabei Este programa: %s\n\n",listaDeProgramas[i].nomeProg);
          i++;
          break;
        }
        
        if(listaDeProgramas[i+1].arrivalTime == exTime){
           break;
           }
        percorrerIntrucoesPriority(&listaDeProgramas[i]);
        exTime += listaDeProgramas[i].infoProcesso.PC;
      }
      int fragment = fragment_count(head);
        printf("\n---------------\nnumero de fragmentos aqui: %d\n---------------\n\n",fragment);
    //PrintList(head);
    free(head);
  }
}
void priority(char *listaDeProgramas){ // não pode se implementado assim e não ponhas const char isso não é sempre igual
    FILE *fp =fopen(listaDeProgramas,"r");
    char *arraydestrings[90];
    char string[80];
    char *e;
    programa *listaProgramas=(programa *)calloc(80,sizeof(programa));
    int num;
    int index;
    int i = 0;
      // ele esta entrar neste ao é o fifo nao faças isto le a parte a abaixo)
    if(fp==NULL){
        perror("Nao existe o ficheiro\n");
    }
    char *** leitura =(char ***)calloc(80,sizeof(char **));
    
    while(fgets(string,sizeof(string),fp)!=0){ // TEM DE SER TODO MODADO ISTO NÃO É O FIFO
        char ** leitura2 = (char **)calloc(80,sizeof(char *));
        processo info;
        e = strchr(string, ' '); // isto é o que premite ler, não o que esta a cima disto
        index=(int)(e-string);
        arraydestrings[i] =strndup(string,sizeof(string));
        arraydestrings[i][index]='\0';
        num = atoi((const char *)strtok(e," T:"));
        printf("Arrive:%d\n",num);
        atribuidorDeInstrucoes(arraydestrings[i],leitura2,&info);
        leitura[i] = leitura2;
        listaProgramas[i]=juntor(num,info,leitura[i]);
        i++;
    }
    programaRunnerPriority(listaProgramas,i);
    if (thread2 != 0){
    pthread_join(thread2,NULL);
    }
    if(thread1 != 0){
    pthread_join(thread1,NULL);
    }
    printf("\n\n-------------------\nprecorreu %d programas\n-------------------\n\n",i);
    free(leitura);
    free(listaProgramas);
    fclose(fp);
}

void *filhoThread(void *pai){
    if(pai == NULL){
      printf("ERRO programa não existe\n");
      return NULL;
    }
    printf(" Entrei no processo filho!\n\n\n");
    programa *paiF = pai;
    paiF->infoProcesso.PC++;
    percorrerIntrucoesThread(paiF);
    return NULL;
}

void percorrerIntrucoesThread(programa *progAPercorrer){
    int forkjump = 0;
    int forkFlag = 0;
    int pos = 0;
	while(progAPercorrer->infoProcesso.PC < progAPercorrer->infoProcesso.quantidadeDeIntrucoes){
		if(!(strncmp(progAPercorrer->listaDeIntrucoes[progAPercorrer->infoProcesso.PC],"M",strlen("M")))){
            progAPercorrer->infoProcesso.processValue = atoi(strtok(progAPercorrer->listaDeIntrucoes[progAPercorrer->infoProcesso.PC],"M "));
        }
		if(!(strncmp(progAPercorrer->listaDeIntrucoes[progAPercorrer->infoProcesso.PC],"A",strlen("A")))){      
            progAPercorrer->infoProcesso.processValue += atoi(strtok(progAPercorrer->listaDeIntrucoes[progAPercorrer->infoProcesso.PC],"A "));    
        }
		if(!(strncmp(progAPercorrer->listaDeIntrucoes[progAPercorrer->infoProcesso.PC],"S",strlen("S")))){ 
            progAPercorrer->infoProcesso.processValue -= atoi(strtok(progAPercorrer->listaDeIntrucoes[progAPercorrer->infoProcesso.PC],"S ")); 
        }
            //EXECV()
		if(!(strncmp(progAPercorrer->listaDeIntrucoes[progAPercorrer->infoProcesso.PC],"L",strlen("L")))){ 
            char *nome = strtok(progAPercorrer->listaDeIntrucoes[progAPercorrer->infoProcesso.PC],"L ");
            strfind(nome,'\n',&pos);
            if(nome[pos-1] == '\r') nome[pos-1] = '\0';
            else nome[pos] = '\0';   
            progAPercorrer->infoProcesso.nome = nome;
            progAPercorrer->nomeProg = progAPercorrer->infoProcesso.nome;
            //CASO SEJA UM PROCESSO FILHO
            if(progAPercorrer->infoProcesso.ppid != 1){ 
            int aux = progAPercorrer->infoProcesso.pid;
            atribuidorDeInstrucoes(nome,progAPercorrer->listaDeIntrucoes,&progAPercorrer->infoProcesso);
            progAPercorrer->infoProcesso.ppid = aux;
            }
            //NÂO SEJA FILHO
            else  atribuidorDeInstrucoes(progAPercorrer->infoProcesso.nome,progAPercorrer->listaDeIntrucoes,&progAPercorrer->infoProcesso);
        }
            //FORK()
        if(!(strncmp(progAPercorrer->listaDeIntrucoes[progAPercorrer->infoProcesso.PC],"C",strlen("C")))){
            forkjump = atoi(strtok(progAPercorrer->listaDeIntrucoes[progAPercorrer->infoProcesso.PC],"C "));
            forkFlag = 1;
            pthread_create(&thread2,NULL,filhoThread,(void *)progAPercorrer);
            progAPercorrer->infoProcesso.PC = progAPercorrer->infoProcesso.PC + forkjump;
        }   //WAITING()
        if(!(strncmp(progAPercorrer->listaDeIntrucoes[progAPercorrer->infoProcesso.PC],"B",strlen("B")))){
            progAPercorrer->estado = 1; //PARADO
            progAPercorrer->infoProcesso.PC++;
            return;
        }
        if (forkFlag) forkFlag = 0;
        else progAPercorrer->infoProcesso.PC++;
	}
    progAPercorrer->estado = 2; //MORTO
    //printf("nome do filho:%s valor final do ProcessCounter %d\n",progAPercorrer->nomeProg,progAPercorrer->infoProcesso.PC);
}
































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































