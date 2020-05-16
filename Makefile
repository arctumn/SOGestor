CC=cc
FLAGS=-c -Wall -pthread
FLAGSO=-o gestor 
LIBS=-lm
OBS=main.o gestorImplementation.o #porefinir

#Alvo por defeito é o primeiro
all : gestor

gestor: main.o gestorImplementation.o
	$(CC) $(FLAGSO) $(OBS) -pthread gestor.h escalonamentoSJF.c
	make cleanEx
#comentar o make cleanEx se quiserem os objetos

main.o : gestor.h main.c
	$(CC) $(FLAGS) main.c

gestorImplementation.o : gestor.h gestorImplementation.c
	$(CC) $(FLAGS) gestorImplementation.c

cleanEx : 
	rm -f *.o

clean :
	rm -f *.o gestor