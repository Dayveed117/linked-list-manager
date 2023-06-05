#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h> 

#define FIFO1 "/tmp/fifo.1"
#define FIFO2 "/tmp/fifo.2"
#define PERMS 0666
#define SR sizeof(float)

void menuFuncao();
void menuOpcao();

int op;

int main ()//ficheiro exame.c
{
	int writefd = open(FIFO1, 1);
	int readfd =open(FIFO2, 0);
	
	while(1)
	{
		menuOpcao(writefd, readfd);

		if(op == '7')
		{
			printf("A fechar o programa");
			exit(1);
		}
	}

	return 0;
}

void menuFuncao()
{
	printf("Menu Principal:\n");
	printf("\t1 - Visualizar mensagem\n");
	printf("\t2 - Inserir uma mensagem\n");
	printf("\t3 - Apagar uma mensagem\n");
	printf("\t4 - Criar uma nova fila\n");
	printf("\t5 - Listar filas existentes\n");
	printf("\t6 - Ver todas as mensagens de uma fila\n");
	printf("\t7 - Abrir um ficheiro\n");
	printf("\t8 - Sair\n");
	printf("Escolha uma opção: \n");

}

void menuOpcao(int writefd, int readfd)
{
	int ID, msgId, flag;	
	char content[100];
	char mensagem[5000];


	menuFuncao();

	scanf("%d", &op);
	write(writefd, &op, sizeof(int));

	switch(op)
	{
		case 1: 
			printf("Introduza o ID da fila que prentede visualizar:\n");
			scanf("%d", &ID);
			printf("Introduza o msgID lista de mensagem que deseja:\n");
			scanf("%d", &msgId);

			write(writefd, &ID,     sizeof(int));
			write(writefd, &msgId,  sizeof(int));
			read(readfd, mensagem, sizeof(char) * 5000);	

			printf("%s",mensagem);		
			break;
		
		case 2:
			
			printf("Introduza o ID da fila onde prentede inserir a mensagem:\n");
			scanf("%d", &ID);
			
			getchar();//engolir a \n da cima

			printf("Introduza a mensagem:\n");
			fflush(stdout);
			gets(content);

			//printf("<%s>\n",content);

			write(writefd, &ID, sizeof(int));			
			write(writefd, content, sizeof(char)* 100);
			//printf("writes done\n");
			read(readfd, mensagem, sizeof(char) * 5000);
			printf("%s\n",mensagem);			
			break;
		
		case 3:
			printf("Introduza o ID da Fila:\n");
			scanf("%d",&ID);
			printf("Introduza o msgId do elemento que deseja:\n");
			scanf("%d",&msgId);

			write(writefd, &ID, sizeof(int));
			write(writefd, &msgId, sizeof(int));
			read(readfd, mensagem, sizeof(char) * 5000);

			printf("%s\n",mensagem);	
			break;

		case 4:
			read(readfd, &mensagem, sizeof(char) * 5000);
			printf("%s\n",mensagem);	
			break;

		case 5:
			read(readfd, &mensagem, sizeof(char) * 5000);
			printf("%s\n",mensagem);	
			break;
		
		case 6: 
			printf("Introduza a Fila que prentede ver:\n");
			scanf("%d",&ID);
	
			write(writefd, &ID, sizeof(int));
			read(readfd, mensagem, sizeof(char)*5000);
			printf("%s\n",mensagem);	
			break;
			
		case 7:
			printf("Introduza o ficheiro que pretende ver:\n");
			getchar();
			gets(content);

			write(writefd, content, sizeof(char)*100);//0
			//ver se é secreto
			read(readfd, &flag, sizeof(int));//1
			if(flag == 1) {
				printf("Introduza a password:\n");
				fflush(stdout);
				gets(content);
				write(writefd, content, sizeof(char)* 100);//2
				read(readfd, &flag, sizeof(int));//3
				if (flag == 1) {//tentar aceder ao ficheiro secreto
					printf("Introduza o ficheiro secreto:\n");
					fflush(stdout);
					gets(content);
					write(writefd, content, sizeof(char)* 100);//4
					read(readfd, &flag, sizeof(int));//5
					if (flag == 1) {
						printf("Opening: %s\n", content);
						read(readfd, mensagem, sizeof(char) * 5000);//6
						printf("%s\n",mensagem);	
					}
					else 
						printf("Erro ao abrir o ficheiro.\n");					
				}	
				else {
					printf("Password incorreta.\n");
				}
			}//ficheiro normal
			else {
				read(readfd, &flag, sizeof(int));//2
				if(flag == 1) {
					printf("Erro ao abrir o ficheiro\n");
				}
				else {
					read(readfd, mensagem, sizeof(char)*5000);//3
					printf("\n%s\n",mensagem);			
				}
			}
			break;
		case 8:
			exit(0);
		
		default: 
			printf("Opção inválida introduza de novo!");
	}		




}
