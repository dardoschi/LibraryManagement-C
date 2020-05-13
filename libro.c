#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "libro.h"

#define max 100

//crea la struttura del libro
libro *CreaLibro(char *titolo, int disp){
    libro *nuovoLibro = (libro *)malloc(sizeof(libro));
    if(!nuovoLibro) return NULL;

    strcpy(nuovoLibro->titolo, titolo);
    nuovoLibro->disp = disp;
    nuovoLibro->next = NULL;
    
    return nuovoLibro;
}

//inserimento in coda
libro *InserisciCoda(libro *libreria, char *titolo, int disp){
    if(libreria == NULL) return CreaLibro(titolo, disp);
    libreria->next = InserisciCoda(libreria->next, titolo, disp);
    return libreria;
 }


//legge file e crea lista
libro *LeggiFile(libro *libreria, FILE *fp){
    char titolo[max];
    int disp;

    while(fscanf(fp,"%s %d", titolo ,&disp) == 2){
        libreria = InserisciCoda(libreria, titolo, disp);
    }
    return libreria;
 }


 //stampa lista
 void StampaLibri(libro *libreria){
     if(libreria != NULL){
         printf("%s %d\n", libreria->titolo, libreria->disp);
         StampaLibri(libreria->next);
     }
 }

int LunghezzaLista(libro *lista){
  if(!lista) return 0;
  return(1 + LunghezzaLista(lista->next));
}

//funzione check -> boolean -> ok/no
bool checkinlista(char *titolo, libro *libreria){
    if(libreria != NULL){   //strcmp(str1,str2)ritorna 0 se ugual
        if(strcmp(titolo, libreria->titolo) == 0){
            return true;
        } 
        checkinlista(titolo, libreria->next);
    }
}


libro *getlibro(char *titolo, libro *libreria){
    libro *tmp = (libro *)malloc(sizeof(libro));
    if(libreria != NULL){
        if(strcmp(titolo, libreria->titolo) == 0){
            strcpy(tmp->titolo, libreria->titolo);
            tmp->disp = libreria->disp;
            return tmp;
        }else{
            free(tmp);//tmp non viene utilizzato in questa chiamata
            getlibro(titolo, libreria->next);
        }
    }
}

void modificalibro(libro *nuovo, libro *libreria){
    if(libreria != NULL){
        if(strcmp(nuovo->titolo, libreria->titolo) == 0){
            libreria->disp = nuovo->disp;
            printf("\nLibreria aggiornata\n");
        }
        modificalibro(nuovo, libreria->next);
    }
}

void StampaLibriStudente(libro *libreria){
     if(libreria != NULL){
         printf("%s \n", libreria->titolo);
         StampaLibriStudente(libreria->next);
     }
 }