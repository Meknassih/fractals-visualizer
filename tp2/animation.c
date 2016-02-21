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
  int delay;
  int step; //Etape de l'animation entre [0-4]
} Win_Data;

void win1_on_expose(Ez_event *ev) {
  Win_Data *data = ez_get_data(ev->win);
  PLISTE *list = data->list;
  EPOINT *dernier_point, *avantdernier_point;
  int i;

  if (data->mode == SIMULTANE) { //Mode simultané
    for (i=0; i<5; i++) { //Pour chaque liste (i.e. k[0-4].in)
      ez_set_color(ez_get_HSV(i*80,1,1));
      ez_set_thick(4);

      avantdernier_point = list[i];
      dernier_point = list[i]->next;
      //Trace des segments entre les points jusqu'à fin de liste
      while (dernier_point != NULL) {
	ez_draw_line(ev->win, avantdernier_point->x , avantdernier_point->y, dernier_point->x, dernier_point->y);
	avantdernier_point = dernier_point;
	dernier_point = dernier_point->next;
      }
      //Relie le dernier point au premier
      ez_draw_line(ev->win, avantdernier_point->x, avantdernier_point->y, list[i]->x, list[i]->y);
    }
  } else if (data->mode == SEQUENTIEL) { //Mode séquentiel
    ez_set_color(ez_black);
    ez_set_thick(4);

    avantdernier_point = list[data->step];
    dernier_point = list[data->step]->next;
    //Trace des segments entre les points jusqu'à fin de liste
    while (dernier_point != NULL) {
      ez_draw_line(ev->win, avantdernier_point->x , avantdernier_point->y, dernier_point->x, dernier_point->y);
      avantdernier_point = dernier_point;
      dernier_point = dernier_point->next;
    }
    //Relie le dernier point au premier
    ez_draw_line(ev->win, avantdernier_point->x, avantdernier_point->y, list[data->step]->x, list[data->step]->y);
  }
}

void win1_on_timer(Ez_event *ev) {
  Win_Data *data = ez_get_data(ev->win);
  if (data->step < 4)
    data->step+=1;
  else
    data->step=0;
  ez_set_data(ev->win, data);
  ez_send_expose(ev->win);
  ez_start_timer(ev->win, data->delay);
}

void win1_event(Ez_event *ev) {
  Win_Data *data;
  switch(ev->type) {
  case Expose: 
    win1_on_expose(ev);
    break;
  case TimerNotify:
    win1_on_timer(ev);
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
      ez_start_timer(ev->win, -1); //Supprime le timer
      printf("Mode SIM (%d)\n", data->mode);
      ez_send_expose(ev->win); //Force à redessiner toutes les formes
      break;
    case XK_d : //Touche D : Mode séquentiel
      data = ez_get_data(ev->win);
      data->mode = SEQUENTIEL;
      data->step = 0; //Remet l'animation à 0
      ez_set_data(ev->win, data);
      ez_start_timer(ev->win, data->delay); //Met en place le timer
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
  data.delay = 100;
  data.step = 0;

  if (ez_init() < 0)
    exit(1);
  
  window = ez_window_create(500, 500, "SURFACE", win1_event);
  ez_set_data(window, &data);

  ez_main_loop();
  exit(0);

  return 0;
}
