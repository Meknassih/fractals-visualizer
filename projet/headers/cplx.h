#ifndef __CPLXIO__
#define __CPLXIO__

#include <stdio.h>
#include <stdlib.h>

typedef struct { 
  double reel;
  double imaginaire;
} Complexe;

/*
 * Cree un complexe a partir de deux reels.
 * 
 * INPUT: reel partie reelle, reel partie imaginaire
 * OUTPUT: pointeur sur struct Complexe, allocation memoire dans la 
 * fonction
 */ 
Complexe * create_complexe(double r, double i);

/* Le format est la lecture de deux reels de type long, separes
 * par un espace (partie reelle suivie de partie imaginaire).
 * La fonction renvoit un pointeur vers le complexe nouvellement lu.
 * L'affectation memoire se fait dans la fonction.
 * Lecture sur entrée standard (clavier).
 *
 * INPUT: --
 * OUTPUT: pointeur sur nouvelle structure de complexe
 * 
 */

Complexe * read_complexe(void);

/* Ecrit le complexe sans le i, comme deux coordonnees separees par un
 * espace, sur la sortie standard (terminal). 
 * Le format est le meme que pour la lecture (partie reelle puis 
 * imaginaire). 
 * 
 * INPUT: pointeur sur un element de structure de complexe.
 * OUTPUT: --
 * 
 */

void print_complexe (Complexe *cpx);

/* Calcule la somme de deux complexes 
 * Allocation memoire d'un nouveau pointeur.
 * 
 * INPUT: pointeurs vers des complexes (operandes)
 * OUTPUT: pointeur sur resultat, un complexe.
 */
Complexe * add_cplx (Complexe *cpx1, Complexe *cpx2);

/* Calcule la soustraction entre deux complexes z1-z2 
 * Allocation memoire d'un nouveau pointeur.
 * 
 * INPUT: pointeurs vers des complexes (operandes)
 *        entier, si 1 = moins unaire (oppose), si 2 = moins binaire 

 * OUTPUT: pointeur sur resultat, un complexe.
 */
Complexe * moins_cplx (Complexe *cpx1, Complexe *cpx2);

/* Calcule la multiplication entre deux complexes 
 * Allocation memoire d'un nouveau pointeur.
 * 
 * INPUT: pointeurs vers des complexes (operandes)
 * OUTPUT: pointeur sur resultat, un complexe.
 */

Complexe * mul_cplx (Complexe *cpx1, Complexe *cpx2);

/* Calcule le produit d'un complexe et d'un reel
 * Allocation memoire d'un nouveau pointeur.
 * 
 * INPUT: pointeur sur un complexe et un reel (operandes)
 * OUTPUT: pointeur sur resultat, un complexe.
 * Complexe * mul_cplx_reel (Complexe*, double);
 */
 
double abs_cplx (Complexe *cpx);
#endif
