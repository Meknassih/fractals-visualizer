#ifndef __UTIL__
#define __UTIL__

#include <stdlib.h>
#include <stdio.h>
#include "ez-draw.h"
#include "ez-image.h"
#include "cplx.h"

//Paramètres initiaux
#define FIRST_X 200
#define WIDTH_MAIN 800
#define HEIGHT_MAIN 600
#define MAX_ZOOM_PARTS 100
#define FRAME_MARGIN 15
#define FACTOR_INIT 4
#define ORDRE_INIT 2
#define TAILLE_INIT 300
#define BUF_MAX 9

extern Ez_window drawing_window, ui_window, popup_window;

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

typedef enum {
  SIMULTANE,
  SEQUENTIEL
} Expose_Mode;

/* **************************************************************** */
/* ************************* Période 2 **************************** */
/* **************************************************************** */
#define WIDTH_POPUP 320
#define HEIGHT_POPUP 60
#define MAX_ITER 100
#define L_CONVERGENCE 4

struct Pixel {
	Ez_uint8 r;
	Ez_uint8 g;
	Ez_uint8 b;
};

typedef struct Pixel Pixel;

struct Image {
	Pixel ***plan;
	int width;
	int height;
};

typedef struct Image Image;

/* **************************************************************** */
/* ************************ Fin Période 2 ************************* */
/* **************************************************************** */

//COMMENT
typedef struct {
  PLISTE list, zoom_list[MAX_ZOOM_PARTS]; //Liste de points pour la fractale + portion zoomée
  int n; //Ordre de la fractale
  int configure_count; //Nombre de ConfigureNotify déclenchés
  double c; //Largeur du premier segment (koch)
  PLISTE list_anim[10];
  Expose_Mode mode_anim;
  int delay_anim; //ms entre chaque flocon
  int step_anim;
  int width, height; //Dimensions de la fenêtre à tout moment
  svmode mode; //Mode de sauvegarde (PIX, PPM)
  char *save_file; //Nom du fichier de sauvegarde sans ext
  char *temp_buf, *buf;
  bool zooming;
  int zoom_part_count;
  int factor;
  int x1_frame, x2_frame, y1_frame, y2_frame;
  Ez_image *image_background; // image du background
  Ez_image *image_button[21]; // tableau d'images de tous les bouttons
  Ez_image *image_active_button[21]; // Tableau d'images des bouttons actives
  int **bptab; // Tableau regroupant tous les cordonnées des points des bouttons
  int count_buttons; // Nombres de bouttons dans la fênetre
  bool *active_button; // Verifie si le boutton est active ou pas
  Image *mandelbrot; //Matrice de pixels correspondant à l'ensemble de Mandelbrot
  Image *julia; //Matrice de pixels correspondant à l'ensemble de Julia
  Complexe z0_c; // Valeur c pour les différents Julia
  Complexe old_z0_c;
  Complexe z0; // Z0 = 0+0i pour Mandelbrot
  bool is_mandel_color; // Couleur mandelbrot
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
void dessiner_liste(Ez_window window, int thickness, PLISTE list, Ez_uint32 color, bool zoom_mode);

/*
 * Dessine le cadre de portée du zoom (frame) dans la fenêtre
 * INPUT: fenetre concernée, épaisseur du trait, liste de points, couleur
 * OUTPUT: --
 */
void dessiner_frame(Ez_window window, int thickness, Ez_uint32 color);

/*
 * Initialise les paramètres généraux de base (facteur de zoom, taille de
 * la fenêtre, ...)
 * INPUT: --
 * OUTPUT: Structure initialisée partiellement
 */
Win_Data init_general_settings(void);

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
 * Modifie les données en mémoire pour gérer le zoom
 * INPUT: 
 * OUTPUT: faux si aucun point dans la frame
 */
bool zoom(Win_Data *win_data, int mouse_x, int mouse_y);

/*
 * Crée la ou les liste de points sur lesquelles on zoom
 * INPUT: 
 * OUTPUT: --
 */
void init_zoom(Win_Data *win_data);

/*
 * Centre la ou les sous-listes de points concernées
 * INPUT: 
 * OUTPUT: --
 */
void center_points(Win_Data *win_data, int x_offset, int y_offset);

/*
 * Applique le zoom sur la ou les listes de points concernées
 * INPUT: 
 * OUTPUT: --
 */
void expand_points(Win_Data *win_data);

/* **************************************************************** */
/* ************************ Période 2 ***************************** */
/* **************************************************************** */

Pixel* init_pixel(int R, int G, int B);
Image* init_image(int width, int height);
void set_pixel(Image * im, Pixel * p, int lig, int col);
void free_image(Image *im);
void print_mandelbrot_julia(Ez_window window, int thickness, Image *fractale, bool isJulia);
void save_img(Image *img, char *nf);
Image* load_img(char *nf);
void init_active_buttons_zoom_text_entry(Win_Data *win1_data, bool r);
void valid_text_entry(Win_Data *win1_data);

#endif
