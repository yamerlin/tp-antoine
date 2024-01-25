#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "nodeStruct.h"

int saveCalendar(struct node *head, int nodeId){
    char calendarName[100];

    printf("\nVos calendriers sont enregistres dans le dossier courant ou le programme est execute\n");
    printf("Entrez le nom de votre calendrier : ");
    //Flusher les possible caracteres end of line restant dans le buffer d'input pour éviter le fgets() de se faire skipper si il choppe un eof ou eof
    char c; //Variable bidon
    while ((c = getchar()) != '\n' && c != EOF);
    //Récuperer l'input utilisateur
    fgets(calendarName, 100, stdin);

    //Récupérer la longeur du nom de l'agenda pour le formater (en .txt)
    int strLength = strlen(calendarName);
    //On remplace le caractère eol par un point
    calendarName[strLength -1] = '.'; 

    //Ajouter "txt" au nom du fichier
    strncat(calendarName, "txt", 4);

    //strncat(calendarName, "\0",3);

    //Ouvrir le calendrier
    FILE *filePointer;
    filePointer = fopen(calendarName,"w");

    struct node *testNode = head;
    //Skipper le noeud de tete car il est bidon
    testNode = testNode->next;

    //Ecrire les données dans le calendrier
    while(testNode != NULL) {
        fprintf(filePointer, "%d %d/%d/%d %d %s\n", testNode->nodeId, testNode->day, testNode->month, testNode->year, testNode->hour, testNode->eventDescription);

        //Passer au noeud suivant
        testNode = testNode->next;
    }

    printf("%s a ete sauvegarde !", calendarName);

    //Fermer le calendrier
    fclose(filePointer);

    return nodeId;
}
