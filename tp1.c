#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

//Le nodeId est un identifiant unique à chaque noeud
//Il sera utilisé principalement pour choisir un noeud quand on veut le supprimer car c'est la seule manière de diffèrencier deux noeud ayant exactement la même date et la même heure
int nodeId = 0;

//Définition de la structure d'un noeud
struct node{
    int year;
    int month;
    int day;
    int hour;
    int nodeId;

    char eventDescription[100];

    struct node *next;
};
//Création du noeud de tête
struct node *head = NULL;

void printCalendar(){
    struct node *testNode = head;
    //Skipper le noeud de tete car il est bidon
    testNode = testNode->next;
    printf("\n");

    while(testNode != NULL) {
        printf("____\n");
        printf("| Id de l'événement : %d\n", testNode->nodeId);
        printf("| Date : %d/%d/%d à %dh \n", testNode->day, testNode->month, testNode->year, testNode->hour);
        printf("| Description : %s\n", testNode->eventDescription);

        //Passer au noeud suivant
        testNode = testNode->next;
    }
    printf("\n");
}

void addEvent(int day, int month, int year, int hour, char eventDescription[100]){

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
                        printf("\nPlace trouvée\n");
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
                    printf("\nPlace trouvée\n");
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
                printf("\nPlace trouvée\n");
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
            printf("\nPlace trouvée\n");
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
        printf("Noeud ajouté en temps que noeud de fin \n");
    }
    else{
        newNode->next = nextNode;
        printf("Noeud ajouté \n");
    }
}

void createEvent(){
    int year;
    int month;
    int day;
    int hour;
    char eventDescription[100];

    //Demander les inputs utilisateur
    printf("\n");
    printf("/!\\ Les dates doivent êtres entrées en chiffres svp /!\\\n");
    printf("Entrez le jour de l'événement : ");
    scanf("%d", &day);

    printf("Entrez le mois de l'événement : ");
    scanf("%d", &month);

    printf("Entrez l'année de l'événement : ");
    scanf("%d", &year);

    printf("Entrez l'heure de l'événement : ");
    scanf("%d", &hour);

    printf("Entrez la description de l'événement (100 caractères maximum - évitez les accents) : ");
    //Flusher les possible caracteres end of line restant dans le buffer d'input pour éviter le fgets() de se faire skipper si il choppe un eol ou eof
    char c; //Variable bidon
    while ((c = getchar()) != '\n' && c != EOF);
    //Ici on utilise fgets() à la place de scanf() pour pouvoir prendre des éventuelles caractères espace
    fgets(eventDescription, 100, stdin);
    //Enlever le eol de eventDescription
    int len = strlen(eventDescription);
    eventDescription[len-1]='\0';

    printf("| Résumé de votre événement : \n");
    printf("| Date : %d/%d/%d à %dh \n", day, month, year, hour);
    printf("| Description : %s \n", eventDescription);
    printf("\n");

    //Ajouter le noeud
    addEvent(day, month, year, hour, eventDescription);
}

void deleteEvent(){
    int idOfEventToDelete;
    bool isEventFound = false;
    struct node *previousNode = head;
    printf("\nVoici les événements disponibles : \n");
    printCalendar();
    printf("\nEntrez l'Id de l'événement que vous souhaitez supprimer :");
    scanf("%d", &idOfEventToDelete);
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
        printf("Le noeud n'a pas été trouvé, vérifiez si l'id est correct");
    }
    else{
        printf("Noeud trouvé et supprimé !");
    }
}

void saveCalendar(){
    char calendarName[100];

    printf("\nVos calendriers sont enregistrés dans le dossier courant où le programme est executé\n");
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

    printf("%s a été sauvegardé !", calendarName);

    //Fermer le calendrier
    fclose(filePointer);
}

void loadCalendar(){
    char ch;

    int year;
    int month;
    int day;
    int hour;
    int nodeId;

    char yearStr[4] = "";
    char monthStr[2] = "";
    char dayStr[2] = "";
    char hourStr[2] = "";
    char nodeIdStr[20] = "";

    char eventDescription[100];
    char calendarName[100];

    printf("\nVos calendriers doivent être dans le dossier courant où le programme est executé\n");
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
                printf(" Année :");
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
                addEvent(day, month, year, hour, eventDescription);

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
}

int main() {

    //Init le noeud de tete
    head = malloc(sizeof(struct node));
    head->next = NULL;

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
                createEvent();
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
