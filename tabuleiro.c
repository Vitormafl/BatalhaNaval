#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "api.h"

void iniciarTabuleiro(coord** tabPlayer, coord** tabBot){
	
	coord *no, *aux;
	
	//Inicia o tabuleiro do player
	for(int l = 0; l < 12; l++){

		no = *tabPlayer;
		for(int i = 0; i < l - 1; i++){ 
			
			no = no->s;
		}
		
		//Printa os nós criados, de forma ordenada
		if(l == 0){
			
			no = (coord*)malloc(sizeof(coord));
			no->simb_ex = ' ';
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
			no->simb_ex = ' ';
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
				no->simb_ex = ' ';
				no->simb = ' ';
				no->type = '0';
			}
			else{
				no->e = NULL;
			}
			if(l != 0 && c > 0){
			
				no->n = no->w->n->e;
				no->n->s = no;
			}
		}
	}
	
	//Inicia o tabuleiro do bot
	for(int l = 0; l < 12; l++){

		no = *tabBot;
		for(int i = 0; i < l - 1; i++){ 
		
			no = no->s;
		}
		
		if(l == 0){
			
			no = (coord*)malloc(sizeof(coord));
			no->simb_ex = ' ';
			no->simb = ' ';
			no->type = '0';
			no->n = NULL;
			no->w = NULL;
			*tabBot = no;
		}
		else if (l < 12){
			
			no->s = (coord*)malloc(sizeof(coord));
			aux = no;
			no = no->s;
			no->n = aux;
			no->w = NULL;
			no->simb = ' ';
			no->simb_ex = ' ';
			no->type = '0';
			if(l == 11) no->s = NULL;
		}
			
		for(int c = 0; c < 11; c++){
			
			if(l == 0) no->n = NULL;
			else if(c > 0) {

				no->n = no->w->n->e;
				no->n->s = no;
			}

			if(c < 11){

				no->e = (coord*)malloc(sizeof(coord));
				aux = no;
				no = no->e;
				no->w = aux;
				no->simb = ' ';
				no->simb_ex = ' ';
				no->type = '0';
			}
			else{
				no->e = NULL;
			}
			if(l != 0 && c > 0){
			
				no->n = no->w->n->e;
				no->n->s = no;
			}

		}
	}
}

