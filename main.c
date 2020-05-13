#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "richiesta.h"
#include "libro.h"
#include "studente.h"

int creazionemenu(libro *libreria, coda *Q, studente *listaStudenti);


int main()
{
    libro *libreria = NULL;
    studente *listaStudenti = NULL;
    coda Q;
    creacoda(&Q);
    FILE *fp;

    //viene aperto il file con l'elenco dei libri e inserito nella lista, poi chiuso il file
    fp = fopen("data.txt", "r");
    if(!fp) {perror("Errore"); exit(0);}
    libreria = LeggiFile(libreria, fp);
    fclose(fp);

    creazionemenu(libreria, &Q, listaStudenti);
    return 0;
}



int creazionemenu(libro *libreria, coda *Q, studente *listaStudenti){
    int scelta = 0;
    richiesta *rich;
    int matricola;
    //bool tipo;
    char titolo[max];
    do{
        printf("\n1.Mostra elenco libri\n2.Richiedi libro\n3.Restituisci libro\n4.Mostra lista richieste\n5.Esegui richiesta\n6.Mostra elenco prestiti\n\n0.Esci\n");
        scanf("%d", &scelta);
        switch(scelta){
            case 1: //mostra elenco
                system("cls");
                puts("");
                StampaLibri(libreria);
                break;
            case 2: // richiedi libro
                system("cls");
                printf("\nInserire matricola:\n");
                scanf("%d", &matricola);
                puts("");
                puts("Elenco libri:");
                StampaLibri(libreria);
                printf("\nInserire il titolo del libro richiesto:\n");
                scanf("%s", &titolo);
                if(checkinlista(titolo, libreria) == true){
                    enqueue(Q, titolo, false, matricola);
                }else{
                    printf("\nLibro non trovato\n");
                }
                break;
            case 3: //restituisci libro
                system("cls");
                printf("\nInserire matricola:\n");
                scanf("%d", &matricola);
                puts("");
                puts("Elenco libri:");
                StampaLibri(libreria);
                printf("\nInserire il titolo del libro da restituire:\n");
                scanf("%s", &titolo);
                if(checkinlista(titolo, libreria) == true){
                    enqueue(Q, titolo, true, matricola);
                }else{
                    printf("\nLibro non trovato\n");
                }
                break;
            case 4: //elenco richieste
                system("cls");
                leggicoda(Q);
                break;
            case 5: //esegui richiesta
                system("cls");
                if(codavuota(Q)){
                    printf("\nNessuna richiesta\n"); 
                    break;
                }else{
                    rich = copiatesta(Q);
                    listaStudenti = eseguirichiesta(rich, libreria, listaStudenti);
                    dequeue(Q, rich);
                    break;
                 }
            case 6:
                system("cls");
                if(LunghezzaListaStudenti(listaStudenti) == 0){
                    puts("Nessun prestito"); 
                    break;
                }else {
                    stampaListaStudenti(listaStudenti);
                }       
            case 0:
                break;
            default:
                printf("\nScelta invalida\n");
                break;
        }
    }while(scelta != 0);
    return 0;
}