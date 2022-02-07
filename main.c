#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> //Linux
//#include <dos.h> //Windows
#include "api.h"

int main(){
	
	int iniciar_jogo = 1;
	int pontP = 0, pontB = 0, ver = 0;
	coord* ant = NULL;
	coord *tabP = NULL; 
	coord *tabB = NULL;
	iniciarTabuleiro(&tabP, &tabB);
		
	while(iniciar_jogo == 1)
		PreencherTabuleiro(tabP);
		sleep(1);
		PreencherTabuleiro(tabB);
		revelarTab(tabP);
		printarTabuleiro(tabP, tabB);
		while(pontB < 8 && pontP < 8){
			input(tabP, tabB, &pontP, &pontB, &ver);
			jogadaBot(tabP, tabB, &ver, &ant, &pontP, &pontB);	
		}
		
		if(pontP = 8){
			printf("Parabéns, você derrotou a melhor máquina de batalha naval!\n");
		}
		else
			printf("Você foi derrotado\n");
		
		printf("Deseja continuar jogando Batalha Naval? \n (1) sim \n (Outra tecla) não\n");
		scanf("%d",&iniciar_jogo);
}


