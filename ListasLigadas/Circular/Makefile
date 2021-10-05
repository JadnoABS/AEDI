begin: main

main: main.o listaLigCircular.o
	gcc -o listaLigadaCircular main.o listaLigCircular.o

main.o: main.c listaLigCircular.h
	gcc -c main.c

listaLigCircular.o: listaLigCircular.c listaLigCircular.h
	gcc -c listaLigCircular.c
