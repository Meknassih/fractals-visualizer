#include "ez-draw.h"
#include "ez-image.h"
#include "listep_op.h"

typedef enum {
  SIMULTANE,
  SEQUENTIEL
} Expose_Mode;

typedef struct {
  PLISTE list[5];
  Expose_Mode mode = SIMULTANE;
} Win_Data;

void win1_on_expose(Ez_event *ev) {
  Win_Data data = ez_get_data(ev->win);
  PLISTE list[5] = data->list;
  EPOINT *dernier_point, *avantdernier_point;

  if (data->mode == SIMULTANE) {
    for (i=0; i<5; i++) { //TODO: Tester la partie SIMULTANE
      ez_set_color(ez_get_HSV(i*20,1,1));
      ez_set_thick(5);

      avantdernier_point = list[i];
      dernier_point = list[i]->next;
      while (dernier_point != NULL) {
	ez_draw_line(ev->win, avantdernier_point->x , avantdernier_point->y, dernier_point->x, dernier_point->y);
	avantdernier_point = dernier_point;
	dernier_point = dernier_point->next;
      }
      ez_draw_line(ev->win, avantdernier_point->x, avantdernier_point->y, list->x, list->y);
    }
  } else if (data->mode == SEQUENTIEL) {
    //TODO: Implémenter partie affichant listes à intervalle t
  }
}

void win1_event(Ez_event *ev) {
  switch(ev->type) {
  case Expose: 
    win1_on_expose(ev);
    break;
  case KeyPress:
    switch (ev->key_sym) {
    case XK_q : 
      ez_quit (); 
      break;
    case XK_s :
	Win_Data *win1_data = ez_get_data(ev->win);
	win1_data->list = lire_liste("");
	break;
    case XK_d :
      
    }
    break;
  }
}

int main(int argc, char *argv[]) {
  Ez_window window;
  Win_Data data;
  int i;
  char *nf;

  strcpy(nf, "k0.out");
      
  for (i=0; i<5; i++) {
    nf[1] = (char)i;
    data.list[i] = lire_liste(nf);
  }

  if (ez_init() < 0)
    exit(1);
  
  window = ez_window_create(500, 500, "SURFACE", win1_event);
  ez_set_data(window, &win1_data);
  
  ez_main_loop();
  exit(0);

  return 0;
}
