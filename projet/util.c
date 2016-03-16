#include "headers/util.h"
#include "headers/ez-draw.h"

PLISTE init_liste(double xx, double yy) {
  PLISTE new_list;

  new_list=(PLISTE)malloc(sizeof(EPOINT));

  new_list->x = xx;
  new_list->y = yy;
  new_list->next = NULL;

  return new_list;
}

EPOINT * insert_after(EPOINT * elt, double xx, double yy) {
  EPOINT *new_point;
  EPOINT *new_next; //DEBUG

  new_point=(EPOINT*)malloc(sizeof(EPOINT));
  new_point->x = xx;
  new_point->y = yy;
  if (elt->next == NULL) { //Si 'elt' était le dernier de la liste
    new_point->next = NULL; //(xx,yy) n'a pas de successeur (il devient dernier)
    printf("Added (%.0lf,%.0lf) after (%.0lf,%.0lf)\n", xx, yy, elt->x, elt->y); //DEBUG
  } else { //Si 'elt' était en milieu de chaine
    //Le point suivant 'elt' devient le successeur de (xx,yy)
    new_point->next = elt->next;
    new_next = new_point->next; //DEBUG
    printf("Added (%.0lf,%.0lf) between (%.0lf,%.0lf) and (%.0lf,%.0lf)\n", xx, yy, elt->x, elt->y, new_next->x, new_next->y); //DEBUG
  }
  elt->next = new_point; //Le point suivant elt devient le point (xx,yy)
  
  return new_point;
}

EPOINT * remove_after(EPOINT * elt) {
  free(elt->next);
  elt->next = NULL;
  
  return elt;
}

void save_pixmap(char * nf, PLISTE lp, int width, int height) {
  FILE *pnf;
  EPOINT *current_point;
  
  pnf=fopen(nf, "w");
  if (pnf==NULL) {
    printf("Impossible d'ouvrir le fichier\n");
    return;
  }
  
  fprintf(pnf, "%d %d\n", width, height);
  printf("SAVED Width %d / Height %d\n", width, height);
  current_point=lp;
  while(current_point != NULL) {
    fprintf(pnf, "%.0lf %.0lf\n", current_point->x, current_point->y);
    current_point = current_point->next;
  }
  fclose(pnf);
  printf("Liste ecrite dans %s\n", nf);
}

PLISTE load_pixmap(char * nf, int *width, int *height){
  double x,y;
  PLISTE new_list;
  EPOINT *end_point;
  FILE* pnf = NULL;
  char *nfext;
  
  nfext = malloc(strlen(nf) + strlen(".pix") + 1);
  strcpy(nfext, nf);
  strcat(nfext, ".pix");
  pnf = fopen(nfext, "r");
  if (pnf != NULL)
  {
	fscanf(pnf, "%d %d\n", width, height);
	printf("LOADED Width %d / Height %d\n", *width, *height);
    fscanf(pnf, "%lf %lf\n", &x, &y);
    new_list = init_liste(x,y);
    end_point = new_list;
    while(fscanf(pnf, "%lf %lf\n", &x, &y) != -1){
		//printf("x = %lf y = %lf\n", x, y);
		end_point->next = insert_after(end_point, x,y);
		end_point = end_point->next;
    }
  }
  else
  {
    // On affiche un message d'erreur si on veut
    printf("Impossible d'ouvrir le fichier\n");
  }
  fclose(pnf);
  
  return new_list;
}

void afficher_liste(PLISTE l){
  PLISTE current_point = l;
  int i=0;
  
  while(current_point != NULL) {
    printf("--N°:%d\nmaillon->x=%lf\nmaillon->y=%lf\nmaillon->next=%p\n", i, current_point->x, current_point->y, current_point->next); 
    current_point = current_point->next;
  } 
}

void dessiner_liste(Ez_window window, int thickness, PLISTE list, Ez_uint32 color, bool zoom_mode) {
  EPOINT *dernier_point, *avantdernier_point;

  ez_set_color(color);
  ez_set_thick(thickness);

  avantdernier_point = list;
  dernier_point = list->next;
  while (dernier_point != NULL) {
    ez_draw_line(window, avantdernier_point->x , avantdernier_point->y, dernier_point->x, dernier_point->y);
    avantdernier_point = dernier_point;
    dernier_point = dernier_point->next;
  }
  if (!zoom_mode)
    ez_draw_line(window, avantdernier_point->x, avantdernier_point->y, list->x, list->y);
}

void dessiner_frame(Ez_window window, int thickness, Ez_uint32 color) {
  Win_Data *win_data = ez_get_data(window);

  ez_set_color(color);
  ez_set_thick(thickness);

  ez_draw_rectangle(window, win_data->x1_frame, win_data->y1_frame, win_data->x2_frame, win_data->y2_frame);
}

