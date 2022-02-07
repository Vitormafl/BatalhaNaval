#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> //Linux
//#include <dos.h> //Windows
#include "api.h"

/*	Algoritmo que decide a jogada do bot:

	tabPlayer = ponteiro para o tabuleiro do player.
	tabBot = ponteiro para o tabuleiro do bot.
	ver = ponteiro para o booleano que define se o bot atingiu uma embarcação numa jogada 
	anterior e não a afundou.
	ant = Ponteiro para ponteiro para a última posição que contém um navio que o bot atingiu.
	pontP = ponteiro para o valor da pontuação do player.
	pontB = ponteiro para o valor da pontuação do bot.					
												*/
void jogadaBot(coord* tabPlayer, coord* tabBot, int* ver, coord** ant, int* pontP, int* pontB){
	
	printf("\nVez da máquina:\n");
	coord *aux;
	
	int l, c, escolhendo = 1, escolha;
	
/*	Caso não tenha acertado uma embarcação ou caso a última embarcação atingida já tenha 
	sido afundada, escolhe aleatoriamente uma posição para atacar.			*/ 
	if (*ver == 0){
		while(escolhendo){
		
			srand(time(NULL));
			l = rand()%12;
			c = rand()%12;
			
			aux = tabPlayer;
			escolhendo = 0;
			
			for(int i = 0; i < l; i++){
				aux = aux->s;
			}
			for(int j = 0; j < c; j++){
				aux = aux->e;
			}
			if(aux->simb_ex == '*' || aux->simb_ex == 'O'){
				sleep(1);
				escolhendo = 1;
			}
			else if(aux->simb_ex == ' '){
				aux->simb_ex = 'O';
				aux->hit = 1;
				printarTabuleiro(tabPlayer, tabBot, *pontP, *pontB);
				return;
			}
			else{	

				aux->simb_ex = '*';
				aux->hit = 1;
				*ver = 1;
				*ant = aux;
				printarTabuleiro(tabPlayer, tabBot, *pontP, *pontB);
				return verificarJogada(tabPlayer, tabBot, NULL, *ant, pontP, pontB, ver);
			}
		}
	}

//	Caso tenha atingido uma embarcação sem afundá-la:
	else{
		aux = *ant;
	
		
/* 1.		 Último tiro
		 |
		 V
		** 
		  ^
		  |
		  Caso não nulo e não atingido, atira aqui	*/
		if((aux->e != NULL && aux->e->simb_ex == '*') && (aux->w != NULL && aux->w->hit == 0)){

			if(aux->w->simb_ex == ' '){
				aux->w->simb_ex = 'O';
				return;
			}
			else if(aux->w->simb_ex == 'O'){
				aux = *ant;
			}
			else{
				aux->w->simb_ex = '*';
				aux->w->hit = 1;
				*ver = 1;
				*ant = aux->w;
				printarTabuleiro(tabPlayer, tabBot, *pontP, *pontB);
				return verificarJogada(tabPlayer, tabBot, NULL, *ant, pontP, pontB, ver);
			}
		}
		
/* 2.		 Último tiro
		 |
		 V
		 ** 
		^
		|  
		Caso não nulo e não atingido, atira aqui	*/
		else if((aux->w != NULL && aux->w->simb_ex == '*') && (aux->e != NULL && aux->e->hit == 0)){

			if(aux->e->simb_ex == ' '){
				aux->e->simb_ex = 'O';
				return;
			}
			else if(aux->e->simb_ex == 'O'){
				aux = *ant;
			}
			else{
				aux->e->simb_ex = '*';
				aux->e->hit = 1;
				*ver = 1;
				*ant = aux->e;
				printarTabuleiro(tabPlayer, tabBot, *pontP, *pontB);
				return verificarJogada(tabPlayer, tabBot, NULL, *ant, pontP, pontB, ver);
			}
		}
		
			
/* 3.		 
		  <-- Caso não nulo e não atingido, atira aqui
		 *<-- Último tiro
		 *
									*/
		else if((aux->s != NULL && aux->s->simb_ex == '*') && (aux->n != NULL && aux->n->hit == 0)){
			if(aux->n->type == '0'){
				aux->n->simb_ex = 'O';
				return;
			}
			else if(aux->n->simb_ex == 'O'){
				aux = *ant;
			}
			else{
				aux->n->simb_ex = '*';
				aux->n->hit = 1;
				*ver = 1;
				*ant = aux->n;
				printarTabuleiro(tabPlayer, tabBot, *pontP, *pontB);
				return verificarJogada(tabPlayer, tabBot, NULL, *ant, pontP, pontB, ver);
			}
		
		}
		
/* 3.		 
		 *
		 *<-- Último tiro
		  <-- Caso não nulo e não atingido, atira aqui
	
									*/
		else if((aux->n != NULL && aux->n->simb_ex == '*') && (aux->s != NULL && aux->s->hit == 0)){
			if(aux->s->simb_ex == ' '){
				aux->s->simb_ex = 'O';
				return;
			}
			else if(aux->s->simb_ex == 'O'){
				aux = *ant;
			}
			else{
				aux->s->simb_ex = '*';
				aux->s->hit = 1;
				*ver = 1;
				*ant = aux->s;
				printarTabuleiro(tabPlayer, tabBot, *pontP, *pontB);
				return verificarJogada(tabPlayer, tabBot, NULL, *ant, pontP, pontB, ver);
			}
		}
		
/* 4.		 Último tiro em qualquer uma destas posições
		 |
		vvv
		**** 
		    ^
		    |
		    Caso não nulo e não atingido, atira aqui	
		    							*/
		if(aux->e != NULL && aux->e->simb_ex == '*'){
			
			while(aux->e != NULL && aux->e->simb_ex == '*')
				aux = aux->e;
				
			if (aux->e == NULL)
				aux = *ant;
				
			else if(aux->e->simb_ex == 'O')
				aux = *ant;
		
			else if(aux->e->simb_ex == ' '){
				aux->e->simb_ex = 'O';
				aux->hit = 1;
				printarTabuleiro(tabPlayer, tabBot, *pontP, *pontB);
				return;
			}
			else{
				aux->e->simb_ex = '*';
				aux->e->hit = 1;
				*ver = 1;
				*ant = aux->e;
				printarTabuleiro(tabPlayer, tabBot, *pontP, *pontB);
				return verificarJogada(tabPlayer, tabBot, NULL, *ant, pontP, pontB, ver);
			}
		}
		
/* 5.		   
		   Último tiro em qualquer uma destas posições
		   |
		  vvv
		 **** 
		^
		|
		Caso não nulo e não atingido, atira aqui	
									*/
		else if(aux->w != NULL && aux->w->simb_ex == '*'){
		
			while(aux->w != NULL && aux->w->simb_ex == '*')
				aux = aux->w;
				
			if (aux->w == NULL)
				aux = *ant;
					
			else if(aux->w->simb_ex == 'O')
				aux = *ant;
			
				else if(aux->w->simb_ex == ' '){
					aux->w->simb_ex = 'O';
					aux->hit = 1;
					printarTabuleiro(tabPlayer, tabBot, *pontP, *pontB);
				return;
				}
			else{
				aux->w->simb_ex = '*';
				aux->w->hit = 1;
				*ver = 1;
				*ant = aux->w;
				printarTabuleiro(tabPlayer, tabBot, *pontP, *pontB);
				return verificarJogada(tabPlayer, tabBot, NULL, *ant, pontP, pontB, ver);
			}
		}
			
/* 3.		 
		  <-- Caso não nulo e não atingido, atira aqui
		 *
		 *<
		 *<-- Último tiro em qualquer uma destas posições
		 *<
		  								*/
		else if(aux->n != NULL && aux->n->simb_ex == '*'){
		
			while(aux->n != NULL && aux->n->simb_ex == '*')
				aux = aux->n;
			
			if (aux->n == NULL)
				aux = *ant;
					
			else if(aux->n->simb_ex == 'O')
				aux = *ant;
			
			else if(aux->n->simb_ex == ' '){
				aux->n->simb_ex = 'O';
				aux->hit = 1;
				printarTabuleiro(tabPlayer, tabBot, *pontP, *pontB);
				return;
			}
			else{
				aux->n->simb_ex = '*';
				aux->n->hit = 1;
				*ver = 1;
				*ant = aux->n;
				printarTabuleiro(tabPlayer, tabBot, *pontP, *pontB);
				return verificarJogada(tabPlayer, tabBot, NULL, *ant, pontP, pontB, ver);
			}
		}
		
/* 4.		 
		 *<
		 *<-- Último tiro em qualquer uma destas posições
		 *<
		 *
		  <-- Caso não nulo e não atingido, atira aqui		*/
		else if(aux->s != NULL && aux->s->simb_ex == '*'){
		
			while(aux->s != NULL && aux->s->simb_ex == '*')
				aux = aux->s;
			
			if (aux->s == NULL)
				aux = *ant;
					
			else if(aux->s->simb_ex == 'O')
				aux = *ant;
			
			else if(aux->s->simb_ex == ' '){
				aux->s->simb_ex = 'O';
				aux->hit = 1;
				printarTabuleiro(tabPlayer, tabBot, *pontP, *pontB);
				return;
			}
			else{
				aux->s->simb_ex = '*';
				aux->s->hit = 1;
				*ant = aux->s;
				*ver = 1;
				printarTabuleiro(tabPlayer, tabBot, *pontP, *pontB);
				return verificarJogada(tabPlayer, tabBot, NULL, *ant, pontP, pontB, ver);
			}
		}
		
		//Escolhe aletóriamente um dos lados da coordenada atingida.
		else{

			while(escolhendo){
				aux = *ant;
				srand(time(NULL));
				escolha = rand()%4;
				escolhendo = 0;
			
				if(escolha == 0)
					aux = aux->e;
				else if(escolha == 1)
					aux = aux->w;
				else if(escolha == 2)
					aux = aux->n;
				else if(escolha == 3)
					aux = aux->s;
					
				if(aux == NULL)
					escolhendo = 1;
				else{
					if(aux->simb_ex == '*' || aux->simb_ex == 'O')
						escolhendo = 1;
					else if(aux->simb_ex == ' '){
						aux->simb_ex = 'O';
						aux->hit = 1;
						printarTabuleiro(tabPlayer, tabBot, *pontP, *pontB);
						return;
					}
					else{
						aux->simb_ex = '*';
						aux->hit = 1;
						*ver = 1;
						*ant = aux;
						printarTabuleiro(tabPlayer, tabBot, *pontP, *pontB);
						return verificarJogada(tabPlayer, tabBot, NULL, *ant, pontP, pontB, ver);
				
					}
				}
			}
		}
		
		//Escolhe aleatóriamente qualquer coordenada caso alguma desgraça acometa os if anteriores.
		while(escolhendo){
		
			srand(time(NULL));
			l = rand()%12;
			c = rand()%12;
			
			aux = tabPlayer;
			escolhendo = 0;
			
			for(int i = 0; i <= l; i++){
				aux = aux->s;
				
				for(int j = 0; j <= c; j++)
					aux = aux->e;
			}
		
			if(aux->simb_ex == '*' || aux->simb_ex == 'O')
				escolhendo = 1;
			else if(aux->simb_ex == ' '){
				aux->hit = 1;
				aux->simb_ex = 'O';
				printarTabuleiro(tabPlayer, tabBot, *pontP, *pontB);
				return;
			}
			else{
				aux->simb_ex = '*';
				aux->hit = 1;
				*ver = 1;
				*ant = aux;
				printarTabuleiro(tabPlayer, tabBot, *pontP, *pontB);
				return verificarJogada(tabPlayer, tabBot, NULL, *ant, pontP, pontB, ver);
			}
		}
	}
}
