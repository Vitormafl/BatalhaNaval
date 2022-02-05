#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "api.h"

void iniciarTabuleiro(coord** tabPlayer, coordB** tabBot){
	
	coord *no, *aux;
	coordB *no2, *aux2;
	
	//Inicia o tabuleiro do player
	for(int l = 0; l < 12; l++){

		no = *tabPlayer;
		for(int i = 0; i < l - 1; i++){ 
			
			no = no->s;
		}
		
		if(l == 0){
			
			no = (coord*)malloc(sizeof(coord));
			no->simb = ' ';
			no->type = '0';
			no->n = NULL;
			no->w = NULL;
			*tabPlayer = no;
		}
		else if (l < 12){
			
			no->s = (coord*)malloc(sizeof(coord));
			aux = no;
			no = no->s;
			no->n = aux;
			no->w = NULL;
			no->simb = ' ';
			no->type = '0';
			if(l == 11) no->s = NULL;
		}
			
		for(int c = 0; c < 11; c++){
			
			if(l == 0) no->n = NULL;
			else if(c > 0){

				no->n = no->w->n->e;
				no->n->s = no;
			}

			if(c < 11){
				no->e = (coord*)malloc(sizeof(coord));
				aux = no;
				no = no->e;
				no->w = aux;
				no->simb = ' ';
				no->type = '0';
			}
			else{
				no->e = NULL;
			}
		}
	}
	
	//Inicia o tabuleiro do bot
	for(int l = 0; l < 12; l++){

		no2 = *tabBot;
		for(int i = 0; i < l - 1; i++){ 
		
			no2 = no2->s;
		}
		
		if(l == 0){
			
			no2 = (coordB*)malloc(sizeof(coordB));
			no2->simb_ex = ' ';
			no2->simb = ' ';
			no2->type = '0';
			no2->n = NULL;
			no2->w = NULL;
			*tabBot = no2;
		}
		else if (l < 12){
			
			no2->s = (coordB*)malloc(sizeof(coordB));
			aux2 = no2;
			no2 = no2->s;
			no2->n = aux2;
			no2->w = NULL;
			no2->simb = ' ';
			no2->simb_ex = ' ';
			no2->type = '0';
			if(l == 11) no2->s = NULL;
		}
			
		for(int c = 0; c < 11; c++){
			
			if(l == 0) no2->n = NULL;
			else if(c > 0) {

				no2->n = no2->w->n->e;
				no2->n->s = no2;
			}

			if(c < 11){

				no2->e = (coordB*)malloc(sizeof(coordB));
				aux2 = no2;
				no2 = no2->e;
				no2->w = aux2;
				no2->simb = ' ';
				no2->simb_ex = ' ';
				no2->type = '0';
			}
			else{
				no2->e = NULL;
			}

		}
	}
}

//Printa o estado atual doo tabuleiro
void printarTabuleiro(coord* tabPlayer, coordB* tabBot){
	
	coord *noP;
	coordB *noB;
	
	printf("      Humano          Computador  \n\n");
	printf("   ABCDEFGHIJKL      ABCDEFGHIJKL \n");
	printf("  +------------+    +------------+\n");
	
	for(int l = 1; l <= 12; l++){

		noP = tabPlayer;
		noB = tabBot;
		printf("%2d+", l);
		
		for(int l2 = 1; l2 < l; l2++){
		
			noP = noP->s;
			noB = noB->s;
		}
		for(int c = 1; c <= 12; c++){
		
			printf("%c", noP->simb);
			if(c < 12)
				noP = noP->e;
		}
		printf("+  %2d+", l);
		for(int c2 = 1; c2 <= 12; c2++){
		
			printf("%c", noB->simb_ex);
			if(c2 < 12)
				noB = noB->e;
		}
		printf("+\n");
		
	}
	printf("  +------------+    +------------+\n");
}

