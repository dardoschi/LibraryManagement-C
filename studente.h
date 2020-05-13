#ifndef STUDENTE_H
#define STUDENTE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libro.h"

#define max 100

typedef struct studente{
    int matricola;
    char libroprestato[max];
    struct studente *next;
}studente;

studente *CreaStudente(int matricola, char* titolo);
studente *InserisciCodaStudente(studente *listaStudenti, int matricola, char *titolo);
void stampaListaStudenti(studente *listaStudenti);
bool checkinlistastudenti(int matricola, studente *listaStudenti);
bool possiedelibro(int matricola, char *titolo, studente *listaStudenti);
studente *EliminaStudente(int matricola, studente *listaStudenti);
int LunghezzaListaStudenti(studente *lista);

#endif