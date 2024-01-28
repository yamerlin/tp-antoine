#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "nodeStruct.h"
#include "addEvent.h"
#include "testInput.h"
#include "convertInputToString.h"

int createEvent(struct node *head, int nodeId){
    char strYear[100] = " ";
    char strMonth[100] = " ";
    char strDay[100] = " ";
    char strHour[100] = " ";

    int year;
    int month;
    int day;
    int hour;
    char eventDescription[100];

    //Demander les inputs utilisateur
    printf("\n");
    printf("/!\\ Les dates doivent etres entrees en chiffres svp /!\\\n");

    //Tester si le jour est bien un int
    while(!testInput(strDay)){
        printf("Entrez le jour de l'evenement : ");
        scanf("%s", strDay);

        if(!testInput(strDay)){
            printf("Veuillez entrer un numero valide svp\n");
        }
        else{
            day = convertInputToString(strDay);
        }
    }
    strcpy(strDay, "");

    //Tester si le mois est bien un int
    while(!testInput(strMonth)){
        printf("Entrez le mois de l'evenement : ");
        scanf("%s", strMonth);

        if(!testInput(strMonth)){
            printf("Veuillez entrer un numero valide svp\n");
        }
        else{
            month = convertInputToString(strMonth);
        }
    }
    strcpy(strMonth, "");

    //Tester si l'annee est bien un int
    while(!testInput(strYear)){
        printf("Entrez l'annee de l'evenement : ");
        scanf("%s", strYear);

        if(!testInput(strYear)){
            printf("Veuillez entrer un numero valide svp\n");
        }
        else{
            year = convertInputToString(strYear);
        }
    }
    strcpy(strYear, "");

    //Tester si l'heure est bien un int
    while(!testInput(strHour)){
        printf("Entrez l'heure de l'evenement : ");
        scanf("%s", strHour);

        if(!testInput(strHour)){
            printf("Veuillez entrer un numero valide svp\n");
        }
        else{
            hour = convertInputToString(strHour);
        }
    }
    strcpy(strHour, "");

    printf("Entrez la description de l'evenement (100 caracteres maximum - evitez les accents) : ");
    //Flusher les possible caracteres end of line restant dans le buffer d'input pour éviter le fgets() de se faire skipper si il choppe un eol ou eof
    char c; //Variable bidon
    while ((c = getchar()) != '\n' && c != EOF);
    //Ici on utilise fgets() à la place de scanf() pour pouvoir prendre des éventuelles caractères espace
    fgets(eventDescription, 100, stdin);
    //Enlever le eol de eventDescription
    int len = strlen(eventDescription);
    eventDescription[len-1]='\0';

    printf("| Resume de votre evenement : \n");
    printf("| Date : %d/%d/%d a %dh \n", day, month, year, hour);
    printf("| Description : %s \n", eventDescription);
    printf("\n");

    //Ajouter le noeud
    nodeId = addEvent(day, month, year, hour, eventDescription, head, nodeId);

    return nodeId;
}
