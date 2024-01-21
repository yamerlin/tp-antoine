#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct node{
    int year;
    int month;
    int day;
    int hour;

    char eventDescription[100];

    struct node *next;
};
struct node *head = NULL;

void addEvent(){
    int year;
    int mounth;
    int day;
    int hour;

    printf("Entrez l'année de l'événement : ");
    scanf("%d", &year);

    struct node *newNode = NULL;
    newNode = malloc(sizeof(struct node));

    //Noeuds bidons pour évaluer la position du nouveau noeud
    struct node *testNode = head;
    struct node *nextNode = head;
    struct node *previousNode = head;
    //Boolean pour confirmer que la position du nouveau noeud a été trouvée
    bool isPosFound = false;

    //Evaluation
    previousNode = testNode;
    while(testNode != NULL && !isPosFound) {
      printf(" %d ",testNode->year);

      if (testNode->year > year){
        //Retenir le noeud qui sera après
        nextNode = testNode;

        //Avancer d'un noeud
        //testNode = testNode->next;

        //Confirmer que la position a été trouvée
        isPosFound = true;
      }
      else{
        //Retenir le noeud qui sera avant
        previousNode = testNode;
        //Avancer d'un noeud
        testNode = testNode->next;
      }
    }

    //Seter les valeurs du noeud d'avant le nouveau noeud
    previousNode->next = newNode;

    //Seter les valeurs du nouveau noeud
    newNode->year = year;
    if(testNode == NULL){               //Vérifier s'il s'agit du noeud de fin
        newNode->next = NULL;
        printf("Noeud ajouté en temps que noeud de fin \n");
    }
    else{
        newNode->next = nextNode;
        printf("Noeud ajouté \n");
    }
}

void deleteEvent(){

}

void saveCalendar(){

}

void loadCalendar(){

}

void printCalendar(){
    struct node *p = head;
    printf("\n[");

    while(p != NULL) {
      printf(" %d ",p->year);
      p = p->next;
    }

    printf("]");
}

int main() {
    //Init le noeud de tete
    head = malloc(sizeof(struct node));
    head->next = NULL;
    head->year = 0;
    head->month = 0;
    head->day = 0;
    head->hour = 0;

    // struct node *n1 = NULL;
    // struct node *n2 = NULL;
    // struct node *n3 = NULL;
    // struct node *n4 = NULL;

    // n1 = malloc(sizeof(struct node));
    // n2 = malloc(sizeof(struct node));
    // n3 = malloc(sizeof(struct node));
    // n4 = malloc(sizeof(struct node));
    

    // n1->year = 1;
    // n2->year = 2;
    // n3->year = 4;
    // n4->year = 5;

    
    // n1->next = n2;
    // n2->next = n3;
    // n3->next = n4;
    // n4->next = NULL;

    int value;

    while(value != 6){
        printf("_______________________________\n");
        printf("|             Menu            |\n");
        printf("| 1 - Ajouter un événement    |\n");
        printf("| 2 - Supprimer un événement  |\n");
        printf("| 3 - Sauvegarder l'agenda    |\n");
        printf("| 4 - Charger un agenda       |\n");
        printf("| 5 - Afficher l'agenda       |\n");
        printf("| 6 - Quitter                 |\n");
        printf("|_____________________________|\n");

        printf("Entrez le numéro de votre choix : ");
        scanf("%d", &value);

        switch( value ) {
            case 1:
                addEvent();
                break;
            case 2:
                deleteEvent();
                break;
            case 3:
                saveCalendar();
                break;
            case 4:
                loadCalendar();
                break;
            case 5:
                printCalendar();
                break;
            case 6:
                printf( "Quitter\n" );
                exit(0);
                break;
            default:
                printf( "Entrer un nombre compris dans le menu svp\n" );
        }

        printf("\n");
    }

    return 0;
}
