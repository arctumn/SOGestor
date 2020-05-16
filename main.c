#include "gestor.h"

//----------------------------------------------------------------------------------------------------------------------------------------
//Authors: Pedro Lopes, Luís Espirito Santo, Pedro Carrasco, Afonso Simões
//Program that simmulates Escalonation of processes
//The program is in portuguese language as it was part of the University course:"Sistemas Operativos"(Operative Systems) Second Semmester
//The Decomentation is also in portuguese
//----------------------------------------------------------------------------------------------------------------------------------------


int main(){
    int option;
    printf("Escolha um metodo para percorrer os programas\n");
    printf("1 -> Metodo FIFO\n");
    printf("2 -> Metodo Priority (Preemptive) \n");
    scanf("%d",&option);
    switch (option){
    case 1:
       fifo("lista.txt");
        break;
    case 2:
        priority("lista.txt");// por implementar
    default: //qualquer outra tecla  fecha o programa o exit fora deste switch não tem sentido
        exit(0);
        break;
    }
    //exit(0); isto era inutil porque o default nunca iria permitir que isto va acontecer
}