#Compiler
CC=gcc
#Common compiling flags
CFLAGS=-c -Wall
#Graphic libraries
GFLAGS=-lX11 -lXext
#Math library
MFLAGS=-lm

all: projet

projet: main.o generate.o util.o ez-draw.o
	$(CC) ez-draw.o util.o generate.o main.o -o projet $(GFLAGS) $(MFLAGS)

ez-draw.o: ez-draw.c
	$(CC) $(CFLAGS) ez-draw.c $(GFLAGS)

util.o: util.c
	$(CC) $(CFLAGS) util.c $(MFLAGS)

generate.o: generate.c
	$(CC) $(CFLAGS) generate.c $(MFLAGS)

main.o: main.c
	$(CC) $(CFLAGS) main.c

clean: #Nettoie les fichier objets, temporaires, de restauration et l'exec
	rm *.o *~ *# projet 
