#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "studente.h"

studente *CreaStudente(int matricola, char *titolo){
    studente *nuovostud = (studente *)malloc(sizeof(studente));
    if(!nuovostud) return NULL;

    nuovostud->matricola = matricola;
    strcpy(nuovostud->libroprestato, titolo);
    nuovostud->next = NULL;
    return nuovostud;
}

studente *InserisciCodaStudente(studente *listaStudenti, int matricola, char *titolo){
    if(listaStudenti == NULL) return CreaStudente(matricola, titolo);
    if(checkinlistastudenti(matricola, listaStudenti) == true){
        printf("\nLo studente %d ha gi un libro in prestito.\n", matricola);
        return listaStudenti;
    }
    listaStudenti->next = InserisciCodaStudente(listaStudenti->next, matricola, titolo);
    return listaStudenti;
}


studente *EliminaStudente(int matricola, studente *listaStudenti){
    if(!listaStudenti) return NULL;
    if(listaStudenti->matricola == matricola) return EliminaStudente(matricola, listaStudenti->next);
    listaStudenti->next = EliminaStudente (matricola, listaStudenti->next);
    return listaStudenti;
}

void stampaListaStudenti(studente *listaStudenti){
    if(listaStudenti != NULL){
        printf("%d ha in prestito ", listaStudenti->matricola);
        printf("%s\n", listaStudenti->libroprestato);
        stampaListaStudenti(listaStudenti->next);
    } 
}


bool checkinlistastudenti(int matricola, studente *listaStudenti){
    if(listaStudenti != NULL){
        if(matricola == listaStudenti->matricola){
            return true;
        } 
        checkinlistastudenti(matricola, listaStudenti->next);
    }else
    {
        return false;
    }
       
}


bool possiedelibro(int matricola, char *titolo, studente *listaStudenti){
    if(listaStudenti != NULL){
        if(matricola == listaStudenti->matricola){
            if(strcmp(titolo, listaStudenti->libroprestato) == 0){
                return true;
            }
        }
        possiedelibro(matricola, titolo, listaStudenti->next);
    }else
    {
        return false;
    }
    
}

int LunghezzaListaStudenti(studente *lista){
  if(!lista) return 0;
  return(1 + LunghezzaListaStudenti(lista->next));
}