#include "gestor.h"

//----------------------------------------------------------------------------------------------------------------------------------------
//Authors: Pedro Lopes, Luís Espirito Santo, Pedro Carrasco, Afonso Simões
//Program that simmulates Escalonation of processes
//The program is in portuguese language as it was part of the University course:"Sistemas Operativos"(Operative Systems) Second Semmester
//The Decomentation is also in portuguese
//Entrega -> PARTE 1
//----------------------------------------------------------------------------------------------------------------------------------------


int main(){
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
}