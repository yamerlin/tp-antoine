#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "nodeStruct.h"
#include "printCalendar.h"
#include "testInput.h"
#include "convertInputToString.h"

int deleteEvent(struct node *head, int nodeId){
    int idOfEventToDelete;
    char strIdOfEventToDelete[100];

    bool isEventFound = false;
    struct node *previousNode = head;
    printf("\nVoici les evenements disponibles : \n");
    printCalendar(head, nodeId);

    //Tester si l'input est bien un int
    while(!testInput(strIdOfEventToDelete)){
        printf("\nEntrez l'Id de l'evenement que vous souhaitez supprimer :");
        scanf("%s", strIdOfEventToDelete);

        if(!testInput(strIdOfEventToDelete)){
            printf("Veuillez entrer un numero valide svp\n");
        }
        else{
            idOfEventToDelete = convertInputToString(strIdOfEventToDelete);
        }
    }
    strcpy(strIdOfEventToDelete, "");

    printf("\n");

    //Parcourir la liste chainée pour trouvé l'événement avec l'id correspondant
    struct node *testNode = head;
    previousNode = testNode;
    //Skipper le noeud de tete car il est bidon
    while(testNode != NULL && !isEventFound) {
        if(testNode->nodeId == idOfEventToDelete){
            //Pour supprimer un noeud, il suffit de relier le neoud d'avant avec le noeud suivant
            previousNode->next = testNode->next;

            isEventFound = true;
        }

        previousNode = testNode;
        //Passer au noeud suivant
        testNode = testNode->next;
    }

    if(!isEventFound){
        printf("Le noeud n'a pas ete trouve, verifiez si l'id est correct");
    }
    else{
        printf("Noeud trouve et supprime !");
    }

    return nodeId;
}
