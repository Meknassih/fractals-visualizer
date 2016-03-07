#include <stdio.h>
#include <stdlib.h>
#include "headers/ez-draw.h"
#include "headers/util.h"
#include "headers/generate.h"

void win1_on_expose(Ez_event *ev) {
  Win_Data *win1_data = ez_get_data(ev->win);
  
  dessiner_liste(ev->win, 1, win1_data->list, ez_blue);
}

void win1_on_configure(Ez_event *ev) {
	Win_Data *win1_data = ez_get_data(ev->win);
	
	printf("ConfigureNotify ! %i\n", win1_data->configure_count++);
	
	win1_data->list = redimensionner_flocon(win1_data->list, ev->width, ev->height , &win1_data->width, &win1_data->height);
	ez_set_data(ev->win, win1_data);
	ez_send_expose(ev->win);
}

void win1_on_keypress (Ez_event *ev) {
	Win_Data *win1_data = ez_get_data(ev->win);
	int *new_height, *new_width;
	new_height = malloc(sizeof(int));
	new_width = malloc(sizeof(int));
	
	switch (ev->key_sym) {
		case XK_s:
			save(win1_data->list, win1_data->save_file, win1_data->mode, win1_data->width, win1_data->height);
			break;
		case XK_l:
			win1_data->list = load_pixmap("sauvegarde", new_width, new_height);
			printf("SETTING WINDOW SIZE Width %d / Height %d\n", *new_width, *new_height);
			win1_data->loading = 0; //Mode loading empêche le redimensionnement lorsque ConfigureNotify sera engendré par ez_window_set_size
			win1_data->width = *new_width;
			win1_data->height = *new_height;
			ez_set_data(ev->win, win1_data);
			ez_window_set_size(ev->win, *new_width, *new_height);
			break;
		case XK_i:
			win1_data->list = koch(ev->win, win1_data->n , win1_data->c);
			win1_data->width = WIDTH_MAIN;
			win1_data->height = HEIGHT_MAIN;
			win1_data->mode = PIXMAP;
			win1_data->save_file = "sauvegarde";
			win1_data->loading = 2;
			ez_set_data(ev->win, win1_data);
			ez_window_set_size(ev->win, WIDTH_MAIN, HEIGHT_MAIN);
			break;
	}
}

void win1_event(Ez_event *ev) {
  switch(ev->type) {
  case Expose: 
    win1_on_expose(ev);
    break;
  case ConfigureNotify:
	win1_on_configure(ev);
	break;
  case KeyPress:
	win1_on_keypress(ev);
	break;
  }
}

int main(int argc, char *argv[]) {
  Ez_window window;
  Win_Data win1_data;

  if (ez_init() < 0)
    exit(1);

  window = ez_window_create (WIDTH_MAIN, HEIGHT_MAIN, "Projet Algorithmique", win1_event);
  win1_data.width = WIDTH_MAIN;
  win1_data.height = HEIGHT_MAIN;
  win1_data.mode = PIXMAP;
  win1_data.save_file = "sauvegarde";
  win1_data.loading = 2;
  
  //DEBUG
  scanf("%d %lf",&win1_data.n ,&win1_data.c);
  win1_data.list = koch(window, win1_data.n , win1_data.c);
  ez_set_data(window, &win1_data);
  //

  ez_main_loop ();
  exit(0); 
}
