#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> //Linux
//#include <dos.h> //Windows
#include "api.h"

void jogadaBot(coord* tabPlayer, coord* tabBot, int* ver, coord** ant, int* pontP, int* pontB){

	coord *aux, *aux2;
	
	int l, c, escolhendo = 1, escolha;
	
	if (*ver == 0){
		while(escolhendo){
		
			srand(time(NULL));
			l = rand()%12;
			c = rand()%12;
			
			printf("L = %d\n", l + 1);
			printf("C = %d\n", c + 1);
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
				return;
			}
			else{	
				aux2 = aux;
				aux->simb_ex = '*';
				*ver = 1;
				*ant = aux2;
				printarTabuleiro(tabPlayer, tabBot);
				return verificarJogada(tabPlayer, tabBot, NULL, *ant, pontP, pontB, ver);
			}
		}
	}
	
	else{
		aux = *ant;
		
		//Verifica uma extremidade
		//Verifica para a esquerda
		if((aux->e != NULL && aux->e->simb_ex == '*') && (aux->w != NULL && aux->w->simb_ex == ' ')){
		
			aux->w->simb_ex = '*';
			*ver = 1;
			*ant = aux->w;
			printarTabuleiro(tabPlayer, tabBot);
			return verificarJogada(tabPlayer, tabBot, NULL, *ant, pontP, pontB, ver);
		
		}
		
		//Verifica para a direita
		else if((aux->w != NULL && aux->w->simb_ex == '*') && (aux->e != NULL && aux->e->simb_ex == ' ')){
		
			aux->e->simb_ex = '*';
			*ver = 1;
			*ant = aux->e;
			printarTabuleiro(tabPlayer, tabBot);
			return verificarJogada(tabPlayer, tabBot, NULL, *ant, pontP, pontB, ver);
		
		}
		
			
		//Verifica para cima
		else if((aux->s != NULL && aux->s->simb_ex == '*') && (aux->n != NULL && aux->n->simb_ex == ' ')){
		
			aux->n->simb_ex = '*';
			*ver = 1;
			*ant = aux->n;
			printarTabuleiro(tabPlayer, tabBot);
			return verificarJogada(tabPlayer, tabBot, NULL, *ant, pontP, pontB, ver);
		
		}
		
		//Verifica para baixo
		else if((aux->n != NULL && aux->n->simb_ex == '*') && (aux->s != NULL && aux->s->simb_ex == ' ')){
		
			aux->s->simb_ex = '*';
			*ver = 1;
			*ant = aux->s;
			printarTabuleiro(tabPlayer, tabBot);
			return verificarJogada(tabPlayer, tabBot, NULL, *ant, pontP, pontB, ver);
		
		}
		
		//Vai para a outra extreminadade do navio
		//Verifica para a direita
		if(aux->e != NULL && aux->e->simb_ex == '*'){
		
			while(aux->e != NULL && aux->e->simb_ex == '*')
				aux = aux->e;
				
			if (aux->e == NULL)
				aux = *ant;
				
			else if(aux->e->simb_ex == 'O')
				aux = *ant;
		
			else if(aux->e->simb_ex == ' '){
				aux->e->simb_ex = 'O';
				return;
			}
			else{
				aux->e->simb_ex = '*';
				*ver = 1;
				*ant = aux->e;
				printarTabuleiro(tabPlayer, tabBot);
				return verificarJogada(tabPlayer, tabBot, NULL, *ant, pontP, pontB, ver);
			}
		}
		
		//Verifica para a esquerda
		else if(aux->w != NULL && aux->w->simb_ex == '*'){
		
			while(aux->w != NULL && aux->w->simb_ex == '*')
				aux = aux->w;
				
			if (aux->w == NULL)
				aux = *ant;
					
			else if(aux->w->simb_ex == 'O')
				aux = *ant;
			
				else if(aux->w->simb_ex == ' '){
					aux->w->simb_ex = 'O';
				return;
				}
			else{
				aux->w->simb_ex = '*';
				*ver = 1;
				*ant = aux->w;
				printarTabuleiro(tabPlayer, tabBot);
				return verificarJogada(tabPlayer, tabBot, NULL, *ant, pontP, pontB, ver);
			}
		}
		
			
		//Verifica para cima
		else if(aux->n != NULL && aux->n->simb_ex == '*'){
			while(aux->n != NULL && aux->n->simb_ex == '*')
				aux = aux->n;
			
			if (aux->n == NULL)
				aux = *ant;
					
			else if(aux->n->simb_ex == 'O')
				aux = *ant;
			
			else if(aux->n->simb_ex == ' '){
				aux->n->simb_ex = 'O';
				return;
			}
			else{
				aux->n->simb_ex = '*';
				*ver = 1;
				*ant = aux->n;
				printarTabuleiro(tabPlayer, tabBot);
				return verificarJogada(tabPlayer, tabBot, NULL, *ant, pontP, pontB, ver);
			}
		}
		
		//Verifica para baixo
		else if(aux->s != NULL && aux->s->simb_ex == '*'){
		
			while(aux->s != NULL && aux->s->simb_ex == '*')
				aux = aux->s;
			
			if (aux->s == NULL)
				aux = *ant;
					
			else if(aux->s->simb_ex == 'O')
				aux = *ant;
			
			else if(aux->s->simb_ex == ' '){
				aux->s->simb_ex = 'O';
				return;
			}
			else{
				aux->s->simb_ex = '*';
				*ant = aux->s;
				*ver = 1;
				printarTabuleiro(tabPlayer, tabBot);
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
						return;
					}
					else{
						aux->simb_ex = '*';
						*ver = 1;
						*ant = aux;
						printarTabuleiro(tabPlayer, tabBot);
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
				aux->simb_ex = 'O';
				return;
			}
			else{
				aux->simb_ex = '*';
				*ver = 1;
				*ant = aux;
				printarTabuleiro(tabPlayer, tabBot);
				return verificarJogada(tabPlayer, tabBot, NULL, *ant, pontP, pontB, ver);
			}
		}
	}
}
