#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "nodeStruct.h"

int addEvent(int day, int month, int year, int hour, char eventDescription[100], struct node *head, int nodeId){

    //Créer le nouveau noeud et lui allouer la mémoire
    struct node *newNode = NULL;
    newNode = malloc(sizeof(struct node));

    //Noeuds bidons pour évaluer la position du nouveau noeud
    struct node *testNode = head;
    struct node *nextNode = head;
    struct node *previousNode = head;
    //Boolean pour confirmer que la position du nouveau noeud a été trouvée
    bool isPosFound = false;

    //Evaluation de la position du nouveau noeud
    previousNode = testNode;
    do {
        if (testNode->year == year){
            //Si l'année est ègale on compare le mois

            if(testNode->month == month){
                //Si le mois est égale on compare le jour

                if(testNode->day == day){
                    //Si le jour est égale on compare l'heure

                    if(testNode->hour >= hour){
                        //Si l'heure est égale alors les deux événements sont égaux alors on le met avant par défaut

                        //Retenir le noeud qui sera après
                        nextNode = testNode;

                        //Confirmer que la position a été trouvée
                        isPosFound = true;
                        printf("\nPlace trouvee\n");
                    }
                    else{
                        //Retenir le noeud qui sera avant
                        previousNode = testNode;

                        //Avancer d'un noeud
                        testNode = testNode->next;
                    }
                }

                else if(testNode->day > day){
                    //Si l'heure est plus grande on a trouvé la place

                    //Retenir le noeud qui sera après
                    nextNode = testNode;

                    //Confirmer que la position a été trouvée
                    isPosFound = true;
                    printf("\nPlace trouvee\n");
                }
                else{
                    //Retenir le noeud qui sera avant
                    previousNode = testNode;

                    //Avancer d'un noeud
                    testNode = testNode->next;
                }
            }
            else if(testNode->month > month){
                //Si le mois est plus grand on a trouvé la place

                //Retenir le noeud qui sera après
                nextNode = testNode;

                //Confirmer que la position a été trouvée
                isPosFound = true;
                printf("\nPlace trouvee\n");
            }
            else{
                //Retenir le noeud qui sera avant
                previousNode = testNode;

                //Avancer d'un noeud
                testNode = testNode->next;
            }
        }
        else if(testNode->year > year){
            //SI L'année est plus grande on a trouvé la place

            //Retenir le noeud qui sera après
            nextNode = testNode;

            //Confirmer que la position a été trouvée
            isPosFound = true;
            printf("\nPlace trouvee\n");
        }
        else{
            //Retenir le noeud qui sera avant
            previousNode = testNode;

            //Avancer d'un noeud
            testNode = testNode->next;
        }
    }while(testNode != NULL && !isPosFound);

    //Setter les valeurs du noeud d'avant le nouveau noeud
    previousNode->next = newNode;

    //Setter les valeurs du nouveau noeud
    newNode->nodeId = nodeId;
    nodeId = nodeId + 1;
    newNode->day = day;
    newNode->month = month;
    newNode->year = year;
    newNode->hour = hour;
    //Ici on utilise strcpy() pour assigner la description à son noeud car en C les strings sont justes des arrays de char donc on peut pas les assigner comme des int
    strcpy(newNode->eventDescription, eventDescription);
    if(testNode == NULL){               //Vérifier s'il s'agit du noeud de fin ou pas
        newNode->next = NULL;           //Si c'est le noeud de fin alors son noeud suivant est null
        printf("Noeud ajoute en temps que noeud de fin \n");
    }
    else{
        newNode->next = nextNode;
        printf("Noeud ajoute \n");
    }

    return nodeId;
}
