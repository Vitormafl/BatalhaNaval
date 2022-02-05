#endif
#ifndef api_h
#define api_h

// Coordenada
	typedef struct _coord{
	
		struct _coord *n;
		struct _coord *s;
		struct _coord *e;
		struct _coord *w;
		char simb;
		char simb_ex;
		char type;
		/*	'p' - Porta-aviões
			'd' - Destroyer
			'f' - Fragata
			's' - Submarino
			'j' - jangada		*/
		int ori; 	//0 = Horizontal | 1 = Vertical
	
	} coord;

void iniciarTabuleiro(coord**, coord**);

void printarTabuleiro(coord*, coord*);

void PreencherTabuleiro(coord*);

int input(coord*, coord*, int*, int*);

void reset(coord*, coord*);

void jogada(coord*,int, coord**);

void verificarJogada(coord*, coord*, coord*, coord*, int*, int*);

#endif
