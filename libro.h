#ifndef LIBRO_H
#define LIBRO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define max 100

typedef struct libro{
    char titolo[max];
    int disp;
    struct libro *next;
}libro ;

libro *CreaLibro(char *titolo, int disp);
libro *InserisciCoda(libro *libreria, char *titolo, int disp);
libro *LeggiFile(libro *libreria, FILE *fp);
void StampaLibri(libro *libreria);
int LunghezzaLista( libro *lista);
bool checkinlista(char *titolo,libro *libreria);
libro *getlibro(char *titolo, libro *libreria);
void modificalibro(libro *nuovo,libro *libreria);
void StampaLibriStudente(libro *libreria);

#endif