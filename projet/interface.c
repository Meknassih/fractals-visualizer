#include "headers/ez-draw.h"
#include "headers/ez-image.h"
#include "headers/util.h"
#include "headers/generate.h"
#include "headers/interface.h"


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
  if(image_background==NULL) printf("Background Nulllllll\n");
  else printf("Image_background = %p \n", image_background);
  return image_background;
}

void init_images_buttons(Win_Data *win1_data){
	
  //FIRST BUTTONS
  win1_data->image_button[0] = ez_image_create(120,35);
  win1_data->image_button[0] = ez_image_load("img/0.png");
  win1_data->image_active_button[0] = ez_image_create(120,35);
  win1_data->image_active_button[0] = ez_image_load("img/14.png");
  win1_data->image_button[1] = ez_image_create(120,35);
  win1_data->image_button[1] = ez_image_load("img/1.png");
  win1_data->image_active_button[1] = ez_image_create(120,35);
  win1_data->image_active_button[1] = ez_image_load("img/15.png");

  //SECOND BUTTONS
  win1_data->image_button[2] = ez_image_create(80,35);
  win1_data->image_button[2] = ez_image_load("img/2.png");
  win1_data->image_active_button[2] = ez_image_create(80,35);
  win1_data->image_active_button[2] = ez_image_load("img/16.png");
  win1_data->image_button[3] = ez_image_create(80,35);
  win1_data->image_button[3] = ez_image_load("img/3.png");
  win1_data->image_active_button[3] = ez_image_create(80,35);
  win1_data->image_active_button[3] = ez_image_load("img/17.png");
  win1_data->image_button[4] = ez_image_create(80,35);
  win1_data->image_button[4] = ez_image_load("img/4.png");
  win1_data->image_active_button[4] = ez_image_create(80,35);
  win1_data->image_active_button[4] = ez_image_load("img/18.png");
  win1_data->image_button[5] = ez_image_create(240,35);
  win1_data->image_button[5] = ez_image_load("img/5.png");
  win1_data->image_active_button[5] = ez_image_create(240,35);
  win1_data->image_active_button[5] = ez_image_load("img/19.png");
	
  //ZOOM BUTTONS

  win1_data->image_button[6] = ez_image_create(40,33);
  win1_data->image_button[6] = ez_image_load("img/6.png");
  win1_data->image_active_button[6] = ez_image_create(40,33);
  win1_data->image_active_button[6] = ez_image_load("img/20.png");
  win1_data->image_button[7] = ez_image_create(40,33);
  win1_data->image_button[7] = ez_image_load("img/7.png");
  win1_data->image_active_button[7] = ez_image_create(40,33);
  win1_data->image_active_button[7] = ez_image_load("img/21.png");
  win1_data->image_button[8] = ez_image_create(40,33);
  win1_data->image_button[8] = ez_image_load("img/8.png");
  win1_data->image_active_button[8] = ez_image_create(40,33);
  win1_data->image_active_button[8] = ez_image_load("img/22.png");
  win1_data->image_button[9] = ez_image_create(40,33);
  win1_data->image_button[9] = ez_image_load("img/9.png");
  win1_data->image_active_button[9] = ez_image_create(40,33);
  win1_data->image_active_button[9] = ez_image_load("img/23.png");

  // check box buttons images 
  win1_data->image_button[10] = ez_image_create(24,24);
  win1_data->image_button[10] = ez_image_load("img/10.png");
  win1_data->image_active_button[10] = ez_image_create(24,24);
  win1_data->image_active_button[10] = ez_image_load("img/24.png");
  win1_data->image_button[11] = ez_image_create(24,24);
  win1_data->image_button[11] = ez_image_load("img/11.png");
  win1_data->image_active_button[11] = ez_image_create(24,24);
  win1_data->image_active_button[11] = ez_image_load("img/25.png");
	
  // save & load buttons :
  win1_data->image_button[12] = ez_image_create(120,35);
  win1_data->image_button[12] = ez_image_load("img/12.png");
  win1_data->image_active_button[12] = ez_image_create(120,35);
  win1_data->image_active_button[12] = ez_image_load("img/26.png");
  win1_data->image_button[13] = ez_image_create(120,35);
  win1_data->image_button[13] = ez_image_load("img/13.png");
  win1_data->image_active_button[13] = ez_image_create(120,35);
  win1_data->image_active_button[13] = ez_image_load("img/27.png");
}

