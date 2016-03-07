#ifndef __UTIL__
#define __UTIL__

#include <stdlib.h>
#include <stdio.h>
#include "ez-draw.h"

//Paramètres initiaux
#define FIRST_X 200
#define WIDTH_MAIN 800
#define HEIGHT_MAIN 480

//Définition des nouveau types
typedef struct EPOINT EPOINT; 

//COMMENT
struct EPOINT {
  double x;
  double y;
  struct EPOINT * next;
};

//COMMENT
typedef EPOINT * PLISTE;

//Type 'bool' où false = 0 et true = 1
typedef enum {
  false, true
} bool;

//COMMENT
typedef enum {
	PIXMAP, PPM
} svmode;

//COMMENT
typedef struct {
  PLISTE list;
  PLISTE list_zoom;
  int n;
  int configure_count;
  double c;
  int width, height;
  svmode mode;
  char *save_file;
  bool zooming;
} Win_Data;

/*
 * Initialisation avec un point
 * INPUT: coordonnees du point
 * OUTPUT: pointeur sur liste creee
 */
PLISTE init_liste(double xx, double yy);

/*
 * Insere un point apres element elt 
 * INPUT: ptr sur element avant insertion, coordonnees du nouveau point
 * OUTPUT: ptr sur element ajoute
 */
EPOINT * insert_after(EPOINT * elt, double xx, double yy);

/*
 * Supprime un point de la liste apres element elt 
 * INPUT: ptr sur element avant suppression
 * OUTPUT: ptr sur element courant avant suppression
 */
EPOINT * remove_after(EPOINT * elt);

/*
 * Ecriture fichier des points de la liste.
 * INPUT: nom fichier d'ecriture, liste a ecrire
 * OUTPUT: --
 */ 
void save_pixmap(char * nf, PLISTE lp, int width, int height);

/*
 * Lecture d'une liste de points depuis fichier de nom nf
 * INPUT: nom fichier
 * OUTPUT: liste de points lus sur le fichier en entree.
 */  
PLISTE load_pixmap(char * nf, int *width, int *height);

/*
 * Affichage d'une liste de points dans la console
 * INPUT: liste chaînée
 * OUTPUT: --
 */
void afficher_liste(PLISTE l);

/*
 * Dessine le flocon dans la fenêtre
 * INPUT: fenetre concernée, épaisseur du trait, liste de points, couleur
 * OUTPUT: --
 */
void dessiner_liste(Ez_window window, int thickness, PLISTE list, Ez_uint32 color);

/*
 * Modifie la liste de point pour l'adapte à la nouvelle taille de
 * la fenêtre
 * INPUT:  
 * OUTPUT: --
 */
PLISTE redimensionner_flocon(PLISTE pl, int width, int height, int *old_width, int *old_height);

/*
 * Sauvegarde d'une liste de points dans un fichier
 * INPUT: 
 * OUTPUT: --
 */
void save(PLISTE lp, char *nf, svmode mode, int width, int height);

/*
 * Zoom sur un plan de la fenêtre
 * INPUT: 
 * OUTPUT: --
 */
PLISTE zoom(int clic_x, int clic_y, int zoom_factor, Win_Data win1_data);

/*
 * Translate la forme géométrique dans l'espace
 * INPUT: 
 * OUTPUT: --
 */
PLISTE offset(PLISTE lp, double deltax, double deltay);

/*
 * Renvoie la sous-liste incluse 
 * INPUT: 
 * OUTPUT: --
 */
PLISTE list_from_frame(PLISTE lp, double x1, double y1, double x2, double y2);
#endif
