CC=cc
FLAGS=-c -Wall
FLAGSO=-o gestor
LIBS=-lm
OBS=main.o gestorI.o #porefinir

#Alvo por defeito é o primeiro
all : gestor

gestor: main.o gestorImplementation.o
	$(CC) $(FLAGSO)  main.o gestorImplementation.o 
	make cleanEx

main.o : gestor.h main.c
	$(CC) $(FLAGS) main.c

gestorImplementation.o : gestor.h gestorImplementation.c
	$(CC) $(FLAGS) gestorImplementation.c

cleanEx : 
	rm -f *.o

clean :
	rm -f *.o gestor
#echo "Limpeza dos ficheiros exectuaveis, objectos e gedit tralha"
