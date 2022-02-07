all: main

main: tabuleiro.o player.o bot.o jogo.o main.o
	gcc tabuleiro.o player.o bot.o jogo.o main.o -o main
	make clean

main.o: main.c
	gcc -c main.c

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

