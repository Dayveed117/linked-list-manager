#include "biblioteca.h"

FilaDeFila* addElemFilaDeFila(FilaDeFila *filaDeFila)
{
	FilaDeFila *novo, *head= filaDeFila;

	if (filaDeFila == NULL)
	{
		filaDeFila = (FilaDeFila *) malloc(sizeof(FilaDeFila));
		filaDeFila->ID = 1;
		filaDeFila->elemento = NULL;
		filaDeFila->next = NULL;

		return filaDeFila;
	}

	while (filaDeFila->next != NULL)
	{
		filaDeFila = filaDeFila->next;
	}

	novo = (FilaDeFila *)malloc(sizeof(FilaDeFila));

	novo->ID = filaDeFila->ID + 1;
	novo->elemento = NULL;
	novo->next = NULL;

	filaDeFila->next = novo;

	return head;
}

FilaDeFila* findFilaDeFila(FilaDeFila *filaDeFila, int ID)
{
	if (filaDeFila == NULL)
		return NULL;	

	while (filaDeFila != NULL)
	{
		if (filaDeFila->ID == ID)
			return filaDeFila;

		filaDeFila = filaDeFila->next;
	}

	return NULL;

}

void printFilaDeFilas(FilaDeFila *filaDeFila, char mensagem[5000])
{
	char string [5000]="";

	strcpy(mensagem, "");

	if(filaDeFila == NULL)
	{
		strcpy(mensagem, "Não existe nenhuma Fila.\n");
	}

	while (filaDeFila != NULL)
	{
		sprintf(string, " Fila %d:\n", filaDeFila->ID);
		strcat(mensagem, string);
		printFila(filaDeFila->elemento, mensagem);

		filaDeFila = filaDeFila->next;
	}
}

void printUmaFila(FilaDeFila *filaDeFila, char mensagem[5000])
{
	char string [5000]="";

	strcpy(mensagem, "");

	if(filaDeFila == NULL)
	{
		strcpy(mensagem, "Não existe nenhuma Fila.\n");
	}

	sprintf(string, " Fila %d:\n", filaDeFila->ID);
	strcat(mensagem, string);
	printFila(filaDeFila->elemento, mensagem);

}
