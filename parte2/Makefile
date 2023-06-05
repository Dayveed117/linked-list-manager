#A Simple Example Makefile
# 
# Alvo: Dependencias
# tab Action 1
# tab Action 2
#
#Variaveis: Compiler, compiler flags, libraries to link, name of of object files
#
CC=cc
FLAGS=-c -Wall
LIBS=-lm -pthread
OBS=fila.o filaDeFila.o servidor.o
 
#Alvo por defeito é o primeiro 
all :  server
 
fila.o : biblioteca.h fila.c
	$(CC) $(FLAGS) fila.c
filaDeFila.o : biblioteca.h filaDeFila.c
	$(CC) $(FLAGS) filaDeFila.c
servidor.o : biblioteca.h servidor.c
	$(CC) $(FLAGS) servidor.c


server : $(OBS)
	$(CC)  -o server  $(OBS) $(LIBS)

clean limpar:
	rm -f server *.o
	rm -f *~
	echo "Limpeza dos ficheiros exectuaveis, objectos e gedit tralha"