void init_buttons(Win_Data *win1_data){
  int i;
  win1_data->bptab = createTable(14);
  win1_data->count_buttons = 0;
  win1_data->active_button = malloc(sizeof(int)*(14));
  for(i=0; i<14; i++) win1_data->active_button[i] = 0;
  win1_data->active_button[0] = 1; // Koch par défaut
  win1_data->active_button[10] = 1; // Pix par défaut
  create_buttons(&win1_data->count_buttons,  win1_data->bptab, 2, 120, 35, 10, 25);
  create_buttons(&win1_data->count_buttons,  win1_data->bptab, 3,  80, 35, 10, 90);
  create_buttons(&win1_data->count_buttons,  win1_data->bptab, 1, 240, 35, 10, 125);
	
  // zoom buttons 
  create_buttons(&win1_data->count_buttons,  win1_data->bptab, 1, 40, 33, 260, 25);
  create_buttons(&win1_data->count_buttons,  win1_data->bptab, 1, 40, 33, 260, 26+33);
  create_buttons(&win1_data->count_buttons,  win1_data->bptab, 1, 40, 33, 260, 26+33+33);
  create_buttons(&win1_data->count_buttons,  win1_data->bptab, 1, 40, 33, 260, 127);
  // check box sauvegard
  create_buttons(&win1_data->count_buttons,  win1_data->bptab, 1, 24, 24, 90, 348);
  create_buttons(&win1_data->count_buttons,  win1_data->bptab, 1, 24, 24, 90, 373);
  // button save et load
  create_buttons(&win1_data->count_buttons,  win1_data->bptab, 2, 120, 35, 40, 410);
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
void draw_buttons(Ez_window ui_win, Ez_window drawing_win){
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
  ez_set_color(ez_blue);
  ez_draw_text (ui_win, EZ_TL, 10, 10, "Choix de fractales");
  ez_draw_text (ui_win, EZ_TL, 10, 75, "Choix animations");
  ez_draw_text (ui_win, EZ_TL, 10, 180, "Parametre du flocon de koch");
  ez_draw_text (ui_win, EZ_TL, 10, 290, "Parametre de sauvegarde");
  ez_set_color(ez_black);
  ez_draw_text (ui_win, EZ_TL, 30, 200, "Nombre d'iteration (n)         :");
  ez_draw_line (ui_win, 230,212, 260,212);
  text_display(drawing_win, ui_win, 230, 200, win1_data->temp_buf, win1_data->buf);
  ez_draw_text (ui_win, EZ_TL, 30, 220, "Taille du segement             :");
  ez_draw_line (ui_win, 230,232, 260,232);
  text_display(drawing_win, ui_win, 230, 220, win1_data->temp_buf, win1_data->buf);
  ez_draw_text (ui_win, EZ_TL, 265, 220, "pixel");
  ez_draw_text (ui_win, EZ_TL, 30, 240, "Delais entre 2 flocons animes  :");
  ez_draw_line (ui_win, 230,252, 260,252);
  text_display(drawing_win, ui_win, 230, 240, win1_data->temp_buf, win1_data->buf);
  ez_draw_text (ui_win, EZ_TL, 265, 240, "secondes");
  ez_draw_text (ui_win, EZ_TL, 30, 310, "Nom du fichier (save&load):");
  ez_draw_line (ui_win, 200,322, 290,322);
  text_display(drawing_win, ui_win, 200, 210, win1_data->temp_buf, win1_data->buf);
  ez_draw_text (ui_win, EZ_TL, 295, 310, ".in");
  ez_draw_text (ui_win, EZ_TL, 30, 330, "Type du (save&load)       :");
  ez_draw_text (ui_win, EZ_TL, 50, 355, "PPX  :");
  ez_draw_text (ui_win, EZ_TL, 50, 380, "PIXEL:");
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
    win1_data->active_button[B_KOCH] = 1;
    win1_data->active_button[B_MANDELBROT] = 0;
    win1_data->list = koch(drawing_window, win1_data->n , win1_data->c);
    break;
  case B_MANDELBROT:
    win1_data->active_button[B_KOCH] = 0;
    win1_data->active_button[B_MANDELBROT] = 1;
    
    Complexe z0; //DEBUG
    z0.reel = 0; //DEBUG
    z0.imaginaire = 0; //DEBUG
    win1_data->mandelbrot = generate_mandelbrot(z0, 0.0, (double)win1_data->width, 0.0, (double)win1_data->height);
    ez_send_expose(drawing_window);
    break;
		
    // Choix animations
  case B_ANIME1:
    win1_data->active_button[B_ANIME1] = 1;
    win1_data->active_button[B_ANIME2] = 0;
    win1_data->active_button[B_STOPANIM] = 0;
    break;
  case B_ANIME2:
    win1_data->active_button[B_ANIME1] = 0;
    win1_data->active_button[B_ANIME2] = 1;
    win1_data->active_button[B_STOPANIM] = 0;
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
		
    // Choix du type de sauvegarde et chargement
  case B_PIXMAP:
    win1_data->active_button[B_PIXMAP]  = 1;
    win1_data->active_button[B_PPM]  = 0;
    win1_data->mode = PIXMAP;
    break;
  case B_PPM:
    win1_data->active_button[B_PIXMAP]  = 0;
    win1_data->active_button[B_PPM]  = 1;
    win1_data->mode = PPM;
    break;
			
    // Boutton sauvegarde
  case B_SAVE:
    win1_data->active_button[B_SAVE]  = 1;
    save_pixmap(win1_data->save_file, win1_data->list, win1_data->width, win1_data->height);
    win1_data->active_button[B_SAVE]  = 0;
    break;
		
    // Boutton Chargement
  case B_LOAD:
    printf("loading...\n");
    load_pixmap(win1_data->save_file, &win1_data->width, &win1_data->height);
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
    s[i] = ev->key_string[0]; s[i+1] = 0;
    return 1;
  }
  return 0;
}

void text_display(Ez_window drawing_win, Ez_window ui_win, int x, int y, char *s1, char *s2) {
  Win_Data *win1_data = ez_get_data(drawing_win);
  ez_set_color (ez_black);
  ez_draw_text (ui_win, EZ_TL, x, y, "%s|", s1);

  if (strcmp (win1_data->buf, "") != 0) {
    ez_set_color (ez_blue);
    //ez_draw_text (ui_win, EZ_TC, 200, 70, "You have validated this text:\n%s", s2);
  }
}
