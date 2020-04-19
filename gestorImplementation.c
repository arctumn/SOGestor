#include "gestor.h"

void atribuidorDeInstrucoes(char *nomeFich,char **arrayFinalStrings, processo *processoAtual){ // DEVOLVER OQUE?
    FILE *fp1 = fopen(nomeFich,"r");
    char *arraydestrings[90];
    char string[20];
    int i = 0,c = 0,structChecker = 0;
    if (fp1 == NULL){
        perror("NAO EXISTE O FICHEIRO\n");
        return;
    }
    while(fgets(string,sizeof(string),fp1) != 0){
        arraydestrings[i] = strndup(string,sizeof(string));
        printf("%s",arraydestrings[i]);
        i++;
    }
    fclose(fp1);
    i=0;
    printf("\n----------INICIO DO PARSING DO FICHEIRO---------\n");
    while(arraydestrings[i] != NULL){
        printf("%s",arraydestrings[i]);
        if(!(strncmp(arraydestrings[i],"nome:",5))){
            char *nome = strtok(arraydestrings[i],":");
            processoAtual->nome = nome;
            structChecker++; 
        }
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
    if (structChecker != 7){
        printf("Programa Invalido\n");
        return;
    }
}
programa *juntor(processo info,char ** listaDeIntrucoesInfo){
    programa *associado = (programa *)malloc(sizeof(associado));
    associado->nomeProg = info.nome;
    associado->infoProcesso = info;
    associado->listaDeIntrucoes = listaDeIntrucoesInfo;
    associado->estado = 0;
    return associado;
}
void percorrerIntrucoes(programa *progAPercorrer){
    int forkjump = 0;
	while(progAPercorrer->infoProcesso.PC < progAPercorrer->infoProcesso.quantidadeDeIntrucoes){
		if(!(strncmp(progAPercorrer->listaDeIntrucoes[progAPercorrer->infoProcesso.PC],"M",strlen("M")))){
            printf("Entrei numa instruçao M \n");
            progAPercorrer->infoProcesso.processValue = atoi(strtok(progAPercorrer->listaDeIntrucoes[progAPercorrer->infoProcesso.PC],"M "));
            printf("Valor do processo: %d\n",progAPercorrer->infoProcesso.processValue); 
            progAPercorrer->infoProcesso.PC++;
        }
		if(!(strncmp(progAPercorrer->listaDeIntrucoes[progAPercorrer->infoProcesso.PC],"A",strlen("A")))){
            printf("Entrei numa instruçao A \n");
            progAPercorrer->infoProcesso.processValue += atoi(strtok(progAPercorrer->listaDeIntrucoes[progAPercorrer->infoProcesso.PC],"A "));
            printf("Valor do processo: %d\n",progAPercorrer->infoProcesso.processValue);
            progAPercorrer->infoProcesso.PC++;
        }
		if(!(strncmp(progAPercorrer->listaDeIntrucoes[progAPercorrer->infoProcesso.PC],"S",strlen("S")))){
            printf("Entrei numa instruçao S \n");
            progAPercorrer->infoProcesso.processValue -= atoi(strtok(progAPercorrer->listaDeIntrucoes[progAPercorrer->infoProcesso.PC],"S "));
            printf("Valor do processo: %d\n",progAPercorrer->infoProcesso.processValue);
            progAPercorrer->infoProcesso.PC++;
        }
            //EXECV()
		if(!(strncmp(progAPercorrer->listaDeIntrucoes[progAPercorrer->infoProcesso.PC],"L",strlen("L")))){
            printf("Entrei numa instruçao L \n");
            progAPercorrer->infoProcesso.nome = strtok(progAPercorrer->listaDeIntrucoes[progAPercorrer->infoProcesso.PC],"L ");
            progAPercorrer->nomeProg = progAPercorrer->infoProcesso.nome;
            progAPercorrer->listaDeIntrucoes = NULL;
            //CASO SEJA UM PROCESSO FILHO
            if(progAPercorrer->infoProcesso.ppid != 1){ 
            int aux = progAPercorrer->infoProcesso.pid;
            atribuidorDeInstrucoes(progAPercorrer->infoProcesso.nome,progAPercorrer->listaDeIntrucoes,&progAPercorrer->infoProcesso);
            progAPercorrer->infoProcesso.ppid = aux;
            }
            //NÂO SEJA FILHO
            else  atribuidorDeInstrucoes(progAPercorrer->infoProcesso.nome,progAPercorrer->listaDeIntrucoes,&progAPercorrer->infoProcesso);
            progAPercorrer->infoProcesso.PC++;
        }
            //FORK()
        if(!(strncmp(progAPercorrer->listaDeIntrucoes[progAPercorrer->infoProcesso.PC],"C",strlen("C")))){
            printf("Entrei numa instruçao C \n");
            filho(progAPercorrer);
            forkjump = atoi(strtok(progAPercorrer->listaDeIntrucoes[progAPercorrer->infoProcesso.PC],"C "));
            progAPercorrer->infoProcesso.PC+forkjump;
        }   //WAITING()
        if(!(strncmp(progAPercorrer->listaDeIntrucoes[progAPercorrer->infoProcesso.PC],"B",strlen("B")))){
            printf("Entrei numa instruçao B \n");
            progAPercorrer->estado = 1; //PARADO
            progAPercorrer->infoProcesso.PC++;
            return;
        }
	}
    printf("Percorri tudo\n");
    progAPercorrer->estado = 2; //MORTO
}
void filho(programa *pai){
    programa *filho = pai;
    percorrerIntrucoes(filho);
}