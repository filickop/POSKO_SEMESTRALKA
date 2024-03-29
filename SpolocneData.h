#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include <pthread.h>
#include <ncurses.h>

#ifndef SEMESTRALKA_POSKO_SPOLOCNEDATA_H
#define SEMESTRALKA_POSKO_SPOLOCNEDATA_H

typedef struct objekty {
    int hrac1X;
    int hrac1Y;
    int hrac2X;
    int hrac2Y;
    int loptaX;
    int loptaY;
} OBJEKTY;

typedef struct spolData {
    OBJEKTY * objekty;
    int bodyHracJeden;
    int bodyHracDva;
    int quit;
    int newsocketfd;
    pthread_mutex_t * mut;
} SPOL;


void * vykreslovanieF(void * arg);

#endif //SEMESTRALKA_POSKO_SPOLOCNEDATA_H
