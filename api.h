#ifndef api_h
#define api_h

// Coordenada
	typedef struct _coord{
	
		struct _coord *n;
		struct _coord *s;
		struct _coord *e;
		struct _coord *w;
		
		//	Armazena os símbolos das embarcações
		char simb;
		
		//	Símbolo exibido no printarTabuleiro
		char simb_ex;
		
		char type;
		/*	'0' - Água
			'p' - Porta-aviões
			'd' - Destroyer
			'f' - Fragata
			's' - Submarino
			'j' - jangada		*/
		int ori; 	
		//	0 = Horizontal | 1 = Vertical
		int hit;
	
	} coord;

//Funções de jogo.c

	void removerSub(coord*);
	
	void verificarJogada(coord*, coord*, coord*, coord*, int*, int*, int*);

//Funções de tabuleiro.c
	
	void iniciarTabuleiro(coord**, coord**);

	void printarTabuleiro(coord*, coord*, int, int);

	void PreencherTabuleiro(coord*);
	
	void reset(coord*, coord*, int*, int*);
	
	void revelarTab(coord*);

//Função do player.c

	void input(coord*, coord*, int*, int*, int*);

//Função do bot.c

	void jogadaBot(coord*, coord*, int*, coord**, int*, int*);

#endif
