#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "nodeStruct.h"

int printCalendar(struct node *head, int nodeId){
    struct node *testNode = head;
    //Skipper le noeud de tete car il est bidon
    testNode = testNode->next;
    printf("\n");

    while(testNode != NULL) {
        printf("____\n");
        printf("| Id de l'evenement : %d\n", testNode->nodeId);
        printf("| Date : %d/%d/%d a %dh \n", testNode->day, testNode->month, testNode->year, testNode->hour);
        printf("| Description : %s\n", testNode->eventDescription);

        //Passer au noeud suivant
        testNode = testNode->next;
    }
    printf("\n");

    return nodeId;
}
