#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "api.h"

void jogada(coord* tabPlayer, coord* tabBot, int ver, coord** ant, int* pontP, int* pontB){

	coord *aux;
	
	int l, c, escolhendo = 1, escolha;
	
	if (ver == 0){
		while(escolhendo){
		
			srand(time(NULL));
			l = rand()%12;
			j = rand()%12;
			
			aux = tabPlayer;
			escolhendo = 0;
			
			for(i = 0; i <= l, i++){
				
				aux = aux->s;
				for(j = 0; j <= c, j++)
					aux = aux->e;
			}
		
			if(aux->simb == '*' || aux->simb == 'O')
				escolhendo = 1;
			else if(aux->simb == ' '){
				aux->simb = 'O';
				return;
			}
			else{
				aux->simb = '*';
				*ant = aux;
				return verificarJogada(tabPlayer, tabBot, NULL, *ant, pontP, pontB);
			}
		}
	}
	
	else{
		aux = *ant;
		
		//Verifica para a direita
		if(aux->e->simb == '*'){
		
			while(aux->e != NULL && aux->e->simb == '*')
				aux = aux->e;
				
			if (aux->e == NULL)
				aux = *ant;
				
			else if(aux->e->simb == 'O')
				aux = *ant;
		
			else if(aux->e->simb == ' '){
				aux->e->simb = 'O';
				return;
			}
			else{
				aux->e->simb = '*';
				*ant = aux->e;
			
				return verificarJogada(tabPlayer, tabBot, NULL, *ant, pontP, pontB);
			}
		}
		
		//Verifica para a esquerda
		else if(aux->w->simb == '*'){
		
			while(aux->w != NULL && aux->w->simb == '*')
				aux = aux->w;
				
			if (aux->w == NULL)
				aux = *ant;
					
			else if(aux->w->simb == 'O')
				aux = *ant;
			
				else if(aux->w->simb == ' '){
				aux->w->simb = 'O';
				return;
			}
			else{
				aux->w->simb = '*';
				*ant = aux->w;
				
				return verificarJogada(tabPlayer, tabBot, NULL, *ant, pontP, pontB);
			}
		}
		
			
		//Verifica para cima
		else if(aux->n->simb == '*'){
			while(aux->n != NULL && aux->n->simb == '*')
				aux = aux->n;
			
			if (aux->n == NULL)
				aux = *ant;
					
			else if(aux->n->simb == 'O')
				aux = *ant;
			
			else if(aux->n->simb == ' '){
				aux->n->simb = 'O';
				return;
			}
			else{
				aux->n->simb = '*';
					*ant = aux->n;
				return verificarJogada(tabPlayer, tabBot, NULL, *ant, pontP, pontB);
			}
		}
		
		//Verifica para baixo
		else if(aux->s->simb == '*'){
		
			while(aux->s != NULL && aux->s->simb == '*')
				aux = aux->s;
			
			if (aux->s == NULL)
				aux = *ant;
					
			else if(aux->s->simb == 'O')
				aux = *ant;
			
			else if(aux->s->simb == ' '){
				aux->s->simb = 'O';
				return;
			}
			else{
				aux->s->simb = '*';
				*ant = aux->s;
				return verificarJogada(tabPlayer, tabBot, NULL, *ant, pontP, pontB);
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
					if(aux->simb == '*' || aux->simb == 'O')
						escolhendo = 1;
					else if(aux->simb == ' '){
						aux->simb = 'O';
						return;
					}
					else{
						aux->simb = '*';
						*ant = aux;
						return verificarJogada(tabPlayer, tabBot, NULL, *ant, pontP, pontB);
				
					}
				}
			}
		}
		
		//Escolhe aleatóriamente qualquer coordenada caso alguma desgraça acometa os if anteriores.
		while(escolhendo){
		
			srand(time(NULL));
			l = rand()%12;
			j = rand()%12;
			
			aux = tabPlayer;
			escolhendo = 0;
			
			for(i = 0; i <= l, i++){
				aux = aux->s;
				
				for(j = 0; j <= c, j++)
					aux = aux->e;
			}
		
			if(aux->simb == '*' || aux->simb == 'O')
				escolhendo = 1;
			else if(aux->simb == ' '){
				aux->simb = 'O';
				return;
			}
			else{
				aux->simb = '*';
				*ant = aux;
				verificarJogada(tabPlayer, tabBot, NULL, *ant, pontP, pontB);
			}
		}
	}
}
