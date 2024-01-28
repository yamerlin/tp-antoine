#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool testInput(char strInput[100]){
    bool isInputAnInt = false;
    int intInput = 0;

    //Variable qui te dis le dernier premier char qui est pas un int avec strtol()
    //Donc en gros si elle est nulle c'est que l'input a pas de char donc est un int (ou est vide)
    char *end;

    //printf("%s\n", strInput);

    intInput = strtol(strInput, &end, 10);

    //printf("End : %c\n", *end);
    //printf("intInput : %d\n", intInput);

    if(end == strInput && intInput == 0){
        //printf("C'est une string\n");
        isInputAnInt = false;
    }
    else if(intInput != 0 && strcmp(end, "") != 0){
        //printf("C'est un mix de string et int\n");
        isInputAnInt = false;
    }
    else{
        //printf("C'est un int\n");
        isInputAnInt = true;
    }

    return isInputAnInt;
}
