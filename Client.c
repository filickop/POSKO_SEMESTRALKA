#include "Client.h"
#include "SpolocneData.h"
#include <netdb.h>



bool spustenieKlientaClient(char *str[]) {
    initscr();
    int sockfd, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    pthread_mutex_t mut;

    SPOL spolData;
    OBJEKTY objekty;
    spolData.bodyHracDva = 0;
    spolData.bodyHracJeden = 0;
    objekty.hrac1X = 1;
    objekty.hrac1Y = 15;
    objekty.hrac2X = 99;
    objekty.hrac2Y = 15;
    objekty.loptaX = 50;
    objekty.loptaY = 25;
    spolData.objekty = &objekty;

    spolData.quit = 0;
    spolData.bodyHracJeden = 0;
    spolData.bodyHracDva = 0;
    pthread_mutex_init(&mut, NULL);

    spolData.mut = &mut;

    pthread_t nacitavanie;
    pthread_t zapis;
    pthread_t vykreslovanie;
    pthread_t hrac2;


    server = gethostbyname("localhost");
    if (server == NULL) {
        fprintf(stderr, "Error, no such host\n");
        return 2;
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy(
            (char *) server->h_addr,
            (char *) &serv_addr.sin_addr.s_addr,
            server->h_length
    );
    serv_addr.sin_port = htons(atoi(str));

    spolData.newsocketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error creating socket");
        return 3;
    }

    if (connect(spolData.newsocketfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("Error connecting to socket");
        return 4;
    }

    pthread_create(&nacitavanie, NULL, nacitavanieFClient, &spolData);
    pthread_create(&zapis, NULL, zapisFClient, &spolData);
    pthread_create(&vykreslovanie, NULL, vykreslovanieF, &spolData);
    pthread_create(&hrac2, NULL, hrac2F, &spolData);

    pthread_join(hrac2, NULL);
    pthread_join(zapis, NULL);
    pthread_join(nacitavanie, NULL);
    //printf("1\n");
    pthread_join(vykreslovanie, NULL);


    pthread_mutex_destroy(&mut);

    close(sockfd);
}

void * hrac2F(void * arg) {
    SPOL * spolData = arg;
    int ch;

    keypad(stdscr, TRUE);


    while (spolData->quit == 0) {
        usleep(1000);
        timeout(0);
        ch = getch();
        switch (ch) {
            case KEY_UP:
                if (spolData->objekty->hrac2Y - 1 >= 1) {
                    spolData->objekty->hrac2Y--;
                }
                break;
            case KEY_DOWN:
                if (spolData->objekty->hrac2Y + 1 <= 24) {
                    spolData->objekty->hrac2Y++;
                }
                break;
            case 27:
                spolData->quit = 1;
                break;
        }
    }
    endwin();
    pthread_exit(NULL);

}

void * zapisFClient(void * arg) {

    SPOL * spolData = arg;
    int n;
    char buffer[256];


    while(spolData->quit == 0) {
        usleep(10000);
        bzero(buffer, 256);
        pthread_mutex_lock(spolData->mut);

        sprintf(buffer, "%d;%d;%d;%d;%d;%d;%d;%d",
                spolData->objekty->hrac1X, spolData->objekty->hrac1Y,
                spolData->objekty->hrac2X, spolData->objekty->hrac2Y,
                spolData->objekty->loptaX, spolData->objekty->loptaY,
                spolData->bodyHracJeden, spolData->bodyHracDva);
        //printf("sprint%s\n", buffer);

        pthread_mutex_unlock(spolData->mut);

        n = write(spolData->newsocketfd, buffer, strlen(buffer));
        if (n < 0) {
            perror("Error writing to socket");
            //return 5;
            break;
        }
    }
}

void * nacitavanieFClient(void * arg) {

    SPOL * spolData = arg;
    int n;
    int temp[8];
    char buffer[256];
    char *token;
    while(spolData->quit == 0) {
        usleep(10000);

        bzero(buffer,256);
        n = read(spolData->newsocketfd, buffer, 255);
        if (n < 0)
        {
            perror("Error reading from socket");
            //return 4;
            break;
        }

        token = strtok(buffer, ";");
        temp[0] = atoi(token);
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

        token = strtok(NULL, ";");
        temp[6] = atoi(token);
        token = strtok(NULL, ";");
        temp[7] = atoi(token);

        if(temp[3] != 0) {
            pthread_mutex_lock(spolData->mut);

            spolData->objekty->hrac1X = temp[0];
            spolData->objekty->hrac1Y = temp[1];
            //spolData->objekty->hrac2X = temp[2];
            //spolData->objekty->hrac2Y = temp[3];
            spolData->objekty->loptaX = temp[4];
            spolData->objekty->loptaY = temp[5];
            spolData->bodyHracJeden = temp[6];
            spolData->bodyHracDva = temp[7];

            pthread_mutex_unlock(spolData->mut);

        }
        //printf("qwe%d;%d;%d;%d;%d;%d\n",
        //       spolData->objekty->hrac1X, spolData->objekty->hrac1Y,
        //       spolData->objekty->hrac2X, spolData->objekty->hrac2Y,
        //       spolData->objekty->loptaX, spolData->objekty->loptaY);
    }
}
