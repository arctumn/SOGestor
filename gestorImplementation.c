#include "gestor.h"
int a=0;
void atribuidorDeInstrucoes(char *nomeFich,char **arrayFinalStrings, processo *processoAtual){ // DEVOLVER OQUE?
    FILE *fp1 = fopen(nomeFich,"r");
    char *arraydestrings[90];
    char string[80];
    int t = 0;
    int i = 0,c = 0,structChecker = 0;
    if (fp1 == NULL){
        perror("NAO EXISTE O FICHEIRO\n");
        return;
    }
    while(fgets(string,sizeof(string),fp1) != 0){
        arraydestrings[i] = strndup(string,sizeof(string));
        i++;
    }
    t = i;
    processoAtual->nome = arraydestrings[0];
    fclose(fp1);
    i=1;
    while(i < t){
        
        if(!(strncmp(arraydestrings[i],"processValue:",strlen("processValue:")))){
            char *processValue = strtok(arraydestrings[i],"processValue:");
            processoAtual->processValue = atoi(processValue);
            structChecker++; 
        }
        if(!(strncmp(arraydestrings[i],"pid:",4))){
            char *npid = strtok(arraydestrings[i],"pid:");
            processoAtual->pid = atoi(npid);
            structChecker++;
        }
        if(!(strncmp(arraydestrings[i],"ppid:",5))){
            char *nppid = strtok(arraydestrings[i],"ppid:");
            processoAtual->ppid = atoi(nppid);
            structChecker++;
        }
        if(!(strncmp(arraydestrings[i],"prioridade:",strlen("prioridade:")))){
            char *prioridade = strtok(arraydestrings[i],"prioridade:");
            processoAtual->prioridade = atoi(prioridade);
            structChecker++;
        }
       if(!(strncmp(arraydestrings[i],"tempoVida:",strlen("tempoVida:")))){
            char *tVida = strtok(arraydestrings[i],"tempoVida:");
            processoAtual->tempoVida = atoi(tVida);
            structChecker++; 
        } 
        if(!(strncmp(arraydestrings[i],"PC:",strlen("PC:")))){
            char *PC = strtok(arraydestrings[i],"PC:");
            processoAtual->PC = atoi(PC);
            structChecker++;
        }
        if(!(strncmp(arraydestrings[i],"I:",strlen("I:")))){
            char *I = strtok(arraydestrings[i],"I:");
            arrayFinalStrings[c] = I;
            c++;
        }
        i++;
    }
    processoAtual->quantidadeDeIntrucoes = c;
    if (structChecker != 6){
        printf("Programa Invalido\n");
        return;
    }
}
programa juntor(int arrivalTime,processo info,char ** listaDeIntrucoesInfo){
    programa associado;
    associado.nomeProg = info.nome;
    associado.infoProcesso = info;
    associado.listaDeIntrucoes = listaDeIntrucoesInfo;
    associado.estado = 0;
    associado.arrivalTime = arrivalTime;
    return associado;
}


