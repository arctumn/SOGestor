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
    if (structChecker != 7){
        printf("Programa Invalido\n");
        return;
    }
}
programa *juntor(processo info,char ** listaDeIntrucoesInfo){
    programa *associado;
    associado->nomeProg = info.nome;
    associado->infoProcesso = info;
    associado->listaDeIntrucoes = listaDeIntrucoesInfo;
    return associado;
}
void percorrerIntrucoes(int i,programa *progAPercorrer){
    int forkjump = 0;
	while(progAPercorrer->listaDeIntrucoes[i] != NULL){
		if(!(strncmp(progAPercorrer->listaDeIntrucoes[i],"M",strlen("M")))){
            progAPercorrer->infoProcesso.processValue = atoi(strtok(progAPercorrer->listaDeIntrucoes[i],"M "));
            i++;
        }
		if(!(strncmp(progAPercorrer->listaDeIntrucoes[i],"A",strlen("A")))){
            progAPercorrer->infoProcesso.processValue += atoi(strtok(progAPercorrer->listaDeIntrucoes[i],"A "));
            i++;
        }
		if(!(strncmp(progAPercorrer->listaDeIntrucoes[i],"S",strlen("S")))){
            progAPercorrer->infoProcesso.processValue -= atoi(strtok(progAPercorrer->listaDeIntrucoes[i],"S "));
            i++;
        }
		if(!(strncmp(progAPercorrer->listaDeIntrucoes[i],"L",strlen("L")))){
            progAPercorrer->infoProcesso.nome = strtok(progAPercorrer->listaDeIntrucoes[i],"L ");
            progAPercorrer->nomeProg = progAPercorrer->infoProcesso.nome;
            progAPercorrer->listaDeIntrucoes = NULL;
            if(progAPercorrer->infoProcesso.ppid != 1){
            int aux = progAPercorrer->infoProcesso.pid;
            atribuidorDeInstrucoes(progAPercorrer->infoProcesso.nome,progAPercorrer->listaDeIntrucoes,&progAPercorrer->infoProcesso);
            progAPercorrer->infoProcesso.ppid = aux;
            }
            else  atribuidorDeInstrucoes(progAPercorrer->infoProcesso.nome,progAPercorrer->listaDeIntrucoes,&progAPercorrer->infoProcesso);
            i++;
        }
        if(!(strncmp(progAPercorrer->listaDeIntrucoes[i],"C",strlen("C")))){
            filho(i,progAPercorrer);
            forkjump = atoi(strtok(progAPercorrer->listaDeIntrucoes[i],"C "));
            i+forkjump;
        }
	}
}