begin: main

main: main.o listaLigEstatica.o
	gcc -o listaLigadaEstatica main.o listaLigEstatica.o

main.o: main.c listaLigEstatica.h
	gcc -c main.c

listaLigEstatica.o: listaLigEstatica.c listaLigEstatica.h
	gcc -c listaLigEstatica.c
