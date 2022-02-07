#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "api.h"

//função da jogada do player
void input(coord* tabP, coord* tabB, int* pontP, int* pontB, int* ver)
{

	//vetor input tem um limite arbitrário de 5 caracteres recebidos
	char input[5]; int coordenadas[2];


	//o loop while só é quebrado quando uma jogada válida é recebida
	while(1){
    
		int cont = 1;
		coord* noh = tabB;

		printf("Insira a coordenada: \n");
		scanf(" %s", input);
	
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

				if(cont == 1)
					coordenadas[1] = input[i] - 48;
                
				else{

					coordenadas[1] *= 10;
					coordenadas[1] += (input[i] - 48);
				}
				cont++;
			}
		}
		
		//caso o valor das colunas seja inválido
		if(coordenadas[0] < 1 || coordenadas[0] > 12){
			printf("Jogada inválida!\n");
			continue;
		}
		//caso o valor das linhas seja inválido
		if(coordenadas[1] < 1 || coordenadas[1] > 12){
			printf("Jogada inválida!\n");
			continue;
		}
		
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

		if (noh->type != '0' && noh->hit == 0)
		{

			noh->simb_ex = '*';
			noh->hit = 1;
			verificarJogada(tabP, tabB, noh, NULL, pontP, pontB, ver);
		}
	
		else if (noh->hit == 0){
			noh->simb_ex = 'O';
			noh->hit = 1;
		}
		//caso a coordenada seja inválida.
		else{
			printf("Jogada inválida!\n");
			continue;
		}
		break;
	}
}
