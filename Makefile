#Compiler
CC=gcc

# Primeira linha = modo debug
# Segunda = SPEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEED
#EXEC_TYPE = -Og -g
EXEC_TYPE = -O3

FLAGS= -Wall -Wextra -Wparentheses -Wmissing-declarations -Wunreachable-code -Wunused -Wmissing-field-initializers -Wmissing-prototypes -Wswitch-enum -Wredundant-decls -Wshadow -Wswitch-default -Wuninitialized -pedantic -pthread
FLAGSO= -o gestor 
LIBS=

GESTOR_SRC = $(wildcard *.c)
GESTOR_OBJ = ${GESTOR_SRC:.c=.o}

# make || make all
all : gestor
.PHONY: all

gestor: ${GESTOR_OBJ}
	$(CC) ${FLAGS} ${EXEC_TYPE} -o gestor ${GESTOR_OBJ}
.PHONY: gestor

# make clean
clean:
	rm -f *.o gestor
.PHONY: clean

# make oclean
oclean:
	rm -f *.o
.PHONY: oclean