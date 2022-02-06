#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <unistd.h> 
//#include <dos.h>
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
			no->ori = '1';
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

void removerSub(coord* tab)
{
    coord *no = tab;
    int par = 0; int cont = 0;
    /*while(no->type != 's' && cont < 12)
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
        printf("e\n");
        printf("%d\n", cont);
    }
	printf("alguma coisa\n");
	*/
	
	for(int l = 1; l <= 12 && no->type != 's'; l++){

		no = tab;
		
		for(int l2 = 1; l2 < l && no->type != 's'; l2++){
			
			no = no->s;
		}
		for(int c = 1; c <= 12 && no->type != 's'; c++){
		
			if(c < 12)
				no = no->e;
		}		
	}
    if (no->type == 's')
    {
        no->type = '0';
        no->simb = ' ';
        no->simb_ex = ' ';
    }

    else return;
}

void verificarJogada(coord* tabP, coord* tabB, coord* acertoP, coord* acertoB, int* pontP, int* pontB){

	int afundado = 1;
	coord* aux;
	
	//Verifica jogada do player
	if(acertoB == NULL){
		
		aux = acertoP;
		if(aux->type == 'j'){
			aux->simb_ex = aux->simb;
			*pontB += 1;
			removerSub(tabP);
		}
		else if(aux->type == 's'){
			aux->simb_ex = aux->simb;
			*pontP += 1;
			printarTabuleiro(tabP, tabB);
			input(tabP, tabB, pontP, pontB);
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
			input(tabP, tabB, pontP, pontB);
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

int input(coord* tabP, coord* tabB, int* pontP, int* pontB)
{

    coord* noh = tabB;
    int cont = 1;

    while(1)
    {
        char input[5]; int coordenadas[2];

        scanf("%s", input);

        for (int i = 0; i < 5; i++)
        {
            if (((int)(input[i]) > 64 && (int)(input[i]) < 77) || (int)(input[i]) > 96 && (int)(input[i]) < 109)
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
            verificarJogada(tabP, tabB, noh, NULL, pontP, pontB);
        }

        else noh->simb_ex = 'O';

        break;
    }
}

void jogada(coord* tabPlayer, coord* tabBot, int ver, coord** ant, int* pontP, int* pontB){

	coord *aux;
	
	int l, c, escolhendo = 1, escolha;
	
	if (ver == 0){
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
			c = rand()%12;
			
			aux = tabPlayer;
			escolhendo = 0;
			
			for(int i = 0; i <= l; i++){
				aux = aux->s;
				
				for(int j = 0; j <= c; j++)
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

//Para testes
int main(){
	
	int pontP = 0, pontB = 0;
	coord *tabP = NULL; 
	coord *tabB = NULL;
	iniciarTabuleiro(&tabP, &tabB);
	PreencherTabuleiro(tabP);
	sleep(1);
	PreencherTabuleiro(tabB);
	printarTabuleiro(tabP, tabB);
	while(1){
		input(tabP, tabB, &pontP, &pontB);
		printarTabuleiro(tabP, tabB);
	}
}
