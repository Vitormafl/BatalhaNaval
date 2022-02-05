#include <stdio.h>
#include <stdlib.h>
#include "api.h"

int input(coord* tabP, coord* tabB, int* pontP, int* pontB)
{
    while (true)
    {
        char input[5]; char coordenadas[2];

        scanf("%s", &input);

        for (int i = 0; i < 5; i++)
        {
            if (isalpha(input[i]))
            {
                if (int(input[i]) >= 77) continue; 
                coordenadas[0] = input[i];
            }

            if (isdigit(input[i])) 
            {
                if (input[i] < 1 or input[i] > 12) continue; 
                coordenadas[1] = input[i];
            }
        }

        for (int i = 0; i < int(coordenadas[0]); i++)
        {
            noh = noh->e;
        }

        for (int i = 0; i < coordenadas[1]; i++)
        {
            noh = noh->s;
        }

        if (noh->type != '0')
        {
            noh->simb = '*';
            verificarJogada(tabP, tabB, noh, NULL, pontP, pontB);
        }

        else noh->simb = 'O';

        break;
    }
}
