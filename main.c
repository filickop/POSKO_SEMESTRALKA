#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <SDL2/SDL.h>
#include <pthread.h>

typedef struct spolData {
    int bodyHracJeden;
    int bodyHracDva;
    int quit;
    int newsocketfd;
    //char pole[100][50];
    int hrac1X;
    int hrac1Y;
    int hrac2X;
    int hrac2Y;
    int loptaX;
    int loptaY;
    pthread_mutex_t * mut;
    pthread_cond_t * citaj;
    pthread_cond_t * odosielaj;
} SPOL;

void * hrac1F(void * arg) {


}

void * nacitavanieF(void * arg) {
    SPOL * spolData = arg;
    int n;
    int temp[6];
    char buffer[256];
    char *token;
    while(spolData->quit == 0) {
        sleep(5);
        printf("asd\n");
        printf("%d;%d;%d;%d;%d;%d\n",
               spolData->hrac1X, spolData->hrac1Y,
               spolData->hrac2X, spolData->hrac2Y,
               spolData->loptaX, spolData->loptaY);
        bzero(buffer,256);
        printf("try2\n");
        n = read(spolData->newsocketfd, buffer, 255);
        printf("tr3%d\n",n);
        if (n < 0)
        {
            printf("try\n");
            perror("Error reading from socket");
            //return 4;
            break;
        }

        token = strtok(buffer, ";");
        printf("zxc%s\n",token);
        temp[0] = atoi(token);
        printf("zxc%d\n",temp[0]);
        token = strtok(NULL, ";");
        temp[1] = atoi(token);
        token = strtok(NULL, ";");
        temp[2] = atoi(token);
        token = strtok(NULL, ";");
        temp[3] = atoi(token);
        token = strtok(NULL, ";");
        temp[4] = atoi(token);
        token = strtok(NULL, ";");
        temp[5] = atoi(token);


        if(temp[3] != 0) {
            pthread_mutex_lock(spolData->mut);

            spolData->hrac1X = temp[0];
            spolData->hrac1Y = temp[1];
            spolData->hrac2X = temp[2];
            spolData->hrac2Y = temp[3];
            spolData->loptaX = temp[4];
            spolData->loptaY = temp[5];

            pthread_mutex_unlock(spolData->mut);

        }

        printf("qwe%d;%d;%d;%d;%d;%d\n",
               spolData->hrac1X, spolData->hrac1Y,
               spolData->hrac2X, spolData->hrac2Y,
               spolData->loptaX, spolData->loptaY);

    }
}

void * zapisF(void * arg) {

    SPOL * spolData = arg;
    int n;
    char buffer[256];


    while(spolData->quit == 0) {
        sleep(5);
        bzero(buffer, 256);
        pthread_mutex_lock(spolData->mut);


        sprintf(buffer, "%d;%d;%d;%d;%d;%d",
                spolData->hrac1X, spolData->hrac1Y,
                spolData->hrac2X, spolData->hrac2Y,
                spolData->loptaX, spolData->loptaY);
        printf("sprint%s\n", buffer);


        pthread_mutex_unlock(spolData->mut);


        n = write(spolData->newsocketfd, buffer, strlen(buffer));
        if (n < 0) {
            perror("Error writing to socket");
            //return 5;
            break;
        }
    }

}

int main(int argc, char *argv[])
{
    pthread_mutex_t mut;
    pthread_cond_t citaj;
    pthread_cond_t odosielaj;
    SPOL spolData;
    spolData.bodyHracDva = 0;
    spolData.bodyHracJeden = 0;

    spolData.hrac1X = 0;
    spolData.hrac1Y = 25;

    spolData.hrac2X = 99;
    spolData.hrac2Y = 25;

    spolData.loptaX = 50;
    spolData.loptaY = 25;

    //for(int i = 0; i < 100; i++) {
    //    for(int j = 0; j < 50; j++) {
    //        spolData.pole[i][j] = '0';
    //    }
    //}
    //HRAC 1
   // spolData.pole[0][23] = '1';
    //spolData.pole[0][24] = '1';
    //spolData.pole[0][25] = '1';
    //spolData.pole[0][26] = '1';
    //spolData.pole[0][27] = '1';
    //HRAC 2
   // spolData.pole[99][23] = '2';
    //spolData.pole[99][24] = '2';
   // spolData.pole[99][25] = '2';
   // spolData.pole[99][26] = '2';
   // spolData.pole[99][27] = '2';
    //LOPTA
   // spolData.pole[50][25] = 'o';

    pthread_mutex_init(&mut, NULL);
    pthread_cond_init(&citaj, NULL);
    pthread_cond_init(&odosielaj, NULL);
    spolData.mut = &mut;
    spolData.odosielaj = &odosielaj;
    spolData.citaj = &citaj;

    pthread_t nacitavanie;
    pthread_t zapis;
    pthread_t hrac1;

    int sockfd, newsockfd;
    socklen_t cli_len;
    struct sockaddr_in serv_addr, cli_addr;
    int n;
    char buffer[256];

    if (argc < 2)
    {
        fprintf(stderr,"usage %s port\n", argv[0]);
        return 1;
    }

    bzero((char*)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(atoi(argv[1]));

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("Error creating socket");
        return 1;
    }

    if (bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("Error binding socket address");
        return 2;
    }

    listen(sockfd, 5);
    cli_len = sizeof(cli_addr);

    newsockfd = accept(sockfd, (struct sockaddr*)&cli_addr, &cli_len);
    if (newsockfd < 0)
    {
        perror("ERROR on accept");
        return 3;
    }

    spolData.newsocketfd = newsockfd;

    pthread_create(&hrac1, NULL, hrac1F, &spolData);
    pthread_create(&nacitavanie, NULL, nacitavanieF, &spolData);
    pthread_create(&zapis, NULL, zapisF, &spolData);

    //pthread_join(hrac1, NULL);
    pthread_join(zapis, NULL);
    pthread_join(nacitavanie, NULL);
    //TODO VLAKNO NA VYKRESLOVANIE


    pthread_mutex_destroy(&mut);
    pthread_cond_destroy(&zapis);
    pthread_cond_destroy(&nacitavanie);

    close(newsockfd);
    close(sockfd);

    return 0;
}