void percorrerIntrucoes(programa *progAPercorrer){
    int forkjump = 0;
    int forkFlag = 0;
    int pos = 0;
	while(progAPercorrer->infoProcesso.PC < progAPercorrer->infoProcesso.quantidadeDeIntrucoes){
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
            filho(*progAPercorrer);
            progAPercorrer->infoProcesso.PC = progAPercorrer->infoProcesso.PC + forkjump;
            printf("VALOR DO PC:%d\n",progAPercorrer->infoProcesso.PC);
        }   //WAITING()
        if(!(strncmp(progAPercorrer->listaDeIntrucoes[progAPercorrer->infoProcesso.PC],"B",strlen("B")))){
            printf(" Entrei numa instruçao B \n");
            progAPercorrer->estado = 1; //PARADO
            progAPercorrer->infoProcesso.PC++;
            return;
        }
        if (forkFlag) forkFlag = 0;
        else progAPercorrer->infoProcesso.PC++;
        printf(" PC:%d\n",progAPercorrer->infoProcesso.PC);
	}
    progAPercorrer->estado = 2; //MORTO
}
void filho(programa pai){
    printf(" Entrei no processo filho!\n");
    pai.infoProcesso.PC++;
    percorrerIntrucoes(&pai);
    printf(" Fim do processo filho!\n");
}
void percorrerIntrucoesSJF(programa *progAPercorrer){
    int forkjump = 0;
    int forkFlag = 0;
    int pos = 0;
		if(!(strncmp(progAPercorrer->listaDeIntrucoes[progAPercorrer->infoProcesso.PC],"M",strlen("M")))){
            a++;
            printf(" Entrei numa instruçao M \n");
            progAPercorrer->infoProcesso.processValue = atoi(strtok(progAPercorrer->listaDeIntrucoes[progAPercorrer->infoProcesso.PC],"M "));
            printf(" Valor do processo: %d\n",progAPercorrer->infoProcesso.processValue); 
        }
		if(!(strncmp(progAPercorrer->listaDeIntrucoes[progAPercorrer->infoProcesso.PC],"A",strlen("A")))){
            a++;
            printf(" Entrei numa instruçao A \n");
            progAPercorrer->infoProcesso.processValue += atoi(strtok(progAPercorrer->listaDeIntrucoes[progAPercorrer->infoProcesso.PC],"A "));
            printf(" Valor do processo: %d\n",progAPercorrer->infoProcesso.processValue);
        }
		if(!(strncmp(progAPercorrer->listaDeIntrucoes[progAPercorrer->infoProcesso.PC],"S",strlen("S")))){
            a++;
            printf(" Entrei numa instruçao S \n");
            progAPercorrer->infoProcesso.processValue -= atoi(strtok(progAPercorrer->listaDeIntrucoes[progAPercorrer->infoProcesso.PC],"S "));
            printf(" Valor do processo: %d\n",progAPercorrer->infoProcesso.processValue);
        }
            //EXECV()
		if(!(strncmp(progAPercorrer->listaDeIntrucoes[progAPercorrer->infoProcesso.PC],"L",strlen("L")))){
            a++;
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
            a++;
            printf(" Entrei numa instruçao C \n");
            forkjump = atoi(strtok(progAPercorrer->listaDeIntrucoes[progAPercorrer->infoProcesso.PC],"C "));
            forkFlag = 1;
            filho(*progAPercorrer);
            progAPercorrer->infoProcesso.PC = progAPercorrer->infoProcesso.PC + forkjump;
            printf("VALOR DO PC:%d\n",progAPercorrer->infoProcesso.PC);
        }   //WAITING()
        if(!(strncmp(progAPercorrer->listaDeIntrucoes[progAPercorrer->infoProcesso.PC],"B",strlen("B")))){
            a++;
            printf(" Entrei numa instruçao B \n");
            progAPercorrer->estado = 1; //PARADO
            progAPercorrer->infoProcesso.PC++;
            return;
        }
        if((a=20)){//o 20 vai ser o numero que vamos ler do ficheiro so que nao estou a conseguir ler
            printf("vou parar o programa");
            progAPercorrer->estado =1;//estado WAITING
          return;
        }
        if (forkFlag) forkFlag = 0;
        else progAPercorrer->infoProcesso.PC++;
        printf(" PC:%d\n",progAPercorrer->infoProcesso.PC);
	
    progAPercorrer->estado = 2; //MORTO
}
void programaRunnerFifo(char *nomeDoPrograma){ // FIFO
    char ** leitura =(char **)malloc(80*sizeof(char *));
    processo A;
    programa AB;
    atribuidorDeInstrucoes(nomeDoPrograma,leitura,&A);
    AB = juntor(0,A,leitura);
    printf("\n");
    printf("Info do processo ->\n");
    printf(" nome:%s pid:%d\n ppid:%d\n prioridade:%d\n tempo de vida:%d\n PC:%d\n processValue:%d\n Quantidade de intruçoes:%d\n",A.nome,A.pid,A.ppid,A.prioridade,A.tempoVida,A.PC,A.processValue,A.quantidadeDeIntrucoes);
    printf("Execução do processo ->\n");
    percorrerIntrucoes(&AB);
    free(leitura);
    printf(" Counter: %d \nFim do programa:%s\n",AB.infoProcesso.PC,AB.nomeProg);
}
void fifo(const char *listaDeProgramas){
    FILE *fp =fopen(listaDeProgramas,"r");
    char *arraydestrings[90];
    char string[80];
    char *e;
    int index;
    int i = 0;
    if (fp == NULL){
        perror("NAO EXISTE O FICHEIRO\n");
        return;
    }
    while(fgets(string,sizeof(string),fp) != 0){
        e = strchr(string, ' ');
        index = (int)(e - string);
        arraydestrings[i] = strndup(string,sizeof(string));
        arraydestrings[i][index] = '\0';
        printf("%s",arraydestrings[i]);
        programaRunnerFifo(arraydestrings[i]);
        i++;
    }
    printf("Precorreu %d programas\n",i);
    fclose(fp);
}
void programaRunnerSjf(char *nomeDoPrograma,int num){ //isto nao vai ser implementado assim pois isso não permite fazer trocas de programas
  char ** leitura =(char **)malloc(80*sizeof(char *));
    processo A;
    programa AB;
    atribuidorDeInstrucoes(nomeDoPrograma,leitura,&A);
    //AB = juntor(A,leitura); não funciona assim falta o argumento arrival time
    printf("\n");
    printf("Info do processo ->\n");
    printf(" nome:%s pid:%d\n ppid:%d\n prioridade:%d\n tempo de vida:%d\n PC:%d\n processValue:%d\n Quantidade de intruçoes:%d\n",A.nome,A.pid,A.ppid,A.prioridade,A.tempoVida,A.PC,A.processValue,A.quantidadeDeIntrucoes);
    printf("Execução do processo ->\n");
    percorrerIntrucoes(&AB);
    free(leitura);
    printf(" Counter: %d \nFim do programa:%s\n",AB.infoProcesso.PC,AB.nomeProg);

}

