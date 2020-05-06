#include"gestor.h"
int exTime=0;
void percorrerIntrucoesSJF(programa *progAPercorrer){
    int forkjump = 0;
    int forkFlag = 0;
    int pos = 0;
		if(!(strncmp(progAPercorrer->listaDeIntrucoes[progAPercorrer->infoProcesso.PC],"M",strlen("M")))){
            exTime++;
            printf(" Entrei numa instruçao M \n");
            progAPercorrer->infoProcesso.processValue = atoi(strtok(progAPercorrer->listaDeIntrucoes[progAPercorrer->infoProcesso.PC],"M "));
            printf(" Valor do processo: %d\n",progAPercorrer->infoProcesso.processValue); 
        }
		if(!(strncmp(progAPercorrer->listaDeIntrucoes[progAPercorrer->infoProcesso.PC],"A",strlen("A")))){
            exTime++;
            printf(" Entrei numa instruçao A \n");
            progAPercorrer->infoProcesso.processValue += atoi(strtok(progAPercorrer->listaDeIntrucoes[progAPercorrer->infoProcesso.PC],"A "));
            printf(" Valor do processo: %d\n",progAPercorrer->infoProcesso.processValue);
        }
		if(!(strncmp(progAPercorrer->listaDeIntrucoes[progAPercorrer->infoProcesso.PC],"S",strlen("S")))){
            exTime++;
            printf(" Entrei numa instruçao S \n");
            progAPercorrer->infoProcesso.processValue -= atoi(strtok(progAPercorrer->listaDeIntrucoes[progAPercorrer->infoProcesso.PC],"S "));
            printf(" Valor do processo: %d\n",progAPercorrer->infoProcesso.processValue);
        }
            //EXECV()
		if(!(strncmp(progAPercorrer->listaDeIntrucoes[progAPercorrer->infoProcesso.PC],"L",strlen("L")))){
            exTime++;
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
            exTime++;
            printf(" Entrei numa instruçao C \n");
            forkjump = atoi(strtok(progAPercorrer->listaDeIntrucoes[progAPercorrer->infoProcesso.PC],"C "));
            forkFlag = 1;
            filho(*progAPercorrer);
            progAPercorrer->infoProcesso.PC = progAPercorrer->infoProcesso.PC + forkjump;
            printf("VALOR DO PC:%d\n",progAPercorrer->infoProcesso.PC);
        }   //WAITING()
        if(!(strncmp(progAPercorrer->listaDeIntrucoes[progAPercorrer->infoProcesso.PC],"B",strlen("B")))){
            exTime++;
            printf(" Entrei numa instruçao B \n");
            progAPercorrer->estado = 1; //PARADO
            progAPercorrer->infoProcesso.PC++;
            return;
        }
        if (forkFlag) forkFlag = 0;
        else progAPercorrer->infoProcesso.PC++;
        printf(" PC:%d\n",progAPercorrer->infoProcesso.PC);
	                                                         
}
void programaRunnerSjf(programa *listaDeProgramas, int count){ // falta isto comparar o programa com os programas na lista de waiting
  int i=0;
  printf("valor do count:%d\n",count);
  while(i<count){
    
  }
}
void sjf(char *listaDeProgramas){ // não pode se implementado assim e não ponhas const char isso não é sempre igual
    FILE *fp =fopen(listaDeProgramas,"r");
    char *arraydestrings[90];
    char string[80];
    char *e;
    programa listaProgramas[80];
    int num;
    int index;
    int i = 0;
      // ele esta entrar neste if nao sei porque raio (NÂO ta a diferenciar isto nao é o fifo nao faças isto le a parte a abaixo)
    if(fp==NULL){
        perror("Nao existe o ficheiro\n");
    }
    char *** leitura =(char ***)malloc(80*sizeof(char **));
    
    while(fgets(string,sizeof(string),fp)!=0){ // TEM DE SER TODO MODADO ISTO NÂO É O FIFO
        char ** leitura2 = (char **)malloc(80*sizeof(char *));
        processo info;
        e = strchr(string, ' '); // isto é o que premite ler, não o que esta a cima disto
        index=(int)(e-string);
        arraydestrings[i] = strndup(string,sizeof(string));
        arraydestrings[i][index]='\0';
        num = atoi(strtok(e," T:"));
        printf("Arrive:%d\n",num);
        atribuidorDeInstrucoes(arraydestrings[i],leitura2,&info);
        leitura[i] = leitura2;
        free(leitura2);
        //listaProgramas[i]=juntor(num,info,leitura[i]);
        i++;
    }
    programaRunnerSjf(listaProgramas,i);
    printf("precorreu %d programas \n",i);
    free(leitura);
    fclose(fp);
}


