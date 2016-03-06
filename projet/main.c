#include <stdio.h>
#include <stdlib.h>
#include "headers/ez-draw.h"
#include "headers/util.h"
#include "headers/generate.h"

#define WIDTH_MAIN 800
#define HEIGHT_MAIN 480

void win1_on_expose(Ez_event *ev) {
  Win_Data *win1_data = ez_get_data(ev->win);
  dessiner_liste(ev->win, 1, win1_data->list, ez_blue);
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

  if (ez_init() < 0)
    exit(1);

  window = ez_window_create (WIDTH_MAIN, HEIGHT_MAIN, "Projet Algorithmique", win1_event);

  //DEBUG
  int n;
  double c;
  scanf("%d %lf",&n ,&c);
  win1_data.list = koch(window, n, c);
  ez_set_data(window, &win1_data);
  //

  ez_main_loop ();
  exit(0); 
}
