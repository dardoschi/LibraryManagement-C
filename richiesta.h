#ifndef RICHIESTA_H
#define RICHIESTA_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "libro.h"
#include "studente.h"

#define max 100

typedef struct richiesta{
    char titolo[max];
    bool tipo; // 0vfalse richiedi --- 1vtrue restituisci
    int matricola;
    struct richiesta *next;
}richiesta;


typedef struct coda{
    richiesta *head;
    richiesta *tail;
}coda;


richiesta *creanodo(char *titolo, bool tipo, int matricola);
int codavuota(coda *Q);
void creacoda(coda *Q);
void enqueue(coda *Q, char *titolo, bool tipo, int matricola);
void leggicoda(coda *Q);
void leggitesta(coda *Q);
studente *eseguirichiesta(richiesta *rich, libro *libreria, studente *listaStudenti);
richiesta *copiatesta(coda *Q);
void dequeue(coda *Q, richiesta *rich);

#endif