//Itera pelos tabuleiros e reinicia os símbolos e embarcações
void reset(coord* tabPlayer, coordB* tabBot){

	coord* noP;
	coordB* noB;
	
	for(int l = 1; l <= 12; l++){

		noP = tabPlayer;
		noB = tabBot;
		
		for(int l2 = 1; l2 < l; l2++){
		
			noP = noP->s;
			noB = noB->s;
		}
		for(int c = 1; c <= 12; c++){
		
			noP->simb = ' ';
			noP->type = 0;
			if(c < 12)
				noP = noP->e;
		}
		for(int c2 = 1; c2 <= 12; c2++){
		
			noB->simb = ' ';
			noB->type = 0;
			if(c2 < 12)
				noB = noB->e;
		}
		
	}
}

//INCOMPLETA
void PreencherTabuleiro(coord* tab){

	coord* no;
	no = tab;

	int linha_r[9], coluna_r[9], direction[9], aux = 0, j = 0;

	srand(time(NULL));

	linha_r[j] = rand()%12;
	coluna_r[j] = rand()%12;
	direction[j] = rand()%2;
	
	if(direction[j] == 0){
		while(coluna_r[j] > 7)
			coluna_r[j] = rand()%12;
	}
	else{
        	while(linha_r[j] > 7){
               	linha_r[j] = rand()%12;
   		}
   	}
    
   	for(int i = 0; i < coluna_r[j]; i++ ){
        	no = no->e;
    	}
    	for(int p = 0; p < linha_r[j]; p++ ){
       	no = no->s;
	}
	
	if(direction[j] == 0){
		for(int i = 0; i < 5; i++){
			no->type = 'a';
			no->ori = '0';
			if(i == 0)
				no->simb = '<';
			else if(i < 4)
				no->simb = '#';
			else{
				no->simb = '>';
			}
			no = no->e;
		}
	}
	else{
		for(int i = 0; i < 5; i++){
			no->type = 'a';
			no->ori = '1';
			if(i == 0)
				no->simb = '^';
			else if(i < 4)
				no->simb = '#';
			else{
				no->simb = 'v';
			}
			no = no->s;
		}
	}
	
	printf("AiC-linha: %d, coluna: %d, direção: %d, barco n: %d\n",linha_r[j], coluna_r[j], direction[j], j);
	j = j + 1;
	
	for(int l = 0; l < 2; l++){
		while(aux == 0){
		
			no = tab;
			aux = 1;

			linha_r[j] = rand()%12;
			coluna_r[j] = rand()%12;
			direction[j] = rand()%2;
		
			if(direction[j] == 0){
				while(coluna_r[j] > 9){
					coluna_r[j] = rand()%12;
				}
				for(int i = 0; i < coluna_r[j]; i++ ){
					no = no->e;
		    		}
			    	for(int k = 0; k < linha_r[j]; k++ ){
			       	 no = no->s;	
				}
				for(int m = 0; m < 3; m ++){
					if(no->type != '0')
						aux = 0;
					no = no->e;
				}
			}
			else{
				while(linha_r[j] > 9){
			       	linha_r[j] = rand()%12;
		   		}
		   		for(int i = 0; i < coluna_r[j]; i++ ){
					no = no->e;
		    		}
			    	for(int m = 0; m < linha_r[j]; m++ ){
			       	 no = no->s;	
				}
				
				for(int k = 0; k < 3; k ++){
					if(no->type != '0')
						aux = 0;
					no = no->s;
				}
		   	}
		}
		
		if(direction[j] == 0){
			for(int i = 0; i < 3; i++){
				no->type = 'd';
				no->ori = '0';
				if(i == 0)
					no->simb = '>';
				else if(i < 2)
					no->simb = '#';
				else{
					no->simb = '<';
				}
				no = no->w;
			}
		}
		else{
			for(int i = 0; i < 3; i++){
				no->type = 'd';
				no->ori = '1';
				if(i == 0)
					no->simb = 'v';
				else if(i < 2)
					no->simb = '#';
				else{
					no->simb = '^';
				}
				no = no->n;
			}
		}
		printf("Des-linha: %d, coluna: %d, direção: %d, barco n: %d\n",linha_r[j], coluna_r[j], direction[j], j);
		j = j + 1;
		aux = 0;
	}
	

}


//Para testes
int main(){
	
	coord *tabP = NULL; 
	coordB *tabB = NULL;
	iniciarTabuleiro(&tabP, &tabB);
	printarTabuleiro(tabP, tabB);
}

