#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "nodeStruct.h"
#include "addEvent.h"

int loadCalendar(struct node *head, int nodeId){
    char ch;

    int year;
    int month;
    int day;
    int hour;

    char yearStr[4] = "";
    char monthStr[2] = "";
    char dayStr[2] = "";
    char hourStr[2] = "";
    char nodeIdStr[20] = "";

    char eventDescription[100];
    char calendarName[100];

    printf("\nVos calendriers doivent etre dans le dossier courant ou le programme est execute\n");
    printf("Charger un calendrier le fusionnera avec le calendrier actuel\n");
    printf("Entrez le nom de votre calendrier (/!\\ ne pas oublier le .txt /!\\) : ");
    //Flusher les possible caracteres end of line restant dans le buffer d'input pour éviter le fgets() de se faire skipper si il choppe un eof ou eof
    char c; //Variable bidon
    while ((c = getchar()) != '\n' && c != EOF);
    //Récuperer l'input utilisateur
    fgets(calendarName, 100, stdin);

    //Enlever le eol de calendarName
    int len = strlen(calendarName);
    calendarName[len-1]='\0';

    //Ouvrir le calendrier
    FILE *filePointer;
    filePointer = fopen(calendarName,"r");

    //Vérifier que le calendrier existe
    if (filePointer == NULL) {
        printf("Le calendrier n'existe pas ou est corompu \n");
    }
    else{
        //ch représente le caractère en cours de lecture dans le fichier
        ch = fgetc(filePointer);

        if(ch == '\n' || ch == EOF){
            printf("Fin du fichier");
        }
        else{
        
            do {

                //---------------------------- Récupérer l'ID ----------------------------
                printf("Id :");
                while (ch != ' ') {
                    //Ajouter le caractère à la fin de la variable string
                    strncat(nodeIdStr, &ch, 1);

                    //Récupérer le caractère suivant
                    ch = fgetc(filePointer);
                }
                //Convertir la variable string en int
                nodeId = strtol(nodeIdStr, NULL, 10);
                printf("%d", nodeId);
                //Vider nodeIdStr
                strcpy(nodeIdStr, "");
                printf("\n");

                //---------------------------- Récupérer le jour ----------------------------
                printf(" Jour :");
                while (ch != '/'){
                    //Récupérer le caractère suivant
                    ch = fgetc(filePointer);

                    //Ajouter le caractère à la fin de la variable string
                    strncat(dayStr, &ch, 1);
                }
                //Convertir la variable string en int
                day = strtol(dayStr, NULL, 10);
                printf("%d", day);
                //Vider dayStr
                strcpy(dayStr, "");
                printf("\n");

                //Récupérer le caractère suivant
                ch = fgetc(filePointer);

                //---------------------------- Récupérer le mois ----------------------------
                strcpy(monthStr, "");
                printf(" Mois :");
                while (ch != '/'){
                    //Ajouter le caractère à la fin de la variable string
                    strncat(monthStr, &ch, 1);

                    //Récupérer le caractère suivant
                    ch = fgetc(filePointer);
                }
                //Convertir la variable string en int
                month = strtol(monthStr, NULL, 10);
                printf("%d", month);
                //Vider monthStr
                strcpy(monthStr, "");
                printf("\n");

                //Récupérer le caractère suivant
                ch = fgetc(filePointer);

                //---------------------------- Récupérer l'année ----------------------------
                printf(" Annee :");
                while (ch != ' '){
                    //Ajouter le caractère à la fin de la variable string
                    strncat(yearStr, &ch, 1);

                    //Récupérer le caractère suivant
                    ch = fgetc(filePointer);
                }
                //Convertir la variable string en int
                year = strtol(yearStr, NULL, 10);
                printf("%d", year);
                //Vider yearStr
                strcpy(yearStr, "");
                printf("\n");

                //Récupérer le caractère suivant
                ch = fgetc(filePointer);

                //---------------------------- Récupérer l'heure ----------------------------
                printf(" Heure :");
                while (ch != ' '){
                    //Ajouter le caractère à la fin de la variable string
                    strncat(hourStr, &ch, 1);

                    //Récupérer le caractère suivant
                    ch = fgetc(filePointer);
                }
                //Convertir la variable string en int
                hour = strtol(hourStr, NULL, 10);
                printf("%d", hour);
                //Vider hourStr
                strcpy(hourStr, "");
                printf("\n");

                //---------------------------- Récupérer la description ----------------------------
                printf(" Description :");
                while (ch != '\n'){
                    //Ajouter le caractère à la fin de la variable string
                    strncat(eventDescription, &ch, 1);

                    //Récupérer le caractère suivant
                    ch = fgetc(filePointer);
                }
                printf("%s", eventDescription);
                printf("\n");

                ch = fgetc(filePointer);

                //--------------------------------- Ajouter le noeud ---------------------------------
                addEvent(day, month, year, hour, eventDescription, head, nodeId);

                //Vider eventDescription
                strcpy(eventDescription, "");

            }while (ch != EOF);

        }
    }

    fclose(filePointer);

    //Ajuster le nodeId en fonction du plus élevé du calendrier chargé
    //Pour éviter que deux noeud aient le même nodeId quand on en ajoutera par la suite
    struct node *testNode = head;
    //Skipper le noeud de tete car il est bidon
    testNode = testNode->next;
    //Défiler tout les noeuds
    while(testNode != NULL) {
        if(testNode->nodeId > nodeId){
            nodeId = testNode->nodeId + 1;
        }

        //Passer au noeud suivant
        testNode = testNode->next;
    }
    printf("\n");

    return nodeId;
}
