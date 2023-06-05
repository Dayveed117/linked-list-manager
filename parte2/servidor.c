#include "biblioteca.h"

#define FIFO1 "/tmp/fifo.1"
#define FIFO2 "/tmp/fifo.2"
#define PERMS 0666
#define SECRET "segredo"
#define PASSWD "iwantin"
#define PATH "./secretfiles/"


typedef struct TRUCK {

    FilaDeFila *Bicha;
    int ID;
    int msgID;
    char msg[100];
    
} Truck;

void *menuOpcao(void *args);
void *addMsg(void *args);
void *findElem_FilaDeFilas(void *args);
void *deleteMsg(void *args);
void *addElemFilaPrincipal();
void *verTodasFilas();
void *verApenasFila();
void *abrirFicheiro(void *args);

int readfd;
int writefd;
Truck *truck;
char mensagem[5000];
pthread_mutex_t trinco;

int main ()//ficheiro exame.c
{
	mknod(FIFO1, S_IFIFO | PERMS, 0); //cria pipes 
	mknod(FIFO2, S_IFIFO | PERMS, 0);
	truck = (Truck *) malloc( sizeof(Truck) );	
	truck->Bicha = NULL;

	while(1)
	{	
		readfd  = open(FIFO1, 0);
		writefd = open(FIFO2, 1);
		
		pthread_t s;
		pthread_create(&s, 0, menuOpcao, NULL);
		pthread_join(s, NULL);
	
				
	}
	return 0;
}

void *menuOpcao(void *args)
{
	int op;
	int ID, msgID;
	char content[100];
	pthread_t thread;

	read(readfd, &op, sizeof(int));

	//fprintf(stdout, "Logger: %d\n",op);

	switch(op)
	{
		case 1: 
			fprintf(stdout,"%d\n", op);
			pthread_mutex_lock( &trinco);
			read(readfd, &ID, sizeof(int));
			read(readfd, &msgID, sizeof(int));
			
			truck->ID = ID;
			truck->msgID = msgID;

			pthread_create(&thread, 0, findElem_FilaDeFilas, (void*) truck);
			pthread_join(thread, NULL);			

			pthread_mutex_unlock( &trinco);			
			break;

		case 2:
			pthread_mutex_lock( &trinco);

			read(readfd, &ID, sizeof(int));
			read(readfd, content, sizeof(char)*100);

			truck->ID = ID;
			strcpy(truck->msg, content);


			pthread_create(&thread, 0, addMsg, (void*) truck);
			pthread_join(thread, NULL);

			pthread_mutex_unlock( &trinco);
			break;

		case 3:
			pthread_mutex_lock( &trinco);

			read(readfd, &ID, sizeof(int));
			read(readfd, &msgID, sizeof(int));
			
			truck->ID = ID;
			truck->msgID = msgID;
			
			pthread_create(&thread, 0, deleteMsg, (void*) truck);
			pthread_join(thread, NULL);
			
			pthread_mutex_unlock( &trinco);		
			break;
		case 4:
			truck->ID = -1;
			truck->msgID = -1;

			pthread_create(&thread, 0, addElemFilaPrincipal, NULL);
			pthread_join(thread, NULL);
			break;

		case 5:
			pthread_create(&thread, 0, verTodasFilas, NULL);
			pthread_join(thread, NULL);
			break;
			
		case 6: 
			read(readfd, &ID, sizeof(int));

			truck->ID = ID;
			pthread_create(&thread, 0, verApenasFila, NULL);
			pthread_join(thread, NULL);
			break;

		case 7:			
			pthread_mutex_lock( &trinco);
			
			read(readfd, content, sizeof(char)*100);
			strcpy(truck->msg, content);

			pthread_create(&thread, 0, abrirFicheiro, NULL);
			pthread_join(thread, NULL);

			pthread_mutex_unlock( &trinco);

			break;		

		case 8:
			printf("Saiu um utilizador.\n");
			break;			
	}		


	return NULL;
}

void *addMsg(void *args) 
{
	Truck *T = (Truck*)args;
	char messageF[100]= "Nao existe a Fila. Tem de criar uma fila.\n";
	char messageS[100]= "Foi criada com sucesso a mensagem.\n";
	FilaDeFila *filaD;

	if(T != NULL)
	{
		if(T->Bicha == NULL)
			T->Bicha = addElemFilaDeFila( T->Bicha);
		
		filaD = findFilaDeFila(T->Bicha, T->ID);
			
		if( filaD == NULL)
		{		
			write(writefd, messageF, sizeof(char) * 5000);
			return NULL;
		}
		
		filaD->elemento = addElemFila(filaD->elemento, T->msg);
		write( writefd, messageS, sizeof(char)*5000);
	}
	else
		write( writefd, messageF, sizeof(char)*5000);

	return NULL;
}

void *findElem_FilaDeFilas(void *args)
{
	Truck *T = (Truck*)args;
	FilaDeFila *head;
	Fila *elemento;

	if(T == NULL)
		return NULL;

	if(T->Bicha == NULL)
	{
		strcpy(mensagem, "Não existe essa Fila referida.\n");
		write(writefd, mensagem, sizeof(char) * 5000);
		return NULL;
	}

	head = T->Bicha;

	while (T->Bicha != NULL) 
	{
		//printf("Bicha\n");
		if(T->Bicha->ID == T->ID)
		{
			//printf("MSG ID %d\n",T->msgID);
			if(T->Bicha->elemento != NULL)
			{
				elemento = getElem(T->Bicha->elemento, T->msgID);
				//printf("%d\n", elemento==NULL);
				
				if(elemento != NULL)
				{
					sprintf(mensagem, "Fila %d -> msgID %d, content \"%s\"\n", T->ID, elemento->msgId, elemento->content); 

					//printf("%s\n", mensagem);
				
					write(writefd, mensagem, sizeof(char) * 5000);
					
					T->Bicha = head;
			
					return NULL;
				}
			}
		}
		
		T->Bicha = T->Bicha->next;
	}

	T->Bicha = head;

	strcpy(mensagem, "Não existe essa msgId na Fila referida.\n");
	write(writefd, mensagem, sizeof(char) * 5000);

	return NULL;
}