//Printa o estado atual doo tabuleiro
void printarTabuleiro(coord* tabPlayer, coord* tabBot, int pontP, int pontB){
	
	coord *noP;
	coord *noB;
	
	printf("\n      Humano          Computador  \n\n");
	printf("   ABCDEFGHIJKL      ABCDEFGHIJKL \n");
	printf("  +------------+    +------------+\n");
	
	//Printa os nós criados, de forma ordenada
	for(int l = 1; l <= 12; l++){

		noP = tabPlayer;
		noB = tabBot;
		printf("%2d+", l);
		
		for(int l2 = 1; l2 < l; l2++){
		
			noP = noP->s;
			noB = noB->s;
		}
		for(int c = 1; c <= 12; c++){
			
			printf("%c", noP->simb_ex);
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
	printf("  +------------+    +------------+\n\n");
	printf("              Placar:             \n");
	printf("    Humano: %d        Computador %d \n", pontP, pontB);
}

//Itera pelos tabuleiros e reinicia os símbolos e embarcações
void reset(coord* tabPlayer, coord* tabBot, int* pontP, int* pontB){

	coord* noP;
	coord* noB;
	
	for(int l = 1; l <= 12; l++){

		noP = tabPlayer;
		noB = tabBot;
		
		for(int l2 = 1; l2 < l; l2++){
		
			noP = noP->s;
			noB = noB->s;
		}
		for(int c = 1; c <= 12; c++){
		
			noP->simb = ' ';
			noP->simb_ex = ' ';
			noP->type = '0';
			noP->hit = 0;
			if(c < 12)
				noP = noP->e;
		}
		for(int c2 = 1; c2 <= 12; c2++){
		
			noB->simb = ' ';
			noB->simb_ex = ' ';
			noB->type = '0';
			noB->hit = 0;
			if(c2 < 12)
				noB = noB->e;
		}
		
	}
	*pontP = 0;
	*pontB = 0;
}

//INCOMPLETA
void PreencherTabuleiro(coord* tab){

	coord* no;
	no = tab;
	
	//Usamos 3 vetores para definir as coordenadas de cada barco de forma aleatória
	int linha_r[9], coluna_r[9], direction[9], aux = 0, j = 0;

	srand(time(NULL));

	linha_r[j] = rand()%12;
	coluna_r[j] = rand()%12;
	direction[j] = rand()%2;
	
	//Verificamos se o barco foi inicializado de forma a sair do tabuleiro
	if(direction[j] == 0){
		while(coluna_r[j] > 7)
			coluna_r[j] = rand()%12;
	}
	else{
		while(linha_r[j] > 7){
	       	linha_r[j] = rand()%12;
		}
   	}
	
	//Percorremos os nós até chegar no primeiro nó do barco
   	for(int i = 0; i < coluna_r[j]; i++ ){
        	no = no->e;
    	}
    	for(int p = 0; p < linha_r[j]; p++ ){
       	no = no->s;
	}
	
	//Dependendo da orientação do barco os nós são devidamente preenchidos e percorridos
	if(direction[j] == 0){
		for(int i = 0; i < 5; i++){
			no->type = 'p';
			no->ori = 0;
			if(i == 0){
				no->simb = '<';
			}
			else if(i < 4){
				no->simb = '#';
			}
			else{
				no->simb = '>';
			}
			no = no->e;
		}
	}
	else{
		for(int i = 0; i < 5; i++){
			no->type = 'p';
			no->ori = 1;
			if(i == 0){
				no->simb = '^';
			}
			else if(i < 4){
				no->simb = '#';
			}
			else{
				no->simb = 'v';
			}
			no = no->s;
		}
	}
	j = j + 1;
	
	//Inicialização do segundo tipo de barco
	for(int l = 0; l < 2; l++){
		while(aux == 0){
		
			no = tab;
			aux = 1;

			linha_r[j] = rand()%12;
			coluna_r[j] = rand()%12;
			direction[j] = rand()%2;
			
			//Tudo é feito exatamente como o barco anterior...
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
				
				//A não ser nessa parte, onde é feita uma verificação para saber se os nós que serão habitados já estão ocupados
				for(int m = 0; m < 3; m ++){
					if(no->type != '0')
						aux = 0;
					if(m != 2)
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
					if(k != 2)
						no = no->s;
				}
		   	}
		}
		
		if(direction[j] == 0){
			for(int i = 0; i < 3; i++){
				no->type = 'd';
				no->ori = 0;
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
				no->ori = 1;
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
		
		j = j + 1;
		aux = 0;
	}
	
	for(int l = 0; l < 3; l++){
		while(aux == 0){
		
			no = tab;
			aux = 1;

			linha_r[j] = rand()%12;
			coluna_r[j] = rand()%12;
			direction[j] = rand()%2;
		
			if(direction[j] == 0){
				while(coluna_r[j] > 10){
					coluna_r[j] = rand()%12;
				}
				for(int i = 0; i < coluna_r[j]; i++ ){
					no = no->e;
		    		}
			    	for(int k = 0; k < linha_r[j]; k++ ){
			       	 no = no->s;	
				}
				for(int m = 0; m < 2; m ++){
					if(no->type != '0')
						aux = 0;
					if(m != 1)
						no = no->e;
				}
			}
			else{
				while(linha_r[j] > 10){
			       	linha_r[j] = rand()%12;
		   		}
		   		for(int i = 0; i < coluna_r[j]; i++ ){
					no = no->e;
		    		}
			    	for(int m = 0; m < linha_r[j]; m++ ){
			       	 no = no->s;	
				}
				
				for(int k = 0; k < 2; k ++){
					if(no->type != '0')
						aux = 0;
					if(k != 1)
						no = no->s;
				}
		   	}
		}
		
		if(direction[j] == 0){
			for(int i = 0; i < 2; i++){
				no->type = 'f';
				no->ori = 0;
				if(i == 0)
					no->simb = '>';
				else{
					no->simb = '<';
				}
				no = no->w;
			}
		}
		else{
			for(int i = 0; i < 2; i++){
				no->type = 'f';
				no->ori = 1;
				if(i == 0)
					no->simb = 'v';
				else{
					no->simb = '^';
				}
				no = no->n;
			}
		}
		j = j + 1;
		aux = 0;
	}
	for(int l = 0; l < 2; l++){
		while(aux == 0){
		
			no = tab;
			aux = 1;

			linha_r[j] = rand()%12;
			coluna_r[j] = rand()%12;
		
			for(int i = 0; i < coluna_r[j]; i++ ){
				no = no->e;
		    	}
			for(int k = 0; k < linha_r[j]; k++ ){
				no = no->s;	
			}
			if(no->type != '0')
				aux = 0;
		}
		no->type = 's';
		no->simb = '@';
		
		j = j + 1;
		aux = 0; 	
		}
	while(aux == 0){
		no = tab;
		aux = 1;
		linha_r[j] = rand()%12;
		coluna_r[j] = rand()%12;			
		for(int i = 0; i < coluna_r[j]; i++ ){
			no = no->e;
		}
		for(int k = 0; k < linha_r[j]; k++ ){
			no = no->s;	
		}
		if(no->type != '0')
			aux = 0;
	}
	no->type = 'j';
	no->simb = '&';	
}

//Revela os navios de um tabuleiro (usada para tornar o tabuleiro do player visível para ele)
void revelarTab(coord* tabP){

	coord* noP = tabP;
	
	if(noP != NULL){
		for(int l = 1; l <= 12; l++){

			noP = tabP;
		
			for(int l2 = 1; l2 < l; l2++){
		
				noP = noP->s;
			}
			for(int c = 1; c <= 12; c++){
			
				noP->simb_ex = noP->simb;
				if(c < 12)
					noP = noP->e;
			}
		}
	}
}
