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
