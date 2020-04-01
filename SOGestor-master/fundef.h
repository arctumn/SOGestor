#include "gestor.h"


char ** atribuidorDeInstrucoes(char *nomeFich, processo * processoAtual){ // DEVOLVER OQUE?
    FILE *fp1 = fopen(nomeFich,"r");
    processo * atual = NULL;
    char string[20];
    char *arraydestrings[90];
    int i = 0;


    if (fp1 == NULL){
        perror("NAO EXISTE O FICHEIRO\n");
        return NULL;
    }

    while(fgets(string,sizeof(string),fp1) != 0){
        arraydestrings[i] = string;
        i++;
    }

    fclose(fp1);
    i=0;

    while(!strcmp(arraydestrings[i],"T")){
           if(!(strncmp(arraydestrings[i],"nome:",5))){
                char *nome = strtok(arraydestrings[i],"nome");
                atual->nome = nome;
                continue;  
     }
 
        
    }
}