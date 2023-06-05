#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define NUM_THREADS 10
#define MSG_SIZE 100

typedef struct FILA {
	
    int msgId;
	char content[MSG_SIZE];
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
    char msg[MSG_SIZE];
    FilaDeFila *FILA;
}JackIn;

/*ligação entre listas e threads
Usar como variável global ou mandar para a thread como parãmetro?
GLOBAL VARIABLES*/
JackIn Jack;
pthread_mutex_t trinco;

FilaDeFila* addElemFilaDeFila(FilaDeFila *F);
FilaDeFila *apagarFilaDeFila(FilaDeFila *F, int ID);
FilaDeFila* saveFila(FilaDeFila *F, int ID);
Fila *addElem(Fila *f, char msgContent[100]);
Fila *apagarMensagens(Fila *f);
Fila *deleteElem(Fila *f, int ID);
void printFilaDeFilas(FilaDeFila *F);
void printFila_id(Fila *f);
void printFilaDeFilas_id(FilaDeFila *F);
void printFila(Fila *f);
void printElem(Fila *f, int msgId);

void *TH_addElemFilaDeFila(void *args);
void *TH_addElem(void *args);
void *TH_apagarMensagens(void *args);
void *TH_apagarFilaDeFila(void *args);
void *TH_deleteElem(void *args);
void *TH_printFilaDeFilas(void *args);
void *TH_printFilaDeFilas_id(void *args);
void *TH_printFila(void *args);
void *TH_printFila_id(void *args);
void *TH_printElem(void *args);
void menu();
void header();

void menu() {

    puts("\t1 - Criar uma fila");
    puts("\t2 - Criar NT/2 filas");
    puts("\t3 - Inserir um elemento numa fila");
    puts("\t4 - Inserir NT elementos numa fila");
    puts("\t5 - Apagar um elemento de uma fila");
    puts("\t6 - Apagar todas as mensagens de uma fila");
    puts("\t7 - Apagar uma fila");
    puts("\t8 - Mostrar conteudo de todas as filas");
    puts("\t9 - Mostrar conteudo de uma fila");
    puts("\t10 - Mostrar um elemento de uma fila");
    puts("\t11 - Mostrar ID de todas as filas");
    puts("\t12 - Mostrar msgIDs de uma fila");
    puts("\t0 - Sair");
    puts("Escolher opção: (INTEIRO)");
}

void header() {
    puts("Programa de Teste de implementação de filas(listas) em threads.");
    puts("Threads atuam uma de cada vez de forma ordenada.");
    puts("Sem conflitos, sem preocupações.");
}

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

