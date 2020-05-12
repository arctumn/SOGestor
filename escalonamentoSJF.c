#include"gestor.h"
int exTime=0;
void percorrerIntrucoesSJF(programa *progAPercorrer){
    int forkjump = 0;
    int forkFlag = 0;
    int pos = 0;
		if(!(strncmp(progAPercorrer->listaDeIntrucoes[progAPercorrer->infoProcesso.PC],"M",strlen("M")))){
      
            printf(" Entrei numa instruçao M \n");
            progAPercorrer->infoProcesso.processValue = atoi(strtok(progAPercorrer->listaDeIntrucoes[progAPercorrer->infoProcesso.PC],"M "));
            printf(" Valor do processo: %d\n",progAPercorrer->infoProcesso.processValue); 
        }
		if(!(strncmp(progAPercorrer->listaDeIntrucoes[progAPercorrer->infoProcesso.PC],"A",strlen("A")))){

            printf(" Entrei numa instruçao A \n");
            progAPercorrer->infoProcesso.processValue += atoi(strtok(progAPercorrer->listaDeIntrucoes[progAPercorrer->infoProcesso.PC],"A "));
            printf(" Valor do processo: %d\n",progAPercorrer->infoProcesso.processValue);
        }
		if(!(strncmp(progAPercorrer->listaDeIntrucoes[progAPercorrer->infoProcesso.PC],"S",strlen("S")))){

            printf(" Entrei numa instruçao S \n");
            progAPercorrer->infoProcesso.processValue -= atoi(strtok(progAPercorrer->listaDeIntrucoes[progAPercorrer->infoProcesso.PC],"S "));
            printf(" Valor do processo: %d\n",progAPercorrer->infoProcesso.processValue);
        }
            //EXECV()
		if(!(strncmp(progAPercorrer->listaDeIntrucoes[progAPercorrer->infoProcesso.PC],"L",strlen("L")))){

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
        if(!(strncmp(progAPercorrer->listaDeIntrucoes[progAPercorrer->infoProcesso.PC],"C",strlen("C")))){

            printf(" Entrei numa instruçao C \n");
            forkjump = atoi(strtok(progAPercorrer->listaDeIntrucoes[progAPercorrer->infoProcesso.PC],"C "));
            forkFlag = 1;
            //filho(*progAPercorrer);
            progAPercorrer->infoProcesso.PC = progAPercorrer->infoProcesso.PC + forkjump;
            exTime+= forkjump;
        }   //WAITING()
        if(!(strncmp(progAPercorrer->listaDeIntrucoes[progAPercorrer->infoProcesso.PC],"B",strlen("B")))){

            printf(" Entrei numa instruçao B \n");
            progAPercorrer->estado = 1; //PARADO
        }
        if (forkFlag) forkFlag = 0;
        else {progAPercorrer->infoProcesso.PC++;exTime++;}
        printf(" PC:%d\n",progAPercorrer->infoProcesso.PC);
      
	                                                         
}
void programaRunnerSjf(programa *listaDeProgramas, int count){ // falta isto comparar o programa com os programas na lista de waiting
//1-processo 3.... 2-processo 1.... 3-processo 4
  int i=0;
  int j=0;
  int z = 0;
  int h = 0;
  int t;
  programa espera[80];
  printf("valor do count:%d\n",count);
  while(listaDeProgramas[i].nomeProg !=NULL){
    int alea=rand()%100;
    if(listaDeProgramas[i+1].arrivalTime == exTime && listaDeProgramas[i].infoProcesso.prioridade>listaDeProgramas[i+1].infoProcesso.prioridade){        
      printf("Menor prioridade\n");
          
          espera[t] = listaDeProgramas[i];
          while(listaDeProgramas[h].nomeProg !=NULL) {
            listaDeProgramas[h] = listaDeProgramas[h+1];
            h++;
            }
        while(espera[z].nomeProg!=NULL){
          z = 0;
          printf("entrei no while do espera\n");
          printf("z=%d\n",z);
            if(espera[z].infoProcesso.prioridade>listaDeProgramas[i+1].infoProcesso.prioridade){
              printf("pus o gajo em espera a executar\n");
              programa p = listaDeProgramas[i];
              listaDeProgramas[i]=espera[z];
              espera[z]=p;
              espera[z+1]=listaDeProgramas[i+1];
              percorrerIntrucoesSJF(&listaDeProgramas[i]);
            }

           z++;
          }
          t++;
        } // depois disto percorrer as instruções de i+1
      while(1){
        
        if(listaDeProgramas[i].listaDeIntrucoes == NULL){
            listaDeProgramas[i].estado = 2;
            break;
        }
        if(listaDeProgramas[i+1].arrivalTime == exTime) break;
        percorrerIntrucoesSJF(&listaDeProgramas[i]);
        exTime += listaDeProgramas[i].infoProcesso.PC;
      }
   
    if(listaDeProgramas[i].estado == 2) i++;
  }
}
void sjf(char *listaDeProgramas){ // não pode se implementado assim e não ponhas const char isso não é sempre igual
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
    char *** leitura =(char ***)malloc(80*sizeof(char **));
    
    while(fgets(string,sizeof(string),fp)!=0){ // TEM DE SER TODO MODADO ISTO NÂO É O FIFO
        char ** leitura2 = (char **)malloc(80*sizeof(char *));
        processo info;
        e = strchr(string, ' '); // isto é o que premite ler, não o que esta a cima disto
        index=(int)(e-string);
        arraydestrings[i] =strndup(string,sizeof(string));
        arraydestrings[i][index]='\0';
        num = atoi(strtok(e," T:"));
        printf("Arrive:%d\n",num);
        atribuidorDeInstrucoes(arraydestrings[i],leitura2,&info);
        leitura[i] = leitura2;
        listaProgramas[i]=juntor(num,info,leitura[i]);
        i++;
    }
    programaRunnerSjf(listaProgramas,i);
    printf("precorreu %d programas \n",i);
    free(leitura);
    free(listaProgramas);
    fclose(fp);
}


