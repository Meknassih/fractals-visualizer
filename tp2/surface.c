#include "ez-draw.h"
#include "ez-image.h"
#include "listep_op.h"

typedef struct {
  PLISTE list;
} Win_Data;

void win1_on_expose(Ez_event *ev) {
  Win_Data *win1_data = ez_get_data(ev->win);
  PLISTE list = win1_data->list;
  EPOINT *dernier_point, *avantdernier_point;

  ez_set_color(ez_red);
  ez_set_thick(5);

  avantdernier_point = list;
  dernier_point = list->next;
  while (dernier_point != NULL) {
    ez_draw_line(ev->win, avantdernier_point->x , avantdernier_point->y, dernier_point->x, dernier_point->y);
    avantdernier_point = dernier_point;
    dernier_point = dernier_point->next;
  }
  ez_draw_line(ev->win, avantdernier_point->x, avantdernier_point->y, list->x, list->y);
}

void win1_event(Ez_event *ev) {
  switch(ev->type) {
  case Expose: 
    win1_on_expose(ev);
    break;
  }
}

int main(int argc, char *argv[]) {
  Ez_window window;
  Win_Data win1_data;
  
  win1_data.list = lire_liste("k2.in");

  if (ez_init() < 0)
    exit(1);
  
  window = ez_window_create(500, 500, "SURFACE", win1_event);
  ez_set_data(window, &win1_data);
  
  ez_main_loop();
  exit(0);

  return 0;
}
