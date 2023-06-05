#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define NUM_THREADS 10

typedef struct FILA {
	
    int msgId;
	char content[100];
	struct FILA *next;

}Fila;

typedef struct FILADEFILA {
	
    int ID;
	Fila *elemento;
	struct FILADEFILA *next;

}FilaDeFila;

typedef struct JackIn {

    int ID;
    int msgID;
    char msg[100];
    FilaDeFila *FILA;

}JackIn;

/*ligação entre listas e threads
Usar como variável global ou mandar para a thread como parãmetro?*/
JackIn Jack;
pthread_mutex_t trinco;

FilaDeFila* addElemFilaDeFila(FilaDeFila *F);
FilaDeFila* saveFila(FilaDeFila *F, int ID);
Fila *addElem(Fila *f, char msgContent[100]);
Fila *deleteElem(Fila *f, int ID);
void printFilaDeFilas(FilaDeFila *F);
void printFila_id(Fila *f);
void printFilaDeFilas_id(FilaDeFila *F);
void printFila(Fila *f);
void printElem(Fila *f, int msgId);

void *TH_addElemFilaDeFila(void *args);
void *TH_addElem(void *args);
void *TH_deleteElem(void *args);
void *TH_printFilaDeFilas(void *args);
void *TH_printFilaDeFilas_id(void *args);
void *TH_printFila(void *args);
void *TH_printFila_id(void *args);
void *TH_printElem(void *args);


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

