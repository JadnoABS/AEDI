begin: main

main: main.o listaDuplamenteLig.o
	gcc -o listaDuplamenteLigada main.o listaDuplamenteLig.o

main.o: main.c listaDuplamenteLig.h
	gcc -c main.c

listaDuplamenteLig.o: listaDuplamenteLig.c listaDuplamenteLig.h
	gcc -c listaDuplamenteLig.c
