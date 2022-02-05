#ifndef api_h
#define api_h

// Coordenada
	typedef struct _coord{
	
		struct _coord *n;
		struct _coord *s;
		struct _coord *e;
		struct _coord *w;
		char simb;
		/*	'p' - Porta-aviões
			'd' - Destroyer
			'f' - Fragata
			's' - Submarino
			'j' - jangada		*/
		char simb_ex;
		char type;
		int ori; 	//0 = Horizontal | 1 = Vertical
	
	} coord;

void iniciarTabuleiro(coord**, coordB**);

void printarTabuleiro(coord*, coordB*);

void PreencherTabuleiro(coord**);

int input(coordB**);

void reset(coord*, coordB*);

void jogada(coord*,int, coord**);

#endif
