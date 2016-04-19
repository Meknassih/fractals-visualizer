#include <stdlib.h>
#include "headers/ez-draw.h"
#include "headers/ez-image.h"
#include "headers/util.h"
#include "headers/generate.h"
#include "headers/interface.h"
#include "headers/events.h"



// Alloue de la mémoire pour un tableau 'l' ligne, 4 colonnes
int ** createTable(int l){
  int **tableau = (int **)malloc(sizeof(int*)*l);
  int *tableau2 = (int *)malloc(sizeof(int)*4*l);
  int i;
  for (i=0 ; i<l ; i++)  tableau[i] = &tableau2[i*4];
  return tableau;
}

Ez_image * init_background(){
  Ez_image *image_background;
  image_background = ez_image_create(WIDTH_UI, HEIGHT_UI);
  image_background = ez_image_load("img/background_win.png");
  if(image_background==NULL) printf("Background Null\n");
  else printf("Image_background = %p \n", image_background);
  return image_background;
}

void init_images_buttons(Win_Data *win1_data){
	
  /* FIRST BUTTONS
   * */
   	  
  //Koch button
  win1_data->image_button[0] = ez_image_create(80,35);
  win1_data->image_button[0] = ez_image_load("img/0.png");
  win1_data->image_active_button[0] = ez_image_create(80,35);
  win1_data->image_active_button[0] = ez_image_load("img/15.png");
  //Mandelbrot button
  win1_data->image_button[1] = ez_image_create(80,35);
  win1_data->image_button[1] = ez_image_load("img/1.png");
  win1_data->image_active_button[1] = ez_image_create(80,35);
  win1_data->image_active_button[1] = ez_image_load("img/16.png");
  //Mandelbrot button
  win1_data->image_button[2] = ez_image_create(80,35);
  win1_data->image_button[2] = ez_image_load("img/2.png");
  win1_data->image_active_button[2] = ez_image_create(80,35);
  win1_data->image_active_button[2] = ez_image_load("img/17.png");
  
  /* SECOND BUTTONS
   * */

  // Circulaire
  win1_data->image_button[3] = ez_image_create(80,35);
  win1_data->image_button[3] = ez_image_load("img/3.png");
  win1_data->image_active_button[3] = ez_image_create(80,35);
  win1_data->image_active_button[3] = ez_image_load("img/18.png");
  // FINI
  win1_data->image_button[4] = ez_image_create(80,35);
  win1_data->image_button[4] = ez_image_load("img/4.png");
  win1_data->image_active_button[4] = ez_image_create(80,35);
  win1_data->image_active_button[4] = ez_image_load("img/19.png");
  // Superposition
  win1_data->image_button[5] = ez_image_create(80,35);
  win1_data->image_button[5] = ez_image_load("img/5.png");
  win1_data->image_active_button[5] = ez_image_create(80,35);
  win1_data->image_active_button[5] = ez_image_load("img/20.png");
  // Stoping animation
  win1_data->image_button[6] = ez_image_create(240,35);
  win1_data->image_button[6] = ez_image_load("img/6.png");
  win1_data->image_active_button[6] = ez_image_create(240,35);
  win1_data->image_active_button[6] = ez_image_load("img/21.png");
	
  /* ZOOM BUTTONS
   * */
   
  win1_data->image_button[7] = ez_image_create(40,33);
  win1_data->image_button[7] = ez_image_load("img/7.png");
  win1_data->image_active_button[7] = ez_image_create(40,33);
  win1_data->image_active_button[7] = ez_image_load("img/22.png");
  win1_data->image_button[8] = ez_image_create(40,33);
  win1_data->image_button[8] = ez_image_load("img/8.png");
  win1_data->image_active_button[8] = ez_image_create(40,33);
  win1_data->image_active_button[8] = ez_image_load("img/23.png");
  win1_data->image_button[9] = ez_image_create(40,33);
  win1_data->image_button[9] = ez_image_load("img/9.png");
  win1_data->image_active_button[9] = ez_image_create(40,33);
  win1_data->image_active_button[9] = ez_image_load("img/24.png");
  win1_data->image_button[10] = ez_image_create(40,33);
  win1_data->image_button[10] = ez_image_load("img/10.png");
  win1_data->image_active_button[10] = ez_image_create(40,33);
  win1_data->image_active_button[10] = ez_image_load("img/25.png");
  
  
  // check box buttons images 
  win1_data->image_button[11] = ez_image_create(24,24);
  win1_data->image_button[11] = ez_image_load("img/11.png");
  win1_data->image_active_button[11] = ez_image_create(24,24);
  win1_data->image_active_button[11] = ez_image_load("img/26.png");
  win1_data->image_button[12] = ez_image_create(24,24);
  win1_data->image_button[12] = ez_image_load("img/12.png");
  win1_data->image_active_button[12] = ez_image_create(24,24);
  win1_data->image_active_button[12] = ez_image_load("img/27.png");
	
  // save & load buttons :
  win1_data->image_button[13] = ez_image_create(120,35);
  win1_data->image_button[13] = ez_image_load("img/13.png");
  win1_data->image_active_button[13] = ez_image_create(120,35);
  win1_data->image_active_button[13] = ez_image_load("img/28.png");
  win1_data->image_button[14] = ez_image_create(120,35);
  win1_data->image_button[14] = ez_image_load("img/14.png");
  win1_data->image_active_button[14] = ez_image_create(120,35);
  win1_data->image_active_button[14] = ez_image_load("img/29.png");
  
  // check box color mandelbrot
  win1_data->image_button[15] = ez_image_create(24,24);
  win1_data->image_button[15] = ez_image_load("img/55.png");
  win1_data->image_active_button[15] = ez_image_create(24,24);
  win1_data->image_active_button[15] = ez_image_load("img/56.png");
  
  // cases transparentes pour la saisie de valeurs
  win1_data->image_button[16] = ez_image_create(30,15);
  ez_image_set_alpha(win1_data->image_button[16], 1);
  ez_image_fill_rgba(win1_data->image_button[16], 255, 255, 255, 0);
  win1_data->image_active_button[16] = ez_image_create(30,15);
  ez_image_set_alpha(win1_data->image_button[16], 1);
  ez_image_fill_rgba(win1_data->image_active_button[16], 255, 255, 255, 0);
  
  
  win1_data->image_button[17] = ez_image_create(30,15);
  ez_image_set_alpha(win1_data->image_button[17], 1);
  ez_image_fill_rgba(win1_data->image_button[17], 255, 255, 255, 0);
  win1_data->image_active_button[17] = ez_image_create(30,15);
  ez_image_set_alpha(win1_data->image_active_button[17], 1);
  ez_image_fill_rgba(win1_data->image_active_button[17], 255, 255, 255, 0);

  
  win1_data->image_button[18] = ez_image_create(30,15);
  ez_image_set_alpha(win1_data->image_button[18], 1);
  ez_image_fill_rgba(win1_data->image_button[18], 255, 255, 255, 0);
  win1_data->image_active_button[18] = ez_image_create(30,15);
  ez_image_set_alpha(win1_data->image_active_button[18], 1);
  ez_image_fill_rgba(win1_data->image_active_button[18], 255, 255, 255, 0);
  
  win1_data->image_button[19] = ez_image_create(55,15);
  ez_image_set_alpha(win1_data->image_button[19], 1);
  ez_image_fill_rgba(win1_data->image_button[19], 255, 255, 255, 0);
  win1_data->image_active_button[19] = ez_image_create(55,15);
  ez_image_set_alpha(win1_data->image_active_button[19], 1);
  ez_image_fill_rgba(win1_data->image_active_button[19], 255, 255, 255, 0);
  
  win1_data->image_button[20] = ez_image_create(55,15);
  ez_image_set_alpha(win1_data->image_button[20], 1);
  ez_image_fill_rgba(win1_data->image_button[20], 255, 255, 255, 0);
  win1_data->image_active_button[20] = ez_image_create(55,15);
  ez_image_set_alpha(win1_data->image_active_button[20], 1);
  ez_image_fill_rgba(win1_data->image_active_button[20], 255, 255, 255, 0);
}

