#Compiler
CC=gcc
#Common compiling flags
CFLAGS=-c -Wall
#Graphic libraries
GFLAGS=-lX11 -lXext
#Math library
MFLAGS=-lm

all: projet

projet: ez-draw.o ez-image.o interface.o generate.o util.o events.o main.o
	$(CC) ez-draw.o ez-image.o interface.o generate.o util.o events.o main.o -o projet $(GFLAGS) $(MFLAGS)

ez-draw.o: ez-draw.c headers/ez-draw.h
	$(CC) $(CFLAGS) ez-draw.c $(GFLAGS)

ez-image.o: ez-image.c headers/ez-image.h
	$(CC) $(CFLAGS) ez-image.c $(GFLAGS)

interface.o: interface.c headers/interface.h
	$(CC) $(CFLAGS) interface.c $(MFLAGS)

util.o: util.c headers/util.h
	$(CC) $(CFLAGS) util.c $(MFLAGS)

generate.o: generate.c headers/generate.h
	$(CC) $(CFLAGS) generate.c $(MFLAGS)

events.o: events.c headers/events.h
	$(CC) $(CFLAGS) events.c $(MFLAGS)

main.o: main.c
	$(CC) $(CFLAGS) main.c

clean: #Nettoie les fichier objets, temporaires, de restauration et l'exec
	rm *.o *~ *# projet 
