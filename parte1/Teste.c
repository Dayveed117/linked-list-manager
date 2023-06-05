#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_THREADS 10

typedef struct FILA
{
	int msgId;
	char content[100];
	struct FILA *next;
}Fila;

typedef struct FILADEFILA
{
	int ID;
	Fila *elemento;
	struct FILADEFILA *next;

}FilaDeFila;

FilaDeFila* addElemFilaDeFila(FilaDeFila *F);
FilaDeFila* saveFila(FilaDeFila *F, int ID);
Fila *addElem(Fila *f, char msgContent[100]);
Fila *deleteElem(Fila *f, int ID);
void printFilaDeFilas(FilaDeFila *F);
void printFila_id(Fila *f);
void printFilaDeFilas_id(FilaDeFila *F);
void printFila(Fila *f);
void printElem(Fila *f, int msgId);


//Operações sobre Fila e FilaDeFila


FilaDeFila* addElemFilaDeFila(FilaDeFila *F)
{
	
	FilaDeFila *novo;
	FilaDeFila *head = F;

	if (F == NULL)
	{
		F = (FilaDeFila *) malloc(sizeof(FilaDeFila));
		F->ID = 1;
		F->elemento = NULL;
		F->next = NULL;

		return F;
	}

	while (F->next != NULL)
	{
		F = F->next;
	}

	novo = (FilaDeFila *)malloc(sizeof(FilaDeFila));

	novo->ID = F->ID + 1;
	novo->elemento = NULL;
	novo->next = NULL;

	F->next = novo;

	return head;
}

Fila *addElem(Fila *f, char msgContent[100])
{
	Fila *new;
	Fila *head = f;

	if (f == NULL)
	{
		f = (Fila*)malloc(sizeof(Fila));
		f->msgId = 1;
		strcpy(f->content, msgContent);
		f->next = NULL;
		
		return f;
	}

	while (f->next != NULL)
	{
		f = f->next;
	}

	new = (Fila*)malloc(sizeof(Fila));
	new->msgId = f->msgId+1;
	strcpy(new->content, msgContent);
	new->next = NULL;

	f->next = new;
	
	return head;
}

Fila *deleteElem(Fila *f, int ID)
{
    
	Fila *tmp;
    Fila *head = f;

	if (f == NULL)
		return f;
		
	if (f->msgId == ID) {
        //caso seja o primeiro
		tmp = f->next;
		free(f);
		return tmp;
	}
			
	while (f->next != NULL) {
		if(f->next->msgId == ID) {
			tmp = f->next;
            //se for o último
            if (tmp->next == NULL) {
                f->next = NULL;
			    free(tmp);
                return head;
            }
            //caso esteja entre 2 elementos
            else {
                f->next = tmp->next;
                free(tmp);
                return head;
            }
		}
		f = f->next;
	}

	return head;
}

FilaDeFila* saveFila(FilaDeFila *filaDeFila, int ID) {
	if (filaDeFila == NULL)
		return NULL;
	while (filaDeFila != NULL) {
		if (filaDeFila->ID == ID)
			return filaDeFila;
		filaDeFila = filaDeFila->next;
	}

	return NULL;
}

//Funções print

void printFilaDeFilas_id(FilaDeFila *F) {
    
    while (F != NULL) {
		printf("%d ", F->ID);
        F = F->next;
	}
    printf("\n");
}

void printFilaDeFilas(FilaDeFila *F) {

    while (F != NULL) {
        if(F->elemento == NULL) {
            printf("Fila %d sem elementos\n\n", F->ID);
        }
        else {
            printf("Fila %d:\n\n", F->ID);
            printFila(F->elemento);
            printf("\n");
        }
        F = F->next;
	}
    printf("\n");
}

void printFila(Fila *f)
{
	while (f != NULL)
	{
        printf("%d: %s\n", f->msgId, f->content);
        f = f->next;
	}
}

void printElem(Fila *f, int msgId)
{
	while (f != NULL)
	{
		if (f->msgId == msgId)
		{
            printf("%d: %s\n", f->msgId, f->content);
            return;
		}
		f = f->next;
	}
	printf("Elemento %d não encontrado.\n", msgId);
}



int main() {

    FilaDeFila *F = NULL;
    FilaDeFila *F2 = NULL;
    FilaDeFila *F3 = NULL;

    int i;

    for(i=0; i<NUM_THREADS; i++) {
        F = addElemFilaDeFila(F);            
    }
    printFilaDeFilas_id(F);
    printf("\n");

    F2 = saveFila(F, 2);
    F3 = saveFila(F, 3);

    for(i=1; i<=NUM_THREADS; i++) {
        if((i%2) == 0) {
            F2->elemento = addElem(F2->elemento, "Even");
        }
        else {
            F->elemento = addElem(F->elemento, "Odd");
        }
    }
    printFila(F2->elemento);
    printFila(F->elemento);
    printf("\n");

    F3->elemento = addElem(F3->elemento, "Surprise Party!");
    F3->elemento = addElem(F3->elemento, "That's enough.");
    printElem(F3->elemento, 1);
    printf("\n");

    for(i=1; i<=NUM_THREADS; i++) {
        if((i%2) == 0) {
            F->elemento = deleteElem(F->elemento, i);
        }
        else {
            F2->elemento = deleteElem(F2->elemento, i);
        }
    }

    printf("\n");
    printFilaDeFilas(F);
   

    return 0;
}