void init_buttons(Win_Data *win1_data){
  int i;
  win1_data->bptab = createTable(21);
  win1_data->count_buttons = 0;
  win1_data->active_button = malloc(sizeof(int)*(21));
  for(i=0; i<21; i++) win1_data->active_button[i] = 0;
  win1_data->active_button[0] = 1; // Koch par défaut
  win1_data->active_button[11] = 1; // Pix par défaut
  win1_data->active_button[7] = 1; // Zoom *4 par défaut
  
  
  create_buttons(&win1_data->count_buttons,  win1_data->bptab, 3,  80, 35, 10, 25);
  create_buttons(&win1_data->count_buttons,  win1_data->bptab, 3,  80, 35, 10, 90);
  create_buttons(&win1_data->count_buttons,  win1_data->bptab, 1, 240, 35, 10, 125);
	
  // zoom buttons 
  create_buttons(&win1_data->count_buttons,  win1_data->bptab, 1, 40, 33, 260, 25);
  create_buttons(&win1_data->count_buttons,  win1_data->bptab, 1, 40, 33, 260, 26+33);
  create_buttons(&win1_data->count_buttons,  win1_data->bptab, 1, 40, 33, 260, 26+33+33);
  create_buttons(&win1_data->count_buttons,  win1_data->bptab, 1, 40, 33, 260, 127);
  // check box sauvegard
  create_buttons(&win1_data->count_buttons,  win1_data->bptab, 1, 24, 24, 130, 414);
  create_buttons(&win1_data->count_buttons,  win1_data->bptab, 1, 24, 24, 130, 440);
  // button save et load
  create_buttons(&win1_data->count_buttons,  win1_data->bptab, 2, 120, 35, 40, 480);
  // check box color mandelbrot
  create_buttons(&win1_data->count_buttons,  win1_data->bptab, 1, 24, 24, 158, 294);

  // bouton saisi valeurs paramétre koch
  create_buttons(&win1_data->count_buttons,  win1_data->bptab, 1, 30, 15, 230, 197);
  create_buttons(&win1_data->count_buttons,  win1_data->bptab, 1, 30, 15, 230, 217);
  create_buttons(&win1_data->count_buttons,  win1_data->bptab, 1, 30, 15, 230, 237);
  // boutons saisi valeurs paramétre julia
  create_buttons(&win1_data->count_buttons,  win1_data->bptab, 1, 55, 15, 230, 357);
  create_buttons(&win1_data->count_buttons,  win1_data->bptab, 1, 55, 15, 230, 377); 

}

