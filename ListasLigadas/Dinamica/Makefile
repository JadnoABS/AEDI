begin: main

main: main.o listaLigDinamica.o
	gcc -o listaLigadaDinamica main.o listaLigDinamica.o

main.o: main.c listaLigDinamica.h
	gcc -c main.c

listaLigDinamica.o: listaLigDinamica.c listaLigDinamica.h
	gcc -c listaLigDinamica.c
