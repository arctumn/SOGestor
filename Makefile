CC=cc
FLAGS=-c -Wall
LIBS=-lm
OBS=main.o #porefinir

#Alvo por defeito é o primeiro
all :  gestor

main.o :fundef.h gestor.h main.c
	$(CC) $(FLAGS) main.c

clean limpar:
	rm -f gestor *.o
	rm -f *~
#echo "Limpeza dos ficheiros exectuaveis, objectos e gedit tralha"