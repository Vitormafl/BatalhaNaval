#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> //Linux
//#include <dos.h> //Windows
#include "api.h"

//Remove um submarino do tabuleiro
void removerSub(coord* tab){
    coord *no = tab;
    int par = 0; int cont = 0;
    
    while(no->type != 's' && cont < 12)
    {
        if (par == 0)
        {
            no = no->e;
        }
        else
        {
            no = no->w;
        }
        if (no->e == NULL)
        {
            no = no->s; 
            par = 1; cont += 1;
        }
        if (no->w == NULL)
        {
            no = no->s; 
            par = 0; cont += 1;
        }
    }
    if (no->type == 's')
    {
        no->type = '0';
        no->simb = ' ';
        no->simb_ex = ' ';
        no->hit = 0;
    }

    else return;
}

//Verifica qual navio foi atingido e se foi afundado
void verificarJogada(coord* tabP, coord* tabB, coord* acertoP, coord* acertoB, int* pontP, int* pontB, int* ver){

	int afundado = 1;
	coord* aux;
	
	//Verifica jogada do player
	if(acertoB == NULL){
	
		aux = acertoP;
		
		//Se atingiu uma jangada
		if(aux->type == 'j'){
			aux->simb_ex = aux->simb;
			*pontB += 1;
			*ver = 0;
			return removerSub(tabP);
		}
		
		//Se atingiu um submarino
		else if(aux->type == 's'){
			aux->simb_ex = aux->simb;
			*pontP += 1;
			*ver = 0;
			printarTabuleiro(tabP, tabB, *pontP, *pontB);
			return input(tabP, tabB, pontP, pontB, ver);
		}
		
		//Se acertou um navio horizontal
		else if(aux->ori == 0){
		
			//1. Vai até a extremidade direita do navio
			while(aux->simb != '>')
				aux = aux->e;
			
			//2. volta até a extremidade esquerda do navio, verificando se ele foi totalmente afundado
			while(aux->simb != '<'){
				if(aux->simb_ex != '*')
					afundado = 0;
					
				aux = aux->w;
				if(aux->simb_ex != '*')
					afundado = 0;
					
			}
			//3. Caso afundou um navio do bot, revela ele por completo.
			if(afundado){
				while(aux->simb != '>'){
					aux->simb_ex = aux->simb;
					aux = aux->e;
					if(aux->simb_ex != aux->simb)
						aux->simb_ex = aux->simb;
				}
				*pontP += 1;
			}
			
			printarTabuleiro(tabP, tabB, *pontP, *pontB);
			return input(tabP, tabB, pontP, pontB, ver);
		}
		//Se acertou um navio vertical
		else{
			//1. 
			while(aux->simb != 'v')
				aux = aux->s;
			
			//2. 
			while(aux->simb != '^'){
			
				if(aux->simb_ex != '*')
					afundado = 0;
				
				aux = aux->n;
				if(aux->simb_ex != '*')
					afundado = 0;
			
			}
			
			//3.
			if(afundado){
				while(aux->simb != 'v'){
					aux->simb_ex = aux->simb;
					aux = aux->s;
					if(aux->simb_ex != aux->simb)
						aux->simb_ex = aux->simb;
				}
				*pontP += 1;
			}
			printarTabuleiro(tabP, tabB, *pontP, *pontB);
			return input(tabP, tabB, pontP, pontB, ver);
		}
	}
	
	
	//Verifica jogada do bot			
	else{
		aux = acertoB;
		if(aux->type == 'j'){
			*pontP += 1;
			*ver = 0;
			return removerSub(tabB);
		}
		else if(aux->type == 's'){
			*pontB += 1;
			*ver = 0;
			return jogadaBot(tabP, tabB, ver, &acertoB, pontP, pontB);
		}
		//Se acertou um navio horizontal
		else if(aux->ori == 0){
			//1. Vai até a extremidade direita do navio
			while(aux->simb != '>')
				aux = aux->e;
			
			//2. volta até a extremidade direita do navio, verificando se ele foi totalmente afundado
			while(aux->simb != '<'){
				if(aux->simb_ex != '*')
					afundado = 0;
					
				aux = aux->w;
				if(aux->simb_ex != '*')
					afundado = 0;
			}
			//3. Caso afundou um navio do player, joga de novo aleatoriamente.
			if(afundado){
				*pontB += 1;
				*ver = 0;
			}
			//4. Caso não tenha afundado o navio do player, joga de novo tentando afundar.
			
			return jogadaBot(tabP, tabB, ver, &acertoB, pontP, pontB);
		}
		
		//Se acertou um navio vertical
		else{
			//1. 
			while(aux->simb != 'v')
				aux = aux->s;
			//2. 	
			while(aux->simb != '^'){
			
				if(aux->simb_ex != '*')
					afundado = 0;
					
				aux = aux->n;
				
				if(aux->simb_ex != '*')
					afundado = 0;
				
			}
			//3.
			if(afundado){
			
				*pontB += 1;
				*ver = 0;
			}
			
			//4.
			return jogadaBot(tabP, tabB, ver, &acertoB, pontP, pontB);
		}
	}
}
