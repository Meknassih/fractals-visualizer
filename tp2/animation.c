#include <string.h>
#include "ez-draw.h"
#include "listep_op.h"

typedef enum {
  SIMULTANE,
  SEQUENTIEL
} Expose_Mode;

typedef struct {
  PLISTE list[5];
  Expose_Mode mode;
} Win_Data;

void win1_on_expose(Ez_event *ev) {
  Win_Data *data = ez_get_data(ev->win);
  PLISTE *list = data->list;
  EPOINT *dernier_point, *avantdernier_point;
  int i;

  if (data->mode == SIMULTANE) {
    for (i=0; i<5; i++) { //TODO: Tester la partie SIMULTANE
      ez_set_color(ez_get_HSV(i*80,1,1));
      ez_set_thick(4);

      avantdernier_point = list[i];
      dernier_point = list[i]->next;
      while (dernier_point != NULL) {
	ez_draw_line(ev->win, avantdernier_point->x , avantdernier_point->y, dernier_point->x, dernier_point->y);
	avantdernier_point = dernier_point;
	dernier_point = dernier_point->next;
      }
      ez_draw_line(ev->win, avantdernier_point->x, avantdernier_point->y, list[i]->x, list[i]->y);
    }
  } else if (data->mode == SEQUENTIEL) {
    //TODO: Implémenter partie affichant listes à intervalle t
  }
}

void win1_event(Ez_event *ev) {
  Win_Data *data;
  switch(ev->type) {
  case Expose: 
    win1_on_expose(ev);
    break;
  case KeyPress:
    switch (ev->key_sym) {
    case XK_q : //Touche Q : Quitte
      ez_quit (); 
      break;
    case XK_s : //Touche S : Mode simultané
      data = ez_get_data(ev->win);
      data->mode = SIMULTANE;
      ez_set_data(ev->win, data);
      printf("Mode SIM (%d)\n", data->mode);
      break;
    case XK_d : //Touche D : Mode séquentiel
      data = ez_get_data(ev->win);
      data->mode = SEQUENTIEL;
      ez_set_data(ev->win, data);
      printf("Mode SEQ (%d)\n", data->mode);
    }
    break;
  }
}

int main(int argc, char *argv[]) {
  Ez_window window;
  Win_Data data;
  int i;
  char ia[2]; //version char de i
  char extension[]=".in";
  char nf[10];

  //Initialise nome de fichier à k0.in
  //strcpy(nf, "k0.in");
  //Charge en mémoire les fichier k[0-4].in
  for (i=0; i<5; i++) {
    sprintf(ia, "%i", i); //Conversion de i en char
    strcpy(nf, "k"); //Initialise nf à "k"
    strcat(nf, ia); //Concatène [0-4]
    strcat(nf, extension); //Concatène ".in"
    printf("Chargement du fichier %s...\n", nf);
    data.list[i] = lire_liste(nf);
  }
  data.mode = SIMULTANE;

  if (ez_init() < 0)
    exit(1);
  
  window = ez_window_create(500, 500, "SURFACE", win1_event);
  ez_set_data(window, &data);
  
  ez_main_loop();
  exit(0);

  return 0;
}
