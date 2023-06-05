#include "biblioteca.h"


Fila* addElemFila(Fila *fila, char msgContent[100])
{
	Fila *novo;
	Fila *header = fila;

	if (fila == NULL)
	{
		fila = (Fila*)malloc(sizeof(Fila));
		fila->msgId = 1;
		strcpy(fila->content, msgContent);
		fila->next = NULL;
		
		return fila;
	}

	while (fila->next != NULL)
	{
		fila =fila->next;
	}

	novo = (Fila *) malloc(sizeof(Fila));
	novo->msgId = fila->msgId+1;
	strcpy(novo->content, msgContent);
	novo->next = NULL;

	fila->next = novo;
	
	return header;
}

Fila *deleteElem(Fila *fila, int ID)
{
	Fila *p;
	Fila *head = fila;

	if (fila == NULL)
		return fila;
	
	if (fila->msgId == ID)
	{
		p = fila;
		fila = fila->next;
		free(p);

		return fila;
	}
			
	while (fila->next != NULL)
	{
		if(fila->next->msgId == ID)
		{
			p = fila->next;
			fila->next = p->next;
			free(p);

			return fila;
		}

		fila = fila->next;
	}

	return head;
}

/*
void setMsgId(Fila *fila, int ID)
{
	fila->msgId = ID;
}
void setContent(Fila *fila, char content[100])
{
	strcpy(fila->content, content);
}
*/

void getMsgId(Fila *fila)
{
	printf("%d\n", fila->msgId);
}
void getContent(Fila *fila)
{
	printf("%s\n", fila->content);
}

Fila* getElem(Fila *fila, int msgId)
{
	while (fila != NULL)
	{
		if (fila->msgId == msgId)
		{
			return fila;
		}
		fila = fila->next;
	}

	return NULL;
}

void printFila(Fila *fila, char mensagem[5000])
{
	char string[5000] ="";

	while (fila != NULL)
	{
		//printf("%d\n", fila->msgId);
		sprintf(string, " -> msgID %d, content \"%s\"\n", fila->msgId, fila->content);	
		strcat(mensagem, string);
		fila = fila->next;
	}
	
	strcat(mensagem, "\n");
}