/* Génére les cordonnées du ( point en haut à droite et celui d'en bas à  
 * gauche) et les mets dans un tableau de (l) lignes et 4 colonnes (bptab[][]) 
 */
void create_buttons(int *count_buttons, int **bptab, int nbr_buttons, int largeur_button, int hauteur_button, int x, int y){
  int *tx, *ty, i;
  int count=2;
  int j=0;

  tx = malloc(sizeof(int)*(nbr_buttons*2));
  ty = malloc(sizeof(int)*(nbr_buttons*2));
	
  tx[0] = x; 
  ty[0] = y;
  tx[1] = tx[0] + largeur_button; 
  ty[1] = ty[0] + hauteur_button;
	
  if(nbr_buttons>1) {	
    while(count/2 < nbr_buttons) {
      tx[count]= tx[count-1];
      ty[count]= ty[0];
      tx[count+1]= tx[count] + largeur_button;
      ty[count+1]= ty[1];
      count += 2;
    }
  }

  if (tx[0] > WIDTH_UI || ty[0] > HEIGHT_UI || tx[count-1] > WIDTH_UI || ty[count-1] > HEIGHT_UI) {
    printf("Echec de création, l'un des boutons suivant dépasse les bords de la fenêtre :\n	-Premier boutton : ([%d],[%d]) OR\n	-Deuxieme boutton: ([%d],[%d])\n", tx[0], ty[0], tx[count-1], ty[count-1]);
  } else {
    for ( i = *count_buttons; i< *count_buttons + nbr_buttons; i++ ) {
      bptab[i][0] = tx[j*2];
      bptab[i][1] = ty[j*2];
      bptab[i][2] = tx[(j*2)+1];
      bptab[i][3] = ty[(j*2)+1];
      j++;
    }
    *count_buttons += nbr_buttons;
  }

}

