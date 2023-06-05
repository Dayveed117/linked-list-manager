#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/stat.h> //mknod library
#include <string.h>


typedef struct FILA
{
	int msgId;
	char content[100];
	struct FILA *next;
} Fila;

typedef struct FILADEFILA
{
	int ID;
	Fila *elemento;
	struct FILADEFILA *next;

} FilaDeFila;

Fila* addElemFila(Fila *fila, char msgContent[100]);
Fila *deleteElem(Fila *fila, int ID);
Fila* getElem(Fila *fila, int msgId);
void printFila(Fila *fila, char mensagem[5000]);

FilaDeFila* addElemFilaDeFila(FilaDeFila *filaDeFila);
FilaDeFila* findFilaDeFila(FilaDeFila *filaDeFila, int ID);
void printFilaDeFilas(FilaDeFila *filaDeFila, char mensagem[5000]);
void printUmaFila(FilaDeFila *filaDeFila, char mensagem[5000]);
 
