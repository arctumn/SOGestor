#include "gestor.h"
void atribuidorDeInstrucoes(char *nomeFich,char **arrayFinalStrings, processo *processoAtual){ // DEVOLVER OQUE?
    FILE *fp1 = fopen(nomeFich,"r");
    char *arraydestrings[90];
    char string[80];
    size_t t = 0;
    processoAtual->programMemory = 0;
    size_t i = 0,c = 0,structChecker = 0;
    if (fp1 == NULL){
        perror(" NAO EXISTE O FICHEIRO\n");
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
            int numalea = rand()%10;
            while(numalea<3 || numalea>10)
            numalea = rand()%10;
            processoAtual->programMemory+=numalea;
            c++;
        }
        i++;
    }
    processoAtual->quantidadeDeIntrucoes = c;
    if (structChecker != 6){
        printf(" Programa Invalido\n");
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
            printf(" VALOR DO PC:%d\n",progAPercorrer->infoProcesso.PC);
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

void programaRunnerFifo(char *nomeDoPrograma){ // FIFO
    char ** leitura =(char **)malloc(80*sizeof(char *));

    struct mem_Space *headFifo = calloc(1,sizeof(struct mem_Space));

    processo A;
    programa AB;
    atribuidorDeInstrucoes(nomeDoPrograma,leitura,&A);
    AB = juntor(0,A,leitura);
    
    //memOPERATIONS
    int verify = alocate_mem(AB.infoProcesso.pid, AB.infoProcesso.programMemory, headFifo);
    if(verify == -1) printf(" Erro alocar na memoria!\n");
      
    //Execution
    printf("\n");
    printf(" Info do processo ->\n");
    printf(" nome:%s pid:%d\n ppid:%d\n prioridade:%d\n tempo de vida:%d\n PC:%d\n processValue:%d\n Quantidade de intruçoes:%d Memoria do Programa:%d \n",A.nome,A.pid,A.ppid,A.prioridade,A.tempoVida,A.PC,A.processValue,A.quantidadeDeIntrucoes,A.programMemory);
    printf(" Execução do processo ->\n");
    percorrerIntrucoes(&AB);
    //
    int fragmentos = fragment_count(headFifo);

    //memDeALLOC
     deallocate_mem(A.pid,headFifo);
    if(verify == -1) printf(" Erro a remover memoria associada\n");
    
    //fim deste programa
    free(leitura);
    printf("\n-------------------\n\nFragmentos: %d Counter: %d \nFim do programa:%s\n-----------------\n",fragmentos,AB.infoProcesso.PC,AB.nomeProg);
    free(headFifo);
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
    printf(" Precorreu %d programas\n",i);
    fclose(fp);
}

int Strlen(const char *string){
    int i = 0;
    while(string[i] != '\0') i++;
    return i;
}

void strfind(const char*string,char charProcuravel,int *pos){ 
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