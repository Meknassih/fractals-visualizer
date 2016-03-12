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

main.o:
	$(CC) $(CFLAGS) main.c

generate.o:
	$(CC) $(CFLAGS) generate.c $(MFLAGS)

util.o:
	$(CC) $(CFLAGS) util.c $(MFLAGS)

ez-draw.o:
	$(CC) $(CFLAGS) ez-draw.c $(GFLAGS)

clean: #Nettoie les fichier objets, temporaires, de restauration et l'exec
	rm *.o *~ *# projet 
