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
  int i=0; //DEBUG

  ez_set_color(color);
  ez_set_thick(thickness);

  avantdernier_point = list;
  dernier_point = list->next;
  while (dernier_point != NULL) {
    if (dernier_point->next == NULL) //DEBUG
      ez_set_color(ez_red);
    else if (i==0) //DEBUG
      ez_set_color(ez_green);
    else
      ez_set_color(color);
    ez_draw_line(window, avantdernier_point->x , avantdernier_point->y, dernier_point->x, dernier_point->y);
    avantdernier_point = dernier_point;
    dernier_point = dernier_point->next;

    i++; //DEBUG
  }
  
  if (!zoom_mode) {
    ez_set_color(color);
    ez_draw_line(window, avantdernier_point->x, avantdernier_point->y, list->x, list->y);
  }
}

void dessiner_frame(Ez_window window, int thickness, Ez_uint32 color) {
  Win_Data *win_data = ez_get_data(window);

  ez_set_color(color);
  ez_set_thick(thickness);

  ez_draw_rectangle(window, win_data->x1_frame, win_data->y1_frame, win_data->x2_frame, win_data->y2_frame);

  ez_set_thick(1);
  ez_draw_rectangle(window, win_data->x1_frame-FRAME_MARGIN, win_data->y1_frame-FRAME_MARGIN, win_data->x2_frame+FRAME_MARGIN, win_data->y2_frame+FRAME_MARGIN);
}

