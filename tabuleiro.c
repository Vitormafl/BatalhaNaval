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

		}
	}
}

//Printa o estado atual doo tabuleiro
void printarTabuleiro(coord* tabPlayer, coord* tabBot){
	
	coord *noP;
	coord *noB;
	
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
void reset(coord* tabPlayer, coord* tabBot){

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
			noP->type = 0;
			if(c < 12)
				noP = noP->e;
		}
		for(int c2 = 1; c2 <= 12; c2++){
		
			noB->simb = ' ';
			noB->simb_ex = ' ';
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
	
	printf("AiC-linha: %d, coluna: %d, direção: %d, barco n: %d\n",linha_r[j], coluna_r[j], direction[j], j);
	
	if(direction[j] == 0){
		for(int i = 0; i < 5; i++){
			no->type = 'p';
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
			no->type = 'p';
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
		
		printf("Des-linha: %d, coluna: %d, direção: %d, barco n: %d\n",linha_r[j], coluna_r[j], direction[j], j);
		
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
		
		printf("Pa-linha: %d, coluna: %d, direção: %d, barco n: %d\n",linha_r[j], coluna_r[j], direction[j], j);
		
		if(direction[j] == 0){
			for(int i = 0; i < 2; i++){
				no->type = 'f';
				no->ori = '0';
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
				no->ori = '1';
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
		printf("sub-linha: %d, coluna: %d, barco n: %d\n",linha_r[j], coluna_r[j],j);
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
	printf("Jang-linha: %d, coluna: %d, barco n: %d\n",linha_r[j], coluna_r[j], j);
}
void verificarJogada(coord* tabP, coord* tabB, coord* acertoP, coord* acertoB, int* pontP, int* pontB){

	int afundado = 1;
	coord* aux;
	
	//Verifica jogada do player
	if(acertoB == NULL){
		
		aux = acerto;;
		if(aux->type == 'j'){
			aux->simb_ex = aux->simb;
			*pontB += 1;
			removerSub(tabP);
		}
		else if(aux->type == 's'){
			aux->simb_ex = aux->simb;
			*pontP += 1;
			input(tabp, tabB, pontP, pontB);
		}
		//Se acertou um navio horizontal
		else if(aux->ori == 0){
		
			//1. Vai até a extremidade direita do navio
			while(aux->simb != '>')
				aux = aux->e;
			
			//2. volta até a extremidade direita do navio, verificando se ele foi totalmente afundado
			do{
				if(aux->simb_ex != '*')
					afundado = 0;
					
				aux = aux->w;
					
			}while(aux->simb != '<');
			
			//3. Caso afundou um navio do bot, revela ele por completo.
			if(afundado){
				do{
				aux->simb_ex = aux->simb;
				aux = aux->e;
				
				}while(aux->simb_ex != '>');
				*pontP += 1;

			}
			input(tabp, tabB, pontP, pontB);
		}
		//Se acertou um navio vertical
		else{
			//1. 
			while(aux->simb != 'v')
				aux = aux->s;
			
			//2. 
			do{
			
				if(aux->simb_ex != '*')
					afundado = 0;
				
				aux = aux->n;
			
			}while(aux->simb != '^');
			
			//3.
			if(afundado){
				do{
					aux->simb_ex = aux->simb;
					aux = acertoB->s;
					
				}while(aux->simb_ex!= 'v');
				*pontP += 1;
			}
		}
	}
	
	
	//Verifica jogada do bot			
	else{
	
		if(acertoB->type == 'j'){
			*pontB += 1;
			removerSub(tabB);
		}
		else if(acertoB->type == 's'){
			*pontB += 1;
			jogada(tabP, tabB, 0, &acertoB, pontP, pontB);
		}
		//Se acertou um navio horizontal
		if(acertoB->ori == 0){
			
			//1. Vai até a extremidade direita do navio
			while(acertoB->simb != '>')
				acertoB = acertoB->e;
			
			//2. volta até a extremidade direita do navio, verificando se ele foi totalmente afundado
			do{
				if(acertoB->simb_ex != '*')
					afundado = 0;
					
				acertoB = acertoB->w;
				
			}while(acertoB->simb != '<');
			
			//3. Caso afundou um navio do player, joga de novo aleatoriamente.
			if(afundado){
				*pontB += 1;
				return jogada(tabP, tabB, 0, &acertoB, pontP, pontB);
			}
			//4. Caso não tenha afundado o navio do player, joga de novo tentando afundar.
			jogada(tabP, tabB, 1, &acertoB, pontP, pontB);
		}
		
		//Se acertou um navio vertical
		else{
			//1. 
			while(acertoB->simb != 'v')
				acertoB = acertoB->s;
			
			//2. 	
			do{
			
				if(acertoB->simb_ex != '*')
					afundado = 0;
					
				acertoB = acertoB->n;
				
			}while(acertoB->simb != '^');
			
			//3.
			if(afundado){
			
				*pontB += 1;
				return jogada(tabP, tabB, 0, &acertoB, pontP, pontB);
			}
			//4.
			jogada(tabP, tabB, 1, &acertoB, pontP, pontB);
		}
	}
}

//Para testes
int main(){
	
	coord *tabP = NULL; 
	coordB *tabB = NULL;
	iniciarTabuleiro(&tabP, &tabB);
	printarTabuleiro(tabP, tabB);
}

