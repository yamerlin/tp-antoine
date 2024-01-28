#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "nodeStruct.h"

#include "createEvent.h"
#include "deleteEvent.h"
#include "saveCalendar.h"
#include "loadCalendar.h"
#include "printCalendar.h"
#include "testInput.h"
#include "convertInputToString.h"


//Le nodeId est un identifiant unique à chaque noeud
//Il sera utilisé principalement pour choisir un noeud quand on veut le supprimer car c'est la seule manière de diffèrencier deux noeud ayant exactement la même date et la même heure
int nodeId = 0;


int main() {

    //Création du noeud de tête
    struct node *head = NULL;


    //Init le noeud de tete
    //free(head);
    head = malloc(sizeof(struct node));
    head->next = NULL;
    

    char strValue[100] = " ";
    int value = 0;

    while(value != 6){
        printf("_______________________________\n");
        printf("|             Menu            |\n");
        printf("| 1 - Ajouter un evenement    |\n");
        printf("| 2 - Supprimer un evenement  |\n");
        printf("| 3 - Sauvegarder l'agenda    |\n");
        printf("| 4 - Charger un agenda       |\n");
        printf("| 5 - Afficher l'agenda       |\n");
        printf("| 6 - Quitter                 |\n");
        printf("|_____________________________|\n");

        //Tester si l'input est bien un int
        while(!testInput(strValue)){
            printf("Entrez le numero de votre choix : ");
            scanf("%s", strValue);

            if(!testInput(strValue)){
                printf("Veuillez entrer un numero valide svp\n");
            }
            else{
                value = convertInputToString(strValue);
            }
        }

        switch( value ) {
            case 1:
                nodeId = createEvent(head, nodeId);
                break;
            case 2:
                nodeId = deleteEvent(head, nodeId);
                break;
            case 3:
                nodeId = saveCalendar(head, nodeId);
                break;
            case 4:
                nodeId = loadCalendar(head, nodeId);
                break;
            case 5:
                nodeId = printCalendar(head, nodeId);
                break;
            case 6:
                printf( "Quitter\n" );
                exit(0);
                break;
            default:
                printf( "Entrer un nombre compris dans le menu svp\n" );
        }

        //Vider strValue
        strcpy(strValue, "");

        printf("\n");
    }

    return 0;
}
