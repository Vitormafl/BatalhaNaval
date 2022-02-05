#ifndef api_h
#define api_h

// Coordenada player
	typedef struct _coord{
	
		struct _coord *n;
		struct _coord *s;
		struct _coord *e;
		struct _coord *w;
		char simb;
		char type;
		int ori;	//0 = Horizontal | 1 = Vertical
	
	} coord;

// Coordenada bot
	typedef struct _coordb{
	
		struct _coordb *n;
		struct _coordb *s;
		struct _coordb *e;
		struct _coordb *w;
		char simb;
		char simb_ex;
		char type;
		int ori; 	//0 = Horizontal | 1 = Vertical
	
	} coordB;

void iniciarTabuleiro(coord**, coordB**);

void printarTabuleiro(coord*, coordB*);

void PreencherTabuleiro(coord**);

int input(coordB**);

void reset(coord*, coordB*);

void jogada(coord*,int, coord**);

#endif
