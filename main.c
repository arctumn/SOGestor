#include "gestor.h"

int main(){
    // somehow esta com problemas a ler a lista...need fixing
    int option;
    printf("Escolha um metodo para percorrer os programas\n");
    printf("1 -> Metodo FIFO\n");
    printf("2 -> Metodo SJF (Por implementar)\n");
    scanf("%d",&option);
    switch (option){
    case 1:
       fifo("lista.txt");
        break;
    case 2:
        sjf("lista.txt");// por implementar
    default:
        printf("Saiu do Programa\n");
        exit(0);
        break;
    }
   //programaRunnerFifo("teste.txt");
}