/*	Dessine tous les bouttons générer par create_buttons
 *	Et vérifie si un boutton est activé au tableau active_button[i]
 * */
void draw_buttons(Ez_window ui_win	, Ez_window drawing_win){
  Win_Data *win1_data = ez_get_data(drawing_win);
  int i;
  for(i=0; i < win1_data->count_buttons; i++) {
    if(win1_data->active_button[i]){
      ez_image_paint(ui_win, win1_data->image_active_button[i], win1_data->bptab[i][0], win1_data->bptab[i][1]);
    } else {
      ez_image_paint(ui_win, win1_data->image_button[i], win1_data->bptab[i][0], win1_data->bptab[i][1]);
    }
  }
}

/* Dessine tous les textes qui doivent se trouver dans le menu 
 * interface graphique                                        */
void draw_text(Ez_window ui_win, Ez_window drawing_win) {
  Win_Data *win1_data = ez_get_data(drawing_win);
  
  ez_set_nfont(0);
  ez_set_color(ez_blue);
  ez_draw_text (ui_win, EZ_TL, 10, 10, "Choix de fractales");
  ez_draw_text (ui_win, EZ_TL, 260, 10, "Zoom");
  ez_draw_text (ui_win, EZ_TL, 10, 75, "Choix animations (Koch seulement)");
  ez_draw_text (ui_win, EZ_TL, 10, 180, "Parametre du flocon de koch");
  ez_draw_text (ui_win, EZ_TL, 10, 260, "Parametre de Mandelbrot");
  ez_draw_text (ui_win, EZ_TL, 10, 320, "Parametre de Julia");
  ez_draw_text (ui_win, EZ_TL, 10, 400, "Parametre de sauvegarde");
  // Paramètres Koch
  ez_set_color(ez_black);
  ez_draw_text (ui_win, EZ_TL, 30, 200, "Nombre d'iteration (n)         :");
  ez_draw_text (ui_win, EZ_TL, 235, 200, "%d", win1_data->n);
  ez_draw_rectangle (ui_win, 230,197,260,212);
  
  ez_draw_text (ui_win, EZ_TL, 30, 220, "Taille du segement             :");
  ez_draw_text (ui_win, EZ_TL, 235, 220, "%.0lf", win1_data->c);
  ez_draw_rectangle (ui_win, 230,217, 260,232); 
  ez_draw_text (ui_win, EZ_TL, 265, 220, "pixel");
  
  ez_draw_text (ui_win, EZ_TL, 30, 240, "Delais entre 2 flocons animes  :");
  ez_draw_text (ui_win, EZ_TL, 235, 240, "%d", win1_data->delay_anim);
  ez_draw_rectangle (ui_win, 230,237, 260,252);
  ez_draw_text (ui_win, EZ_TL, 265, 240, "ms");
  
  // Parametres mandelbrot
  ez_draw_text (ui_win, EZ_TL, 30, 280, "Reel(z0) = 0  & Imaginaire(z0) = 0");
  ez_draw_text (ui_win, EZ_TL, 30, 300, "Couleur Mandelbrot :");
  // Paramatres Julia
  ez_draw_text (ui_win, EZ_TL, 30, 340, "Le comlexe initial C");
  
  ez_draw_text (ui_win, EZ_TL, 40, 360, "reel(C)       :");
  ez_draw_text (ui_win, EZ_TL, 235, 360, "%.5lf", (double)(win1_data->z0_c).reel);
  ez_draw_rectangle (ui_win, 230,357, 285,372);
  
  ez_draw_text (ui_win, EZ_TL, 40, 380, "imaginaire(C) :");
  ez_draw_text (ui_win, EZ_TL, 235, 380, "%.5lf", (double)(win1_data->z0_c).imaginaire);
  ez_draw_rectangle (ui_win, 230,377, 285, 392);
  

  // Parametre de sauvegarde
  ez_draw_text (ui_win, EZ_TL, 30, 420, "Liste pixel  :");
  ez_draw_text (ui_win, EZ_TL, 30, 445, "PPM          :");
}

