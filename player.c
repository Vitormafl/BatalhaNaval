#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "api.h"

//função da jogada do player
void input(coord* tabP, coord* tabB, int* pontP, int* pontB, int* ver)
{

    coord* noh = tabB;
    int cont = 1;

    //o loop while só é quebrado quando uma jogada válida é recebida
    while(1)
    {
        //vetor input tem um limite arbitrário de 5 caracteres recebidos
        char input[5]; int coordenadas[2];

        scanf("%s", input);
	
        //loop for avalia cada um dos caracteres inseridos em input
        for (int i = 0; i < 5; i++)
        {
            //caso em que input[i] é uma letra
            if (isalpha(input[i]))
            {
		if ((int)(input[i]) > 96)
			coordenadas[0] = input[i] - 96;
		else
			coordenadas[0] = input[i] - 64;
            }
            //caso em que input[i] é um dígito
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

        //casos inválidos
        if(coordenadas[0] > 12) continue;
        if(coordenadas[1] > 12) continue;
	
        //movimentação até o nó na coordenada horizontal
        for (int c = 1; c < coordenadas[0]; c++)
        {
            noh = noh->e;
        }

        //movimentação até o nó na coordenada vertical
        for (int l = 1; l < coordenadas[1]; l++)
        {
            noh = noh->s;
        }

        //caso em que acertou um navio
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