Win_Data init_general_settings(void) {
  Win_Data win_data;
  int i;
  
  win_data.width = WIDTH_MAIN;
  win_data.height = HEIGHT_MAIN;
  win_data.mode = PIXMAP;
  win_data.n = ORDRE_INIT;
  win_data.c = TAILLE_INIT;
  win_data.save_file = "sauvegarde";
  win_data.configure_count = 0;
  win_data.zooming = false;
  win_data.factor = FACTOR_INIT;
  win_data.zoom_part_count = 0;
  for (i=0; i<MAX_ZOOM_PARTS; i++)
    win_data.zoom_list[i] = NULL;
  win_data.mandelbrot = init_image(WIDTH_MAIN, HEIGHT_MAIN);

  win_data.buf = malloc(sizeof(char)*BUF_MAX);
  win_data.temp_buf = malloc(sizeof(char)*BUF_MAX);

  return win_data;
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

bool zoom(Win_Data *win_data, int mouse_x, int mouse_y) {
  init_zoom(win_data);
  center_points(win_data, (win_data->width/2)-mouse_x, (win_data->height/2)-mouse_y);
  expand_points(win_data);
  
  if (win_data->zoom_list == NULL)
    return false;
  else
    return true;
}

void init_zoom(Win_Data *win_data) {
  PLISTE lp = win_data->list;
  //int factor = win_data->factor;
  int x1_frame = win_data->x1_frame - FRAME_MARGIN;
  int y1_frame = win_data->y1_frame - FRAME_MARGIN;
  int x2_frame = win_data->x2_frame + FRAME_MARGIN;
  int y2_frame = win_data->y2_frame + FRAME_MARGIN;
  //int xc_frame, yc_frame; //Coordonnées du centre de la frame
  //int i=1; //DEBUG
  EPOINT *current_point, *last_point = NULL;
  PLISTE zoom_list[MAX_ZOOM_PARTS];
  bool searching_first_point = true;

  current_point = lp;
  //Cherchons le premier point de la fractale dans la frame
  while (current_point != NULL) {
    if (current_point->x > x1_frame && current_point->x < x2_frame && current_point->y > y1_frame && current_point->y < y2_frame) { //Si le point est dans la frame
      if (searching_first_point) { //Si c'est le premier point d'une portion du flocon
	printf("First point found, creating list\n");
	zoom_list[win_data->zoom_part_count] = init_liste(current_point->x, current_point->y);
	last_point = zoom_list[win_data->zoom_part_count];
	win_data->zoom_part_count++;
	searching_first_point = false;
      } else { //Si c'est un des points suivants le premier
	printf("Multi point found, inserting into list\n");
	last_point = insert_after(last_point, current_point->x, current_point->y);
      }
    } else {
      if (last_point != NULL) { //Si le point précédent est dans la frame
	printf("End of list, searching new part\n");
	last_point = NULL;
	searching_first_point = true;
      }
    }
    current_point = current_point->next;
  }
  /*
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
*/
  //On recopie le tableau de sous-listes dans la structure de données
  memcpy(win_data->zoom_list, zoom_list, sizeof(PLISTE)*100);
}

void center_points(Win_Data *win_data, int x_offset, int y_offset) {
  EPOINT *current_point;
  int i;
  
  for (i=0; i<win_data->zoom_part_count; i++) {
    printf("Centering zoom part %d\n", i);
    current_point = win_data->zoom_list[i];
    
    while (current_point != NULL) {
      current_point->x += x_offset;
      current_point->y += y_offset;
      current_point = current_point->next;
    }
  }
}

void expand_points(Win_Data *win_data) {
  EPOINT *current_point;
  int xc_window = win_data->width/2;
  int yc_window = win_data->height/2;
  int i;
  
  /*Maintenant, aggrandissons la ou les portions du flocon stockées dans
   *le tableau de sous-listes zoom_list                                 */
  for (i=0; i<win_data->zoom_part_count; i++) {
    printf("Expanding zoom part %d\n", i);
    current_point = win_data->zoom_list[i];
    while (current_point != NULL) {
      if (current_point->x < xc_window) { //Gauche
	current_point->x -= (xc_window - current_point->x)*(win_data->factor-1);
      }
      if (current_point->x > xc_window) { //Droite
	current_point->x += (current_point->x - xc_window)*(win_data->factor-1);
      }

      if (current_point->y < yc_window) { //Haut
	current_point->y -= (yc_window - current_point->y)*(win_data->factor-1);
      }
      if (current_point->y > yc_window) { //Bas
	current_point->y += (current_point->y - yc_window)*(win_data->factor-1);
      }
    
      current_point = current_point->next;
    }
  }

}

/* **************************************************************** */
/* ************************ Période 2 ***************************** */
/* **************************************************************** */

Pixel* init_pixel(int R, int G, int B) {
	Pixel* pix;
	
	pix = malloc(sizeof(Pixel));
	
	pix->r = R;
	pix->g = G;
	pix->b = B;
	
	return pix;
}

Image* init_image(int width, int height) {
	Image* img;
	int i,j;
	img = malloc(sizeof(Image));
	
	img->plan = malloc(sizeof(Pixel**)*height);
	for (i=0; i<height; i++) {
		img->plan[i] = malloc(sizeof(Pixel*)*width);
	}
	
	for (i=0; i<height; i++) {
		for (j=0; j<width; j++) {
			img->plan[i][j] = init_pixel(255, 255, 255);
		}
	}
	
	img->width = WIDTH_MAIN;
	img->height = HEIGHT_MAIN;
	
	return img;
}

void set_pixel(Image * img, Pixel * p, int lig, int col) {
	img->plan[lig][col] = p;
}

void free_image(Image *img) {
	int i, j;
	
	for (i=0; i<img->height; i++) {
		for (j=0; j<img->width; j++) {
			free(img->plan[i][j]);
		}
	}
	
	for (i=0; i<img->height; i++) {
		free(img->plan[i]);
	}
	
	free(img->plan);
}

void print_mandelbrot_julia(Ez_window window, int thickness, Image *fractale, bool isJulia) { // isJulia pas nécéssaire, à retirer
	int i,j;
	ez_set_thick(thickness);
	Pixel ***plan = fractale->plan;
	for (i=0; i<fractale->height; i++) {
		for (j=0; j<fractale->width; j++) {
			ez_set_color(ez_get_RGB(plan[i][j]->r, plan[i][j]->g, plan[i][j]->b));
			ez_set_thick(1);
			ez_draw_point(window, i, j);
			//DEBUG
			if(isJulia)
			printf("Julia : drawing point (%d, %d) color %d\n", i, j, ez_get_RGB(plan[i][j]->r, plan[i][j]->g, plan[i][j]->b));
			else
			printf("Mandelbrot : drawing point (%d, %d) color %d\n", i, j, ez_get_RGB(plan[i][j]->r, plan[i][j]->g, plan[i][j]->b));
		}
	}
}
