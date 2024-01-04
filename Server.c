#include "Server.h"
#include "SpolocneData.c"

bool spustenieServera(char * str[]){

    initscr();
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
    pthread_t hrac1;
    pthread_t logika;

    int sockfd, newsockfd;
    socklen_t cli_len;
    struct sockaddr_in serv_addr, cli_addr;
    int n;
    char buffer[256];

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(atoi(str));

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error creating socket");
        return 1;
    }

    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("Error binding socket address");
        return 2;
    }

    listen(sockfd, 5);
    cli_len = sizeof(cli_addr);

    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &cli_len);
    if (newsockfd < 0) {
        perror("ERROR on accept");
        return 3;
    }

    spolData.newsocketfd = newsockfd;

    pthread_create(&hrac1, NULL, hrac1F, &spolData);
    pthread_create(&nacitavanie, NULL, nacitavanieF, &spolData);
    pthread_create(&zapis, NULL, zapisF, &spolData);
    pthread_create(&vykreslovanie, NULL, vykreslovanieF, &spolData);
    pthread_create(&logika, NULL, logikaLopty, &spolData);

    pthread_join(hrac1, NULL);
    pthread_join(zapis, NULL);
    pthread_join(nacitavanie, NULL);
    pthread_join(vykreslovanie, NULL);
    pthread_join(logika, NULL);

    pthread_mutex_destroy(&mut);
    close(spolData.newsocketfd);
    close(sockfd);
}

void * hrac1F(void * arg) {
    SPOL * spolData = arg;
    int ch;

    keypad(stdscr, TRUE);


    while (spolData->quit == 0) {
        usleep(1000);
        timeout(0);
        ch = getch();
        switch (ch) {
            case KEY_UP:
                if (spolData->objekty->hrac1Y - 1 >= 1) {
                    spolData->objekty->hrac1Y--;
                }
                break;
            case KEY_DOWN:
                if (spolData->objekty->hrac1Y + 1 <= 24) {
                    spolData->objekty->hrac1Y++;
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

void * nacitavanieF(void * arg) {
    SPOL * spolData = arg;
    int n;
    int temp[9];
    char buffer[256];
    char *token;
    while(spolData->quit == 0) {
        usleep(1000);
        //printf("%d;%d;%d;%d;%d;%d\n",
        //       spolData->hrac1X, spolData->hrac1Y,
        //       spolData->hrac2X, spolData->hrac2Y,
        //       spolData->loptaX, spolData->loptaY);
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
        token = strtok(NULL, ";");
        temp[8] = atoi(token);


        if(temp[3] != 0) {
            pthread_mutex_lock(spolData->mut);

            //spolData->objekty->hrac1X = temp[0];
            //spolData->objekty->hrac1Y = temp[1];
            spolData->objekty->hrac2X = temp[2];
            spolData->objekty->hrac2Y = temp[3];
            //spolData->objekty->loptaX = temp[4];
            //spolData->objekty->loptaY = temp[5];
            //spolData->bodyHracJeden = temp[6];
            //spolData->bodyHracDva = temp[7];

            pthread_mutex_unlock(spolData->mut);

        }

        //printf("qwe%d;%d;%d;%d;%d;%d\n",
        //       spolData->objekty->hrac1X, spolData->objekty->hrac1Y,
        //       spolData->objekty->hrac2X, spolData->objekty->hrac2Y,
        //       spolData->objekty->loptaX, spolData->objekty->loptaY);

    }
    pthread_exit(NULL);
}

void * zapisF(void * arg) {

    SPOL * spolData = arg;
    int n;
    char buffer[256];

    while(spolData->quit == 0) {
        usleep(1000);
        bzero(buffer, 256);
        pthread_mutex_lock(spolData->mut);


        sprintf(buffer, "%d;%d;%d;%d;%d;%d;%d;%d;%d",
                spolData->objekty->hrac1X, spolData->objekty->hrac1Y,
                spolData->objekty->hrac2X, spolData->objekty->hrac2Y,
                spolData->objekty->loptaX, spolData->objekty->loptaY,
                spolData->bodyHracJeden, spolData->bodyHracDva,0);
        //printf("sprint%s\n", buffer);


        pthread_mutex_unlock(spolData->mut);


        n = write(spolData->newsocketfd, buffer, strlen(buffer));
        if (n < 0) {
            perror("Error writing to socket");
            //return 5;
            break;
        }
    }
    pthread_exit(NULL);

}

void * logikaLopty(void * arg) {
    SPOL * spolData = arg;
    int skorovane;
    int smerLoptyX;
    int smerLoptyY;
    int rychlost;
    while (spolData->quit == 0) {
        if (rand()%1 == 1) {
            smerLoptyX = 1;
        }
        else {
            smerLoptyX = -1;
        }
        if (rand()%1 == 1) {
            smerLoptyY = 1;
        }
        else {
            smerLoptyY = -1;
        }

        skorovane = 0;
        rychlost = 200000;
        pthread_mutex_lock(spolData->mut);

        spolData->objekty->loptaX = 50;
        spolData->objekty->loptaY = rand()%27;


        pthread_mutex_unlock(spolData->mut);
        while (skorovane == 0 && spolData->quit == 0){

            usleep(rychlost);
            pthread_mutex_lock(spolData->mut);

            spolData->objekty->loptaX += smerLoptyX;
            spolData->objekty->loptaY += smerLoptyY;

            pthread_mutex_unlock(spolData->mut);

            if(spolData->objekty->loptaY >= 28 || spolData->objekty->loptaY <= 1) {
                smerLoptyY = smerLoptyY * -1;
            }
            if((spolData->objekty->loptaX >= 98 && spolData->objekty->loptaY >= spolData->objekty->hrac2Y && spolData->objekty->loptaY <= spolData->objekty->hrac2Y + 4)
            || (spolData->objekty->loptaX <= 2 && spolData->objekty->loptaY >= spolData->objekty->hrac1Y && spolData->objekty->loptaY <= spolData->objekty->hrac1Y + 4)) {
                smerLoptyX = smerLoptyX * -1;
                rychlost = rychlost * 0.8;
            }
            if(spolData->objekty->loptaX >= 99){
                pthread_mutex_lock(spolData->mut);
                spolData->bodyHracJeden++;
                pthread_mutex_unlock(spolData->mut);
                skorovane = 1;
            }
            if(spolData->objekty->loptaX <= 1){
                pthread_mutex_lock(spolData->mut);
                spolData->bodyHracDva++;
                pthread_mutex_unlock(spolData->mut);
                skorovane = 1;
            }

        }

    }
    pthread_exit(NULL);
}