void sjf(const char *listaDeProgramas){ // não pode se implementado assim e não ponhas const char isso não é sempre igual
    FILE *fp =fopen(listaDeProgramas,"r");
    char *arraydestrings[90];
    char string[80];
    char *e;
    int num;
    int index;
    int i = 0;
      // ele esta entrar neste if nao sei porque raio (NÂO ta a diferenciar isto nao é o fifo nao faças isto le a parte a abaixo)
    if(fp==NULL){
        perror("Nao existe o ficheiro\n");
    }
    while(fgets(string,sizeof(string),fp)!=0){ // TEM DE SER TODO MODADO ISTO NÂO É O FIFO
        e = strchr(string, ' '); // isto é o que premite ler, não o que esta a cima disto
        num=atoi(strtok(string,"e "));   // como é que meto isto a ler o numero é dessa forma mas acho que estas a procurar isso mal
        index=(int)(e-string);
        arraydestrings[i] = strndup(string,sizeof(string));  //poe uma instrução no maximo numa linha não ponhas duas
        arraydestrings[i][index]='\0';
        printf("%s",arraydestrings[i]);
        programaRunnerSjf(arraydestrings[i],num); // isto não vai ser implementado assim, vamos ter de alterar isto
        i++;
    }
    printf("precorreu %d programas \n",i);
    fclose(fp);
}
int Strlen(const char *string){
    int i = 0;
    while(string[i] != '\0') i++;
    return i;
}
void strfind(const char*string,char charProcuravel,int *pos){ //remover isto é inutil
    int i = 0;
    while(string[i] != charProcuravel) {
        if(string[i] == '\0') {
            *pos = -1;
            return;
        }
        i++;
        }
    *pos = i;
}