#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "api.h"

int input(coord* tabP, coord* tabB, int* pontP, int* pontB, int* ver)
{

    coord* noh = tabB;
    int cont = 1;

    while(1)
    {
        char input[5]; int coordenadas[2];

        scanf("%s", input);
	
        for (int i = 0; i < 5; i++)
        {
            if (isalpha(input[i]))
            {
		if ((int)(input[i]) > 96)
			coordenadas[0] = input[i] - 96;
		else
			coordenadas[0] = input[i] - 64;
            }
            if (isdigit(input[i])){
            	if(cont == 1){
                	coordenadas[1] = input[i] - 48;
                }
                else{
                	coordenadas[1] *= 10;
                	coordenadas[1] += (input[i] - 48);
                }
                cont++;
            }
        }
        if(coordenadas[0] > 12) continue;
        if(coordenadas[1] > 12) continue;
        
	printf("%d, %d\n", coordenadas[0], coordenadas[1]);
	
        for (int c = 1; c < coordenadas[0]; c++)
        {
            noh = noh->e;
        }

        for (int l = 1; l < coordenadas[1]; l++)
        {
            noh = noh->s;
        }
	
        if (noh->type != '0')
        {

            noh->simb_ex = '*';
            verificarJogada(tabP, tabB, noh, NULL, pontP, pontB, ver);
        }

        else
       	 noh->simb_ex = 'O';

        break;
    }
}
