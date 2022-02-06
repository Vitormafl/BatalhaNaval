#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <unistd.h> //Linux
//#include <dos.h> //Windows
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
			
			printf("%c", noP->simb_ex);
			if(c < 12)
				noP = noP->e;
		}
		printf("+  %2d+", l);
		for(int c2 = 1; c2 <= 12; c2++){
		
			printf("%c", noB->simb);
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

void removerSub(coord* tab)
{
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
	
	
	/*for(int l = 1; l <= 12 && no->type != 's'; l++){

		no = tab;
		
		for(int l2 = 1; l2 < l && no->type != 's'; l2++){
			
			no = no->s;
		}
		for(int c = 1; c <= 12 && no->type != 's'; c++){
		
			if(c < 12)
				no = no->e;
		}		
	}*/
    if (no->type == 's')
    {
        no->type = '0';
        no->simb = ' ';
        no->simb_ex = ' ';
    }

    else return;
}

void verificarJogada(coord* tabP, coord* tabB, coord* acertoP, coord* acertoB, int* pontP, int* pontB, int* ver){

	int afundado = 1;
	coord* aux;
	
	//Verifica jogada do player
	if(acertoB == NULL){
		aux = acertoP;
		if(aux->type == 'j'){
			aux->simb_ex = aux->simb;
			*pontB += 1;
			*ver = 0;
			removerSub(tabP);
		}
		else if(aux->type == 's'){
			aux->simb_ex = aux->simb;
			*pontP += 1;
			*ver = 0;
			printarTabuleiro(tabP, tabB);
			input(tabP, tabB, pontP, pontB, ver);
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
			printarTabuleiro(tabP, tabB);
			input(tabP, tabB, pontP, pontB, ver);
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
			printarTabuleiro(tabP, tabB);
			input(tabP, tabB, pontP, pontB, ver);
		}
	}
	
	
	//Verifica jogada do bot			
	else{
		aux = acertoB;
		if(aux->type == 'j'){
			printf(".\n");
			*pontB += 1;
			removerSub(tabB);
		}
		else if(aux->type == 's'){
			printf("0\n");
			*pontB += 1;
			*ver = 0;
			jogadaBot(tabP, tabB, ver, &acertoB, pontP, pontB);
		}
		//Se acertou um navio horizontal
		if(aux->ori == 0){
			printf("1\n");
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
			printf("afundado: %d\n", afundado);
			//3. Caso afundou um navio do player, joga de novo aleatoriamente.
			if(afundado){
				*pontB += 1;
				printf("A\n");
				*ver = 0;
				return jogadaBot(tabP, tabB, ver, &acertoB, pontP, pontB);
			}
			//4. Caso não tenha afundado o navio do player, joga de novo tentando afundar.
			jogadaBot(tabP, tabB, ver, &acertoB, pontP, pontB);
		}
		
		//Se acertou um navio vertical
		else{
			printf("3\n");
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
			printf("afundado: %d\n", afundado);
			//3.
			if(afundado){
			
				printf("B\n");
				*pontB += 1;
				*ver = 0;
				return jogadaBot(tabP, tabB, ver, &acertoB, pontP, pontB);
			}
			//4.
			jogadaBot(tabP, tabB, ver, &acertoB, pontP, pontB);
		}
	}
}

int input(coord* tabP, coord* tabB, int* pontP, int* pontB, int* ver)
{

    coord* noh = tabB;
    int cont = 1;

    while(1)
    {
        char input[5]; int coordenadas[2];

        scanf("%s", input);
	
        for (int i = 0; i < 5; i++)
        {
            if (isalpha(input[i]))
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
        if(coordenadas[0] > 12) continue;
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
            verificarJogada(tabP, tabB, noh, NULL, pontP, pontB, ver);
        }

        else
       	 noh->simb_ex = 'O';

        break;
    }
}

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
void revelarTab(coord* tabP){

	coord* noP = tabP;
	
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

//Para testes
int main(){
	
	int pontP = 0, pontB = 0, ver = 0;
	coord* ant = NULL;
	char aaaa[100];
	coord *tabP = NULL; 
	coord *tabB = NULL;
	iniciarTabuleiro(&tabP, &tabB);
	PreencherTabuleiro(tabP);
	revelarTab(tabP);
	sleep(1);
	PreencherTabuleiro(tabB);
	printarTabuleiro(tabP, tabB);
	for(;;){
		//input(tabP, tabB, &pontP, &pontB, &ver);
		jogadaBot(tabP, tabB, &ver, &ant, &pontP, &pontB);
		printf("Pontuação: Jogador - %d   Computador - %d\n", pontP, pontB);
		printarTabuleiro(tabP, tabB);
		scanf("%s", aaaa);
	}
}


