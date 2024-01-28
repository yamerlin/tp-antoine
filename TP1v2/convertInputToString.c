#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int convertInputToString(char strInput[100]){
    int intInput = 0;

    //Convertir la variable string en int
    intInput = strtol(strInput, NULL, 10);
    //printf("%d", intInput);

    return intInput;
}