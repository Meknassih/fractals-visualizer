#include "ez-draw.h"
#include "ez-image.h"
#include "listep_op.h"

void win1_on_expose(Ez_event *ev) {
  ez_set_color(ez_red);
  ez_set_thick(1);
  ez_draw_point(ev->win, 350, 400);
}

void win1_event(Ez_event *ev) {
  switch(ev->type) {
  case Expose: 
    win1_on_expose(ev);
    break;
  }
}

int main(int argc, char *argv[]) {
  Ez_window win1;
  PLISTE mlist;

  mlist = lire_liste("k1.in");

  if (ez_init() < 0)
    exit(1);

  win1 = ez_window_create(500, 500, "SURFACE", win1_event);
  
  ez_main_loop();
  exit(0);

  return 0;
}