void printFila_id(Fila *f)
{
	while (f != NULL)
	{
        printf("%d", f->msgId);
        f = f->next;
	}
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



//funções adaptadas a threads

void *TH_addElemFilaDeFila(void *args) {

    //JackIn *parsed = (JackIn*)args;
    pthread_mutex_lock(&trinco);
    Jack.FILA = addElemFilaDeFila(Jack.FILA);
    pthread_mutex_unlock(&trinco);
    return NULL;
}

void *TH_addElem(void *args) {

    char a[20] = "Hey cat.";
    char b[20] = "Hey dog.";
    char c[20] = "Hey lión.";
    char d[20] = "Hey panda.";
    char e[20] = "Hey bear.";
    char f[20] = "Hey bunny.";
    char g[20] = "Hey fly.";
    char h[20] = "Hey snake.";
    char i[20] = "Hey koala.";
    char j[20] = "Heeeeeey brother.";
    //JackIn *parsed = (JackIn*)args;
    pthread_mutex_lock(&trinco);
    int id = *(int*)args;
    int x;
    FilaDeFila *F2 = saveFila(Jack.FILA, id);

    switch (id) {
        case 1:
            for(x=0; x<NUM_THREADS; x++) {
                F2->elemento = addElem(F2->elemento, a);}
        break;
        case 2:
            for(x=0; x<NUM_THREADS; x++) {
                F2->elemento = addElem(F2->elemento, b);}
        break;
        case 3:
            for(x=0; x<NUM_THREADS; x++) {
                F2->elemento = addElem(F2->elemento, c);}
        break;
        case 4:
            for(x=0; x<NUM_THREADS; x++) {
                F2->elemento = addElem(F2->elemento, d);}
        break;
        case 5:
            for(x=0; x<NUM_THREADS; x++) {
                F2->elemento = addElem(F2->elemento, e);}
        break;
        case 6:
            for(x=0; x<NUM_THREADS; x++) {
                F2->elemento = addElem(F2->elemento, f);}
        break;
        case 7:
            for(x=0; x<NUM_THREADS; x++) {
                F2->elemento = addElem(F2->elemento, g);}
        break;
        case 8:
            for(x=0; x<NUM_THREADS; x++) {
                F2->elemento = addElem(F2->elemento, h);}
        break;
        case 9:
            for(x=0; x<NUM_THREADS; x++) {
                F2->elemento = addElem(F2->elemento, i);}
        break;
        case 10:
            for(x=0; x<NUM_THREADS; x++) {
                F2->elemento = addElem(F2->elemento, j);}
        break;
    }
    pthread_mutex_unlock(&trinco);
}

void *TH_deleteElem(void *args) {

    pthread_mutex_lock(&trinco);
    int id = *(int*)args;
    FilaDeFila *F2 = saveFila(Jack.FILA, id);
    //JackIn *parsed = (JackIn*)args;

    F2->elemento = deleteElem(F2->elemento, id);
    if(F2->next != NULL)
        F2 = F2->next;
    pthread_mutex_unlock(&trinco);
    return NULL;
}

void *TH_printFilaDeFilas_id(void *args) {

    //JackIn *parsed = (JackIn*)args;
    pthread_mutex_lock(&trinco);
    printFilaDeFilas_id(Jack.FILA);
    pthread_mutex_unlock(&trinco);
    return NULL;
}

void *TH_printFilaDeFilas(void *args) {

    pthread_mutex_unlock(&trinco);
    printFilaDeFilas(Jack.FILA);
    pthread_mutex_unlock(&trinco);
    return NULL;
}

void *TH_printFila_id(void *args) {

    //JackIn *parsed = (JackIn*)args;
    pthread_mutex_lock(&trinco);
    int id = *(int*)args;
    FilaDeFila *F2 = saveFila(Jack.FILA, id);
    puts("");
    printFila_id(F2->elemento);
    pthread_mutex_unlock(&trinco);
    return NULL;
}

void *TH_printFila(void *args) {

    //JackIn *parsed = (JackIn*)args;
    pthread_mutex_lock(&trinco);
    int id = *(int*)args;
    FilaDeFila *F2 = saveFila(Jack.FILA, id);

    printFila(F2->elemento);
    pthread_mutex_unlock(&trinco);
    return NULL;
}

void *TH_printElem(void *args) {

    //JackIn *parsed = (JackIn*)args;
    //imprimir elemento id da fila id
    int id = *(int*)args;
    FilaDeFila *F2 = saveFila(Jack.FILA, id);
    printElem(F2->elemento, id);
    return NULL;
}

//fazer disto um apontador?
JackIn initialize(void) {

    /*JackIn *J = (JackIn*)malloc(sizeof(JackIn));
    J->FILA = NULL;
    J->fila = NULL;
    J->ID = 0;
    J->msgID = 0;*/
    JackIn J;
    J.FILA = NULL;
    J.ID = 0;
    J.msgID = 0;

    return J;
}

int main() {

    int i, ids[NUM_THREADS];
    pthread_t pth[NUM_THREADS];

    Jack = initialize();
    
    //vetor associado ao id das threads
    for(i=0; i<NUM_THREADS; i++) {
        ids[i] = i+1;
    }

    //adicionar Filas
    for(i=0; i<NUM_THREADS; i++) {
        pthread_create(&pth[i], NULL, TH_addElemFilaDeFila, NULL);
    }
    for(i=0; i<NUM_THREADS; i++) {
        pthread_join(pth[i], NULL);
    }
    pthread_create(&pth[i], NULL, TH_printFilaDeFilas_id, NULL);
    
    //adicionar elementos(mensagens) às filas
    for(i=0; i<NUM_THREADS; i++) {
        pthread_create(&pth[i], NULL, TH_addElem, &ids[i]);
    }
    for(i=0; i<NUM_THREADS; i++) {
        pthread_join(pth[i], NULL);
    }

    //imprimir o conteudo de todas as filas
    pthread_create(&pth[0], NULL, TH_printFilaDeFilas, NULL);
    pthread_join(pth[0], NULL);

    //apagar elemento i da fila i
    for(i=0; i<NUM_THREADS; i++) {
        pthread_create(&pth[i], NULL, TH_deleteElem, &ids[i]);
    }
    for(i=0; i<NUM_THREADS; i++) {
        pthread_join(pth[i], NULL);
    }

    //imprimir de volta para o ecra as filas atualizadas
    pthread_create(&pth[0], NULL, TH_printFilaDeFilas, NULL);
    pthread_join(pth[0], NULL);

    //imprimir os ids das mensagens que restaram em cada fila
    for(i=0; i<NUM_THREADS; i++) {
        pthread_create(&pth[i], NULL, TH_printFila_id, &ids[i]);
    }
    for(i=0; i<NUM_THREADS; i++) {
        pthread_join(pth[i], NULL);
    }

    return 0;
}
