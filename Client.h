#include "SpolocneData.h"
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

#ifndef SEMESTRALKA_POSKO_CLIENT_H
#define SEMESTRALKA_POSKO_CLIENT_H


void * zapisFClient(void * arg);
void * nacitavanieFClient(void * arg);
bool spustenieKlientaClient(char *str[]);
void * hrac2F(void * arg);


#endif //SEMESTRALKA_POSKO_CLIENT_H
