#include <stdio.h>
#include <stdlib.h>
#include "api.h"

int input(coord** tabPlayer){
    char input[5]; char coordenadas[2];

    scanf("%s", &input);

    for (int i = 0; i < 5; i++)
    {
        if (isalpha(input[i]))
        {
            if (int(input[i]) >= 77) return 0; 
            coordenadas[0] = input[i];
        }
        
        if (isdigit(input[i])) 
        {
            if (input[i] < 1 or input[i] > 12) return 0; 
            coordenadas[1] = input[i];
        }
    }

    return 1;
}
