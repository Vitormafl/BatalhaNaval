all: jogo

jogo: tabuleiro.o player.o bot.o jogo.o
	gcc tabuleiro.o player.o bot.o jogo.o -o jogo
	make clean

tabuleiro.o: tabuleiro.c
	gcc -c tabuleiro.c

player.o: player.c
	gcc -c player.c

jogo.o: jogo.c
	gcc -c jogo.c

bot.o: bot.c
	gcc -c bot.c

clean:
	rm -f *.o

