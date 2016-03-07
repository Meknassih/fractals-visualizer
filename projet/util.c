#include "headers/util.h"
#include "headers/generate.h"
#include <math.h>

PLISTE init_liste(double xx, double yy) {
  PLISTE new_list;

  new_list=(PLISTE)malloc(sizeof(EPOINT));

  new_list->x = xx;
  new_list->y = yy;
  new_list->next = NULL;

  return new_list;
}

EPOINT * insert_after(EPOINT * elt, double xx, double yy) {
  EPOINT *new_point, *new_next; //DEBUG new_next

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
    printf("Impossible d'ouvrir le fichier %s\n", nf);
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
    printf("Impossible d'ouvrir le fichier %s\n", nfext);
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

void dessiner_liste(Ez_window window, int thickness, PLISTE list, Ez_uint32 color) {
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
 ez_draw_line(window, avantdernier_point->x, avantdernier_point->y, list->x, list->y);
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

PLISTE zoom(int clic_x, int clic_y, int zoom_factor, Win_Data win1_data) {
  PLISTE list_zoom;
  EPOINT *first_point;
  double deltax, deltay;
  int frame_width, frame_height;

  printf("ZOOMING x%d  with n %d  c %.0lf\n", zoom_factor, win1_data.n, win1_data.c*zoom_factor); //DEBUG

  frame_width = win1_data.width/zoom_factor;
  frame_height = win1_data.height/zoom_factor;

  list_zoom = list_from_frame(win1_data.list, frame_width/2 + clic_x, frame_height/2 + clic_y, (frame_width/2 + clic_x) + frame_width, (frame_height/2 + clic_y) + frame_height);
  /*list_zoom = koch(win1_data.width*zoom_factor, win1_data.height*zoom_factor, win1_data.n, win1_data.c*zoom_factor);
  first_point = list_zoom;
  deltax = win1_data.width/2 - first_point->x;
  deltay = win1_data.height/2 - first_point->y;
  list_zoom = offset(list_zoom, deltax, deltay);*/

  return list_zoom;
}

PLISTE offset(PLISTE lp, double deltax, double deltay) {
  EPOINT *current_point = lp;
	
  printf("TRANSLATION DE (%.0lf,%.0lf))\n", deltax, deltay);
  while (current_point!= NULL) {
    current_point->x = (double) current_point->x + deltax;
    current_point->y = (double) current_point->y + deltay;
    current_point = current_point->next;
  }

  return lp;
}

 PLISTE list_from_frame(PLISTE lp, double x1, double y1, double x2, double y2) {
   PLISTE new_list;
   EPOINT *current_point = lp, *last_point;
   bool searching_first_point = true;
   
   new_list = (PLISTE)malloc(sizeof(PLISTE));
   last_point = (EPOINT *)malloc(sizeof(EPOINT));
        
   while (current_point!= NULL) {
     if (current_point->x >= x1 && current_point->x <= x2 && current_point->y >= y1 && current_point->y <= y2 && searching_first_point == true) {
       new_list->x = current_point->x;
       new_list->y = current_point->y;
       last_point = new_list;
       searching_first_point = false;
     } else if (current_point->x >= x1 && current_point->x <= x2 && current_point->y >= y1 && current_point->y <= y2) {
       last_point = insert_after(last_point, current_point->x, current_point->y);
     }
     current_point = current_point->next;
   }

   return new_list;
   }
