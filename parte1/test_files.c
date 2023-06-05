#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define secret "segredo"
#define passwd "iwantin"
#define path "./secretfiles/"

#define MSG_SIZE 100
#define FILE_SIZE 1000

typedef struct {
    char s[MSG_SIZE];
}string;

int main() {

    const char pass[MSG_SIZE] = passwd;
    const char segredo[MSG_SIZE] = secret;
    char caminho[MSG_SIZE] = path;
    char *file = malloc(FILE_SIZE*sizeof(char));
    string s;
    int fich, n;


    
    puts("Qual o ficheiro a aceder?");
    scanf("%s", s.s);
    getchar();

    if(strcmp(segredo, s.s) == 0) {

        puts("Queres aceder a um segredo?");
        puts("Qual a password?");
        scanf("%s", s.s);
        getchar();
        
        if(strcmp(pass, s.s) == 0) {
            puts("Qual o ficheiro a que queres aceder então?");
            scanf("%s", s.s);
            getchar();
            strcat(caminho, s.s);

            fich = open(caminho, O_RDONLY);
            if(fich < 0)
                perror("Erro ao abrir.");
            else {//abrir ficheiro secreto
                printf("Opening: %s\n", caminho);
                while(read(fich, file, FILE_SIZE) > 0) {
                    puts(file);
                }
            }
        }
        else {//password errada
            puts("Password errada.");
        }
    }
    else {//abrir ficheiro normal
        fich = open(s.s, O_RDONLY);
        if(fich < 0)
            perror("Erro ao abrir.\n");
        else {
            printf("Opening: %s\n", s.s);
            while ((n = read(fich, file, FILE_SIZE)) > 0) {
                puts(file); 
            }
        }
    }

    return 0;
}