/*	Récupérer les cordonnes du clique souris
 *	Et envoie l'ID du point ou l'utilisateur à cliquer
 * */
button get_button_id(int **bptab, int count_buttons, int mx, int my){
  int i;
  
  for(i=0; i < count_buttons; i++) {
    if(mx >= bptab[i][0] && my >= bptab[i][1] && mx <= bptab[i][2] && my <= bptab[i][3]) {
      printf("Ta cliqué sur le bouton numéro %d\n", i); //DEBUG
      break;
    } else if (i == count_buttons-1) {
      printf("Tu n'as pas cliqué sur un bouton là\n"); //DEBUG
      return -1;
    }
  }
  
  return (button) i;
}

/* Exécute une action dépendant du boutton cliqué par l'utilisateur
 * TODO: on ne devrait pas passer la window mais que Win_data      */
 
void execute_button_press(Ez_window drawing_win, button id_button){
  Win_Data *win1_data = ez_get_data(drawing_win);
  switch(id_button) {
    // Choix fractales
  case B_KOCH:
    win1_data->active_button[B_MANDELBROT]  = 0;
    win1_data->active_button[B_JULIA] 		= 0;
    win1_data->active_button[B_KOCH] 		= 1;
    win1_data->mode = PIXMAP;
    win1_data->active_button[B_PPM] = 0;
    win1_data->active_button[B_PIXMAP] = 1;
    win1_data->list = koch(drawing_window, win1_data->n , win1_data->c);
    ez_send_expose(drawing_window);
    break;
  case B_MANDELBROT:
    win1_data->active_button[B_KOCH] 		= 0;
    win1_data->active_button[B_JULIA] 		= 0;
    win1_data->active_button[B_MANDELBROT]  = 1;
    win1_data->mode = PPM;
    win1_data->active_button[B_PPM] = 1;
    win1_data->active_button[B_PIXMAP] = 0;
    /* Apropos des valeurs xmin xmax ymin ymax qui permette la convertion en plan complexes
     * Il sont égals à (-1.25,1.25,-1.25,1.25) pour JULIA
     * et (-2.0,2.0,-1.25,1.25) pour Manlbrot 
     * */
    if(win1_data->mandelbrot == NULL)
		win1_data->mandelbrot = generate_mandelbrot_julia(win1_data->z0,WIDTH_MAIN,HEIGHT_MAIN,-2.0,2.0,-1.25,1.25,false,win1_data->is_mandel_color);
    ez_send_expose(drawing_window);
    break;
  case B_JULIA:
    win1_data->active_button[B_KOCH] 		= 0;
    win1_data->active_button[B_MANDELBROT]  = 0;
    win1_data->active_button[B_JULIA] 		= 1;
    win1_data->mode = PPM;
    win1_data->active_button[B_PPM] = 1;
    win1_data->active_button[B_PIXMAP] = 0;
	if(win1_data->julia == NULL)
		win1_data->julia = generate_mandelbrot_julia(win1_data->z0_c,WIDTH_MAIN,HEIGHT_MAIN,-1.25,1.25,-1.25,1.25,true,true);
    ez_send_expose(drawing_window);
    break;
    		
    // Choix animations
  case B_ANIME1:
	win1_data->active_button[B_ANIME2] = 0;
	win1_data->active_button[B_STOPANIM] = 0;
	printf("simultané \n");
	win1_data->mode_anim = SIMULTANE;
	ez_start_timer(drawing_window, -1); //Supprime le timer

	win1_data->active_button[B_ANIME1] = 1;
	ez_send_expose(drawing_window); //Force à redessiner toutes les formes
    break;
  case B_ANIME2:
    win1_data->active_button[B_ANIME1] = 0;
    win1_data->active_button[B_STOPANIM] = 0;
	win1_data->mode_anim = SEQUENTIEL;
	win1_data->step_anim = 0; //Remet l'animation à 0
    ez_start_timer(drawing_window, win1_data->delay_anim); //Met en place le timer
    
    win1_data->active_button[B_ANIME2] = 1;
	ez_send_expose(drawing_window); //Force à redessiner toutes les formes

    break;
  case B_ANIME3:
    if (win1_data->active_button[B_ANIME3]) win1_data->active_button[B_ANIME3] = 0;
    else win1_data->active_button[B_ANIME3] = 1;
    break;
  case B_STOPANIM:
    if (win1_data->active_button[B_STOPANIM]) win1_data->active_button[B_STOPANIM] = 0;
    else win1_data->active_button[B_STOPANIM] = 1;
    break;
		
    // Choix zooms
  case B_ZOOM4:
    win1_data->active_button[B_ZOOM4]  = 1;
    win1_data->active_button[B_ZOOM6]  = 0;
    win1_data->active_button[B_ZOOM8]  = 0;
    win1_data->active_button[B_ZOOM10] = 0;
    win1_data->factor = 4;
    break;
  case B_ZOOM6:
    win1_data->active_button[B_ZOOM4]  = 0;
    win1_data->active_button[B_ZOOM6]  = 1;
    win1_data->active_button[B_ZOOM8]  = 0;
    win1_data->active_button[B_ZOOM10] = 0;
    win1_data->factor = 6;
    break;
  case B_ZOOM8:
    win1_data->active_button[B_ZOOM4]  = 0;
    win1_data->active_button[B_ZOOM6]  = 0;
    win1_data->active_button[B_ZOOM8]  = 1;
    win1_data->active_button[B_ZOOM10] = 0;
    win1_data->factor = 8;
    break;
  case B_ZOOM10:
    win1_data->active_button[B_ZOOM4]  = 0;
    win1_data->active_button[B_ZOOM6]  = 0;
    win1_data->active_button[B_ZOOM8]  = 0;
    win1_data->active_button[B_ZOOM10] = 1;
    win1_data->factor = 10;
    break;
    // Check box, active les couleurs mandelbrot
  case B_ISMAND_COLOR:
    if (win1_data->active_button[B_ISMAND_COLOR]) {
		win1_data->active_button[B_ISMAND_COLOR] = 0;
		win1_data->is_mandel_color = false;
	} else {
		win1_data->active_button[B_ISMAND_COLOR] = 1;
		win1_data->is_mandel_color = true;
	}
    win1_data->mandelbrot = generate_mandelbrot_julia(win1_data->z0,WIDTH_MAIN,HEIGHT_MAIN,-2.0,2.0,-1.25,1.25,0,win1_data->is_mandel_color);
	ez_send_expose(drawing_window);	
    break;
  // Cases de saisie
  case B_N:
	win1_data->active_button[B_N] = 1;
	win1_data->active_button[B_C] = 0;
	win1_data->active_button[B_DELAY] = 0;
	win1_data->active_button[B_Z0C_REEL] = 0;
	win1_data->active_button[B_Z0C_IMAGINAIRE] = 0;
    win1_data->active_button[B_SAVE]  = 0;
	win1_data->active_button[B_LOAD]  = 0;
	ez_window_show(popup_window, true);

    break;
  case B_C:
	win1_data->active_button[B_N] = 0;
	win1_data->active_button[B_C] = 1;
	win1_data->active_button[B_DELAY] = 0;
	win1_data->active_button[B_Z0C_REEL] = 0;
	win1_data->active_button[B_Z0C_IMAGINAIRE] = 0;
    win1_data->active_button[B_SAVE]  = 0;
	win1_data->active_button[B_LOAD]  = 0;
	ez_window_show(popup_window, true);
    break;
  case B_DELAY:
	win1_data->active_button[B_N] = 0;
	win1_data->active_button[B_C] = 0;
	win1_data->active_button[B_DELAY] = 1;
	win1_data->active_button[B_Z0C_REEL] = 0;
	win1_data->active_button[B_Z0C_IMAGINAIRE] = 0;
    win1_data->active_button[B_SAVE]  = 0;
	win1_data->active_button[B_LOAD]  = 0;
	ez_window_show(popup_window, true);
    break;
  case B_Z0C_REEL:
	win1_data->active_button[B_N] = 0;
	win1_data->active_button[B_C] = 0;
	win1_data->active_button[B_DELAY] = 0;
	win1_data->active_button[B_Z0C_REEL] = 1;
	win1_data->active_button[B_Z0C_IMAGINAIRE] = 0;
    win1_data->active_button[B_SAVE]  = 0;
	win1_data->active_button[B_LOAD]  = 0;
	ez_window_show(popup_window, true);
    break;
   case B_Z0C_IMAGINAIRE:
	win1_data->active_button[B_N] = 0;
	win1_data->active_button[B_C] = 0;
	win1_data->active_button[B_DELAY] = 0;
	win1_data->active_button[B_Z0C_REEL] = 0;
	win1_data->active_button[B_Z0C_IMAGINAIRE] = 1;
    win1_data->active_button[B_SAVE]  = 0;
	win1_data->active_button[B_LOAD]  = 0;
	ez_window_show(popup_window, true);
    break;
    // Choix du type de sauvegarde et chargement
  case B_PIXMAP:

    break;
  case B_PPM:

    break;
			
    // Boutton sauvegarde
  case B_SAVE:
	win1_data->active_button[B_N] = 0;
	win1_data->active_button[B_C] = 0;
	win1_data->active_button[B_DELAY] = 0;
	win1_data->active_button[B_Z0C_REEL] = 0;
	win1_data->active_button[B_Z0C_IMAGINAIRE] = 0;
    win1_data->active_button[B_SAVE]  = 1;
	win1_data->active_button[B_LOAD]  = 0;
	ez_window_show(popup_window, true);
    break;
		
    // Boutton Chargement
  case B_LOAD:
  	win1_data->active_button[B_N] = 0;
	win1_data->active_button[B_C] = 0;
	win1_data->active_button[B_DELAY] = 0;
	win1_data->active_button[B_Z0C_REEL] = 0;
	win1_data->active_button[B_Z0C_IMAGINAIRE] = 0;
	win1_data->active_button[B_SAVE]  = 0;
	win1_data->active_button[B_LOAD]  = 1;
	ez_window_show(popup_window, true);
    break;

  default:
		
    break;
  }
  ez_set_data(drawing_win, win1_data); //renvoie les données modifier à notre fenêtre
}

int text_input(Ez_event *ev, char *s) {
  int i;

  switch (ev->key_sym) {

  case XK_BackSpace : //Effacer
    i = strlen (s);
    if (i == 0) break;
    s[i-1] = 0;
    return 1;

  case XK_Return : //Valider
    return 2;
    
  default : //Nouveau caractère
    if (ev->key_count != 1) break;
    i = strlen (s);
    if (i >= BUF_MAX-1) break;
    s[i] = ev->key_string[0]; s[i+1] = 0; //TODO: n'accepte que les chiffres
    return 1;
  }
  return 0;
}

void text_display(Ez_window win, int x, int y, char *s1, char *s2) {
  Win_Data *win1_data = ez_get_data(drawing_window);
  ez_set_color (ez_black);
  ez_draw_text (win, EZ_TL, x, y, "%s|", s1);

  if (strcmp (win1_data->buf, "") != 0) {
    ez_set_color (ez_blue);
    ez_draw_text (ui_window, EZ_TL, 20, 530	, "You have validated: %s", win1_data->buf);
  }
}