PLISTE redimensionner_flocon(PLISTE lp, int width, int height, int *old_width, int *old_height){
  EPOINT *current_point = lp;
	
  printf("REDIMENSIONNEMENT DE (%d,%d) à (%d,%d)\n", width, height, *old_width, *old_height);
  while (current_point!= NULL) {
    current_point->x = (double) (current_point->x*width)/ *old_width;
    current_point->y = (double) (current_point->y*height)/ *old_height;
    current_point = current_point->next;
  }
  *old_width = width;
  *old_height = height;
	
  return lp;
}

void save(PLISTE lp, char *nf, svmode mode, int width, int height) {
  char *nfext;
	
  switch (mode) {
  case PIXMAP:
    nfext = malloc(strlen(nf) + strlen(".pix") + 1);
    strcpy(nfext, nf);
    strcat(nfext, ".pix");
    save_pixmap(nfext, lp, width, height);
    break;
  case PPM:
    //TODO: SAVE au format PPM
    break;
  }
	
  free(nfext);
}

void load(PLISTE lp, char *nf, svmode mode, int *width, int *height) {
  char *nfext;
	
  switch (mode) {
  case PIXMAP:
    nfext = malloc(strlen(nf) + strlen(".pix") + 1);
    strcpy(nfext, nf);
    strcat(nfext, ".pix");
    load_pixmap(nfext, width, height);
    break;
  case PPM:
    //TODO: SAVE au format PPM
    break;
  }
	
  free(nfext);
}

bool zoom(Win_Data *win_data) {
  win_data->zoom_list = init_zoom(win_data->list, win_data->factor, win_data->x1_frame, win_data->y1_frame, win_data->x2_frame, win_data->y2_frame);
  if (win_data->zoom_list == NULL)
    return false;
  else
    return true;
}

PLISTE init_zoom(PLISTE lp, int factor, int x1_frame, int y1_frame, int x2_frame, int y2_frame) {
  int xc_frame, yc_frame; //Coordonnées du centre de la frame
  int i=1; //DEBUG
  EPOINT *current_point, *last_point;
  PLISTE zoom_list;

  current_point = lp;
  //Cherchons le premier point de la fractale dans la frame
  while (current_point != NULL) {
    if (current_point->x > x1_frame && current_point->x < x2_frame && current_point->y > y1_frame && current_point->y < y2_frame)
      break;
    current_point = current_point->next;
  }
  if (current_point == NULL) { //La fractale ne passe pas par la frame
    printf("Warning: no vertex intersect with zooming frame\n");
    return NULL;
  } else { //Le premier point a été identifié
    printf("Adding point (%.0lf,%.0lf) (0)\n",current_point->x, current_point->y); //DEBUG
    printf("FRAME x %d  y %d | x %d  y%d\n", x1_frame, y1_frame, x2_frame, y2_frame); //DEBUG
    zoom_list = init_liste(current_point->x, current_point->y);

    //On ajoute dans la liste les points situés à l'intérieur de la frame
    last_point = zoom_list; //Le point auquel on va attacher les points suivants
    current_point = current_point->next; //On avance au prochain point
    while (current_point != NULL) {
      if (current_point->x >= x1_frame && current_point->x <= x2_frame && current_point->y >= y1_frame && current_point->y <= y2_frame) {
	printf("Adding point (%d)\n",i); //DEBUG
	printf("FRAME x %d  y %d | x %d  y%d\n", x1_frame, y1_frame, x2_frame, y2_frame); //DEBUG
	last_point = insert_after(last_point, current_point->x,current_point->y);
	i++; //DEBUG
      }
      current_point = current_point->next;
    }
  }

  /*Maintenant, aggrandissons la portion du flocon stockée dans la sous-liste
  xc_frame = (x2_frame - x1_frame)/2; //Centre x et ..
  yc_frame = (y2_frame - y1_frame)/2; //..y de la frame (mx,my)
  current_point = zoom_list;
  while (current_point != NULL) {
    if (current_point->x < xc_frame) { //Gauche
      current_point->x -= (xc_frame - current_point->x)*factor;
    }
    if (current_point->x > xc_frame) { //Droite
      current_point->x += (current_point->x - xc_frame)*factor;
    }

    if (current_point->y < yc_frame) { //Haut
      current_point->y -= (yc_frame - current_point->y)*factor;
    }
    if (current_point->y > yc_frame) { //Bas
      current_point->y += (current_point->y - yc_frame)*factor;
    }
    
    current_point = current_point->next;
  }*/

  return zoom_list;
}
