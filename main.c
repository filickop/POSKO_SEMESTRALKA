#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include "Server.c"
#include "Client.c"

int main(int argc, char *argv[])
{
    char *buff[10];
    char *str[20];
     do{
        printf("1. Server\n");
        printf("2. Klient\n");
        printf("3. Vypnutie\n");
        bzero(buff,10);
        fgets(buff,10, stdin);
        if(atoi(buff) == 1 || atoi(buff) == 2) {
            break;
        } else if(atoi(buff) == 3) {
            return 0;
        }
         printf("zadali ste nespravnu hodnotu\n");
    }while (true);

    if (atoi(buff) == 1) {

        do{
            printf("Vlozte cislo portu (1025-65535):\n");
            bzero(str,20);
            fgets(str,20, stdin);
            if(atoi(str) > 1025 && atoi(str) < 65535){
                break;
            }
            printf("Zadali ste nespravne cislo portu\n");
        } while (1);

        spustenieServera(str);

    }
    else if(atoi(buff) == 2) {

        do{
            printf("Vlozte cislo portu (1025-65535):\n");
            bzero(str,20);
            fgets(str,20, stdin);
            if(atoi(str) > 1025 && atoi(str) < 65535){
                break;
            }
            printf("Zadali ste nespravne cislo portu\n");
        } while (1);
        spustenieKlientaClient(str);
    }


    return 0;
}