void *deleteMsg(void *args) 
{

	Truck *T = (Truck*)args;
	FilaDeFila *head;
	Fila *elemento;

	if(T == NULL)
		return NULL;

	if(T->Bicha == NULL)
	{
		strcpy(mensagem, "Não foi possível remover a mensagem, porque não existe a Fila referida.\n");
		write(writefd, mensagem, sizeof(char) * 5000);
		return NULL;
	}

	head = T->Bicha;

	while (T->Bicha != NULL) 
	{
		//printf("Bicha\n");
		if(T->Bicha->ID == T->ID)
		{
			//printf("MSG ID %d\n",T->msgID);
			if(T->Bicha->elemento != NULL)
			{
				elemento = getElem(T->Bicha->elemento, T->msgID);
				//printf("%d\n", elemento==NULL);
				
				if(elemento != NULL)
				{
					sprintf(mensagem, " Foi eliminada com sucesso a mensagem: Fila %d -> msgID %d, content \"%s\"\n", T->ID, elemento->msgId, elemento->content); 

					T->Bicha->elemento = deleteElem(T->Bicha->elemento, T->msgID);
					

					//printf("%s\n", mensagem);
				
					write(writefd, mensagem, sizeof(char) * 5000);
					
					T->Bicha = head;
			
					return NULL;
				}
			}
		}
		
		T->Bicha = T->Bicha->next;
	}

	T->Bicha = head;

	strcpy(mensagem, "Não foi possível remover a mensagem, porque não existe a mensagem com esse msgId na Fila referida.\n");
	write(writefd, mensagem, sizeof(char) * 5000);

	return NULL;
}

void *addElemFilaPrincipal()
{
	
	if(truck == NULL)
	{
		return NULL;
	}
	
	pthread_mutex_lock( &trinco);
	
	truck->Bicha = addElemFilaDeFila(truck->Bicha);
	strcpy(mensagem, "Foi criado com sucesso a nova Fila.\n");
	write(writefd, mensagem, sizeof(char) * 5000);
	
	pthread_mutex_unlock( &trinco);

	return NULL;
}

void *verTodasFilas()
{
	
	if(truck == NULL)
	{
		return NULL;
	}
	
	pthread_mutex_lock( &trinco);

	printFilaDeFilas(truck->Bicha , mensagem);
	write(writefd, mensagem, sizeof(char) * 5000);

	pthread_mutex_unlock( &trinco);
	
	return NULL;
}

void *verApenasFila()
{
	FilaDeFila *elemento;	

	if(truck == NULL)
	{
		return NULL;
	}
	
	pthread_mutex_lock( &trinco);
	elemento = findFilaDeFila(truck->Bicha ,truck->ID);
	
	if(elemento == NULL)
	{
		strcpy(mensagem, "Não existe nenhuma Fila com esse ID.\n");
		write(writefd, mensagem, sizeof(char) * 5000);
		return NULL;
	}
	printf("%d\n",elemento->ID);
	printUmaFila(elemento , mensagem);
	//printf("%s\n",mensagem);
	write(writefd, mensagem, sizeof(char) * 5000);

	pthread_mutex_unlock( &trinco);
	
	return NULL;
}


void *abrirFicheiro(void *args) {

	const char pass[100] = PASSWD;
	const char segredo[100] = SECRET;
	char caminho[100] = PATH;
	char msg[100];
	int fich, n;
	int um = 1;
	int zero = 0;

	memset(mensagem, 0, sizeof(char)*5000 );

	//compara a mensagem que vem no truck
	if(strcmp(segredo, truck->msg) == 0) 
	{
		write(writefd, &um, sizeof(int));//1
		read(readfd, msg, sizeof(char)*100);//2
		if(strcmp(msg, pass) == 0) {
			write(writefd, &um, sizeof(int));//3
			read(readfd, &msg, sizeof(char)*100);//4
			strcat(caminho, msg);
			fich = open(caminho, O_RDONLY);
			if(fich < 0)
				write(writefd, &zero, sizeof(int));//5
			else {
				write(writefd, &um, sizeof(int));//5
				while ((n = read(fich, mensagem, sizeof(char)*5000)) > 0);
				write(writefd, mensagem, sizeof(char)*5000);//6
			}
		}
		else {
			write(writefd, &zero, sizeof(int));//3
		}
	}
	else {//ficheiro normal
		write(writefd, &zero, sizeof(int));//1
		fich = open(truck->msg, O_RDONLY);
		
		if(fich < 0) 
			write(writefd, &um, sizeof(int));//2
		else {
			write(writefd, &zero, sizeof(int));//2
			//encher o buffer mensagem
			while ((n = read(fich, mensagem, sizeof(char)*5000)) > 0);
			write(writefd, mensagem, sizeof(char)*5000);//3
		}
	}

	return NULL;
}


















