#include "SpolocneData.h"

void * vykreslovanieF(void * arg) {

    SPOL * spolData = arg;
    curs_set(0);
    char * body1[10];
    char * body2[10];

    // PLOCHA
    mvprintw(0,0 , "----------------------------------------------------------------------------------------------------");
    mvprintw(29,0 , "----------------------------------------------------------------------------------------------------");

    //skore
    mvprintw(0,105 , "Skore hrac 1: ");
    mvprintw(1,105 , "Skore hrac 2: ");
    //skore

    for (int i = 0; i < 30; i++) {
        mvprintw(i,0 , "I");
        mvprintw(i,100 , "I");
    }
    // PLOCHA KONIEC

    while (spolData->quit == 0) {
        //clear();
        for (int i = 1; i < 29; ++i) {
            for (int j = 1; j < 100; ++j) {
                mvaddch(i, j, ' ');
            }
        }
        //skore
        sprintf(body1, "%d", spolData->bodyHracJeden);
        sprintf(body2, "%d", spolData->bodyHracDva);
        mvprintw(0,120 , body1);
        mvprintw(1,120 , body2);
        //skore koniec

        //lopta
        mvaddch(spolData->objekty->loptaY, spolData->objekty->loptaX , '*');
        //lopta koniec

        //HRAC1
        mvaddch(spolData->objekty->hrac1Y, spolData->objekty->hrac1X , '|');
        mvaddch(spolData->objekty->hrac1Y +1, spolData->objekty->hrac1X , '|');
        mvaddch(spolData->objekty->hrac1Y +2, spolData->objekty->hrac1X , '|');
        mvaddch(spolData->objekty->hrac1Y +3, spolData->objekty->hrac1X , '|');
        mvaddch(spolData->objekty->hrac1Y +4, spolData->objekty->hrac1X , '|');
        //HRAC1 KONIEC

        //HRAC2
        mvaddch(spolData->objekty->hrac2Y, spolData->objekty->hrac2X , '|');
        mvaddch(spolData->objekty->hrac2Y +1, spolData->objekty->hrac2X , '|');
        mvaddch(spolData->objekty->hrac2Y +2, spolData->objekty->hrac2X , '|');
        mvaddch(spolData->objekty->hrac2Y +3, spolData->objekty->hrac2X , '|');
        mvaddch(spolData->objekty->hrac2Y +4, spolData->objekty->hrac2X , '|');
        //HRAC2 KONIEC

        //refresh();
        //napms(100);
        usleep(1000);
    }

    pthread_exit(NULL);
}