FilaDeFila *apagarFilaDeFila(FilaDeFila *F, int ID) {

    FilaDeFila *tmp;
    FilaDeFila *head = F;

	if (F == NULL)
		return F;
		
	if (F->ID == ID) {
        //caso seja o primeiro
		tmp = F->next;
		free(F);
		return tmp;
	}
			
	while (F->next != NULL) {
		if(F->next->ID == ID) {
			tmp = F->next;
            //se for o último
            if (tmp->next == NULL) {
                F->next = NULL;
			    free(tmp);
                return head;
            }
            //caso esteja entre 2 elementos
            else {
                F->next = tmp->next;
                free(tmp);
                return head;
            }
		}
		F = F->next;
	}

    puts("Elemento não existente.");
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

Fila *apagarMensagens(Fila *f) {

    Fila *tmp;
    
    if(f == NULL)
        return NULL;    

    while(f != NULL) {
        if(f->next == NULL) {
            free(f);
            return NULL;
        }
        tmp = f;
        f = f->next;
        tmp->next = NULL;
        free(tmp);    
    }

    return NULL;
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

    puts("Elemento não existente.");
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
        printf("%d ", f->msgId);
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

    pthread_mutex_lock(&trinco);
    Jack.FILA = addElemFilaDeFila(Jack.FILA);
    pthread_mutex_unlock(&trinco);
    return NULL;
}

void *TH_addElem(void *args) {

    pthread_mutex_lock(&trinco);
    FilaDeFila *F2;
    if((F2 = saveFila(Jack.FILA, Jack.ID)) == NULL) {
        fprintf(stderr, "Não existe a fila %d\n", Jack.ID);
        return NULL;
    }
    F2->elemento = addElem(F2->elemento, Jack.msg);
    pthread_mutex_unlock(&trinco);
    return NULL;
}

void *TH_apagarMensagens(void *args) {

    pthread_mutex_lock(&trinco);
    FilaDeFila *F2;
    if((F2 = saveFila(Jack.FILA, Jack.ID)) == NULL) {
        fprintf(stderr, "Não existe a fila %d\n", Jack.ID);
        return NULL;
    }
    F2->elemento = apagarMensagens(F2->elemento);
    pthread_mutex_unlock(&trinco);
    return NULL;
}

void *TH_apagarFilaDeFila(void *args) {
    
    pthread_mutex_lock(&trinco);
    FilaDeFila *F2;
    if((F2 = saveFila(Jack.FILA, Jack.ID)) == NULL) {
        fprintf(stderr, "Não existe a fila %d\n", Jack.ID);
        return NULL;
    }
    F2->elemento = apagarMensagens(F2->elemento);
    Jack.FILA = apagarFilaDeFila(Jack.FILA, F2->ID);
    pthread_mutex_unlock(&trinco);
    return NULL;
}

void *TH_deleteElem(void *args) {

    pthread_mutex_lock(&trinco);
    FilaDeFila *F2;
    if((F2 = saveFila(Jack.FILA, Jack.ID)) == NULL) {
        fprintf(stderr, "Não existe a fila %d\n", Jack.ID);
        return NULL;
    }
    F2->elemento = deleteElem(F2->elemento, Jack.msgID);
    pthread_mutex_unlock(&trinco);
    return NULL;
}

void *TH_printFilaDeFilas_id(void *args) {

    pthread_mutex_lock(&trinco);
    printFilaDeFilas_id(Jack.FILA);
    pthread_mutex_unlock(&trinco);
    return NULL;
}

void *TH_printFilaDeFilas(void *args) {

    pthread_mutex_lock(&trinco);
    puts("");
    printFilaDeFilas(Jack.FILA);
    pthread_mutex_unlock(&trinco);
    return NULL;
}

void *TH_printFila_id(void *args) {

    pthread_mutex_lock(&trinco);
    FilaDeFila *F2 = saveFila(Jack.FILA, Jack.ID);
    puts("");
    printFila_id(F2->elemento);
    pthread_mutex_unlock(&trinco);
    return NULL;
}

void *TH_printFila(void *args) {

    pthread_mutex_lock(&trinco);
    FilaDeFila *F2 = saveFila(Jack.FILA, Jack.ID);
    printFila(F2->elemento);
    pthread_mutex_unlock(&trinco);
    return NULL;
}

void *TH_printElem(void *args) {

    pthread_mutex_lock(&trinco);
    FilaDeFila *F2 = saveFila(Jack.FILA, Jack.ID);
    printElem(F2->elemento, Jack.msgID);
    pthread_mutex_unlock(&trinco);
    return NULL;
}

JackIn initialize(void) {

    JackIn J;
    J.FILA = NULL;
    J.ID = 0;
    J.msgID = 0;

    return J;
}

JackIn reset_values(JackIn J) {

    J.ID = 0;
    J.msgID = 0;
    memset(Jack.msg, 0, MSG_SIZE);

    return J;
}



int main() {

    char msg[MSG_SIZE];
    int ids[NUM_THREADS];
    int i, op, prompt;
    pthread_t pth[NUM_THREADS];

    for(i=0; i<NUM_THREADS; i++) {
        ids[i] = i+1;
    }

    header();
    Jack = initialize();

    while(1) {

        menu();
        scanf("%d", &op);

        switch(op) {
            
            //sair do programa
            //testado e verificado
            case 0:
                puts("So long, tomoyo.");
                exit(0);
                break;

            //Criar uma fila
            //testado e verificado
            case 1:
                pthread_create(&pth[0], NULL, TH_addElemFilaDeFila, NULL);
                pthread_join(pth[0], NULL);
                puts("Fila adicionada.");
                puts("");
                getchar();
                break;

            //Criar 5 filas
            //testado e verificado
            case 2:
                for(i=0; i<NUM_THREADS/2; i++) {
                    pthread_create(&pth[i], NULL, TH_addElemFilaDeFila, NULL);
                }
                for(i=0; i<NUM_THREADS/2; i++) {
                    pthread_join(pth[i], NULL);
                }
                puts("Filas adicionadas.");
                puts("");
                getchar();
                break;
            
            //inserir um elemento em uma fila
            //testado e verificado
            case 3:
                if(Jack.FILA == NULL) {
                    puts("Não existem filas.");
                    getchar();
                    break;
                }
                puts("Em que fila adicionar?");
                scanf("%d", &Jack.ID);
                getchar();
                puts("Mensagem: (100 char max)");
                scanf("%[^\n]s ", Jack.msg);
                pthread_create(&pth[1], NULL, TH_addElem, NULL);
                pthread_join(pth[1], NULL);
                //limpar o buffer
                puts("Mensagem adicionada.");
                puts("");
                getchar();
                break;

            //inserir 10 elementos numa fila
            //testado e verificado
            case 4:
                if(Jack.FILA == NULL) {
                    puts("Não existem filas.");
                    getchar();
                    break;
                }
                puts("Em que fila adicionar?");
                scanf("%d", &Jack.ID);
                getchar();
                for(i=0; i<10; i++) {
                    printf("Mensagem %d: (100 char max)\n", i+1);
                    scanf("%[^\n]s ", Jack.msg);
                    pthread_create(&pth[i], NULL, TH_addElem, NULL);
                    pthread_join(pth[i], NULL);
                    memset(Jack.msg, 0, MSG_SIZE);
                    getchar();
                }
                //limpar o buffer
                puts("Mensagens adicionadas.");
                puts("");
                getchar();
                break;

            //Apagar 1 elemento de uma fila
            //testado e verificado
            case 5:
                if(Jack.FILA == NULL) {
                    puts("Não existem filas.");
                    getchar();
                    break;
                }
                puts("Apagar de que fila?");
                scanf("%d", &Jack.ID);
                puts("Apagar que ID de mensagem?");
                scanf("%d", &Jack.msgID);
                getchar();
                pthread_create(&pth[2], NULL, TH_deleteElem, NULL);
                pthread_join(pth[2], NULL);
                //limpar o buffer
                puts("Operação concluída.");
                puts("");
                getchar();
                break;
            
            //Apagar todas as mensagens de uma fila
            //testado e verificado
            case 6:
                if(Jack.FILA == NULL) {
                    puts("Não existem filas.");
                    getchar();
                    break;
                }
                puts("Apagar mensagens de que Fila?");
                scanf("%d", &Jack.ID);
                getchar();
                pthread_create(&pth[3], NULL, TH_apagarMensagens, NULL);
                pthread_join(pth[3], NULL);
                //limpar o buffer
                puts("Operação concluída.");
                puts("");
                getchar();

                break;


            //Apagar lista em si
            //testado e verificado
            case 7:
                if(Jack.FILA == NULL) {
                    puts("Não existem filas.");
                    getchar();
                    break;
                }
                puts("Apagar de que fila?");
                scanf("%d", &Jack.ID);
                getchar();
                pthread_create(&pth[4], NULL, TH_apagarFilaDeFila, NULL);
                pthread_join(pth[4], NULL);
                //limpar o buffer
                puts("Operação concluída.");
                puts("");
                getchar();
                break;

            //Imprimir conteudo de todas as filas
            //testado e verificado
            case 8:
                if(Jack.FILA == NULL) {
                    puts("Não existem filas.");
                    getchar();
                    break;
                }
                pthread_create(&pth[5], NULL, TH_printFilaDeFilas, NULL);
                pthread_join(pth[5], NULL);
                puts("");
                getchar();
                break;
            
            //Imprimir conteudo de uma fila
            //testado e verificado
            case 9:
                if(Jack.FILA == NULL) {
                    puts("Não existem filas.");
                    getchar();
                    break;
                }
                puts("Mostrar conteudos de que fila?");
                scanf("%d", &Jack.ID);
                puts("");
                pthread_create(&pth[6], NULL, TH_printFila, NULL);
                pthread_join(pth[6], NULL);
                puts("");
                getchar();
                break;

            //Imprimir um elemento de uma fila
            //testado e verificado
            case 10:
                if(Jack.FILA == NULL) {
                    puts("Não existem filas.");
                    getchar();
                    break;
                }
                puts("Mostrar elemento de que fila?");
                scanf("%d", &Jack.ID);
                puts("Mostrar que elemento?");
                scanf("%d", &Jack.msgID);
                getchar();
                pthread_create(&pth[7], NULL, TH_printElem, NULL);
                pthread_join(pth[7], NULL);
                puts("");
                getchar();
                break;

            //Imprimir ID de todas as filas
            //testado e verificado
            case 11:
                if(Jack.FILA == NULL) {
                    puts("Não existem filas.");
                    getchar();
                    break;
                }
                pthread_create(&pth[8], NULL, TH_printFilaDeFilas_id, NULL);
                pthread_join(pth[8], NULL);
                puts("");
                getchar();
                break;

            //Imprimir msgIDs de uma fila
            //testado e verificado
            case 12:
                if(Jack.FILA == NULL) {
                    puts("Não existem filas.");
                    getchar();
                    break;
                }
                puts("Mostrar elementos de que fila?");
                scanf("%d", &Jack.ID);
                getchar();
                pthread_create(&pth[9], NULL, TH_printFila_id, NULL);
                pthread_join(pth[9], NULL);
                puts("");
                getchar();
                break;
            
            default:
                puts("Input inválido..");
                puts("");
                getchar();
                break;
            //sem casos a adicionar
            Jack = reset_values(Jack);
            getchar();

        }//fim do switch
    }//fim do while

    return 0;
}

