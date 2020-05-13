#include <stdbool.h>
#include <stdio.h>

#include "richiesta.h"

richiesta *creanodo(char *titolo, bool tipo, int matricola){
    richiesta *tmp;
    tmp = (richiesta *)malloc(sizeof(richiesta));
    if(!tmp) return NULL;
    else{
        tmp->next=NULL;
        strcpy(tmp->titolo, titolo);
        tmp->tipo = tipo;
        tmp->matricola = matricola;
    }
    return tmp;
}


int codavuota(coda *Q){
    return(Q->head == NULL); //true --> 1, false -->0
}

void creacoda(coda *Q){
    if(Q){
        Q->head = NULL;
        Q->tail = NULL;
    }
}


void enqueue(coda *Q, char *titolo, bool tipo, int matricola){
    richiesta *tmp;

    if(Q == NULL){
        return;
    }else if(codavuota(Q)){
        Q->head = creanodo(titolo, tipo, matricola);
        Q->tail = Q->head;
        printf("\n%s --> richiesta aggiunta(%d)\n", Q->head->titolo, Q->head->matricola);
        return;
    }else{
        tmp = creanodo(titolo, tipo, matricola);

        if(tmp != NULL){
            Q->tail->next = tmp;
            Q->tail = tmp;
            printf("\n%s --> richiesta aggiunta(%d)\n", tmp->titolo, tmp->matricola);
        }
        return;
    }
}


//cambia in leggi coda
void leggicoda(coda *Q){
    richiesta *tmp = Q->head;
    if(codavuota(Q)) printf("\nNessuna richiesta\n");
    while(tmp && tmp->next){
        puts("");
        if(tmp->tipo == true){
            printf("%s da restituire (%d)--> ", tmp->titolo, tmp->matricola);
        }else if(tmp->tipo == false){
            printf("%s richiesto (%d)--> ", tmp->titolo, tmp->matricola);
        }
        tmp = tmp->next;
    }

    if(tmp){
        puts("");
        if(tmp->tipo == true){
            printf("%s da restituire (%d)--|\n ", tmp->titolo, tmp->matricola);
        }else if(tmp->tipo == false){
            printf("%s richiesto (%d)--|\n ", tmp->titolo, tmp->matricola);
        }
    }
}


void leggitesta(coda *Q){
    richiesta *tmp = Q->head;
    if(tmp != NULL){
        if(tmp->tipo == true){
            printf("%s da restituire (%d)--|\n ", tmp->titolo, tmp->matricola);
        }else if(tmp->tipo == false){
            printf("%s richiesto (%d)--|\n ", tmp->titolo, tmp->matricola);
        }
    }else 
    printf("Nessuna richiesta\n");
}

studente *eseguirichiesta(richiesta *rich, libro *libreria, studente *listaStudenti){
    bool tipo = rich->tipo;
    libro *tmp = getlibro(rich->titolo, libreria);
    if(tipo == true){//restituisci
        if((checkinlistastudenti(rich->matricola, listaStudenti) == true) && (possiedelibro(rich->matricola, rich->titolo, listaStudenti)) == true){
            (tmp->disp)++;
            modificalibro(tmp, libreria);
            printf("%s restituito da %d--|\n ", tmp->titolo, rich->matricola);
            listaStudenti = EliminaStudente(rich->matricola, listaStudenti);
            free(tmp);
            return listaStudenti;
        }else{
            printf("Errore : %d non possiede %s\n", rich->matricola, rich->titolo);
            return listaStudenti;
        }
    }else if(tipo == false){//prestito
        if(checkinlistastudenti(rich->matricola, listaStudenti) == true){
            printf("%d possiede un altro libro\n", rich->matricola);
            return listaStudenti;
        }else{
            if(tmp->disp > 0){
                (tmp->disp)--;
                modificalibro(tmp, libreria);
                printf("%s dato in prestito a %d--|\n ", tmp->titolo, rich->matricola);
                free(tmp);
                listaStudenti = InserisciCodaStudente(listaStudenti, rich->matricola, rich->titolo);
                return listaStudenti;
            }else{
                printf("Libro non disponibile\n");
                return listaStudenti;
            }
            }
        }
}

richiesta *copiatesta(coda *Q){
    richiesta *tmp = (richiesta *)malloc(sizeof(richiesta));
    if(tmp != NULL){
        strcpy(tmp->titolo, Q->head->titolo);
        tmp->tipo = Q->head->tipo;
        tmp->matricola = Q->head->matricola;
        return tmp;
    }else{
        free(tmp);//non utilizzato
        return NULL;
    }
}


void dequeue(coda *Q, richiesta *rich){
    richiesta *tmp = (richiesta *)malloc(sizeof(richiesta));
    if(codavuota(Q)){
        return;
    } else if(Q->head == Q->tail){
        strcpy(Q->head->titolo, rich->titolo);
        Q->head->tipo = rich->tipo;
        free(Q->head);
        Q->head = Q->tail = NULL;
        return;
    }else{
        tmp = Q->head;
        strcpy(Q->head->titolo, rich->titolo);
        Q->head->tipo = rich->tipo;
        Q->head = Q->head->next;
        free(tmp);
        return;
    }
}