#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> //Linux
//#include <dos.h> //Windows
#include "api.h"

int main(){
	
	int iniciar_jogo = 1;
	int pontP = 0, pontB = 0, ver = 0, pontBG = 0, pontPG = 0;
	coord* ant = NULL;
	coord *tabP = NULL; 
	coord *tabB = NULL;
	iniciarTabuleiro(&tabP, &tabB);
	
	while(iniciar_jogo == 1){
		
		PreencherTabuleiro(tabP);
		sleep(1);
		PreencherTabuleiro(tabB);
		revelarTab(tabP);
		printarTabuleiro(tabP, tabB, pontP, pontB);

		while(pontB < 8 && pontP < 8){
			input(tabP, tabB, &pontP, &pontB, &ver);
			jogadaBot(tabP, tabB, &ver, &ant, &pontP, &pontB);
			pontP++;
		}
		if(pontP = 8){
			printf("\nParabéns, você derrotou a melhor máquina de batalha naval!\n");
			pontPG++;
		}
		else{
			printf("Você foi derrotado\n");
			pontBG++;	
		}
		
		printf("\nJogos ganhos:\n\nPlayer: %d      Computador: %d\n", pontPG, pontBG);
		printf("\nDeseja continuar jogando Batalha Naval? \n (1) sim \n\n (Outra tecla) não\n");
		scanf(" %d",&iniciar_jogo);
		if(iniciar_jogo == 1) reset(tabP, tabB, &pontP, &pontP);
	}
}


