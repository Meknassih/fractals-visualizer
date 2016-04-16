#include <stdio.h>
#include <stdlib.h>
#include "headers/ez-draw.h"
#include "headers/ez-image.h"
#include "headers/util.h"
#include "headers/generate.h"
#include "headers/interface.h"
#include "headers/events.h"

//Variables globales uniquement pour les fenêtres
Ez_window drawing_window, ui_window, popup_window;

int main(int argc, char *argv[]) {
  Win_Data win1_data;

  if (ez_init() < 0)
    exit(1);

  drawing_window = ez_window_create(WIDTH_MAIN, HEIGHT_MAIN, "Affichage fractale", win1_event);
  ui_window = ez_window_create(WIDTH_UI, HEIGHT_UI, "Paramètres", win2_event);
  popup_window = ez_window_create(WIDTH_POPUP, HEIGHT_POPUP, "", win3_event);
  ez_window_show(popup_window, false);

  // Initialisation
  win1_data = init_general_settings();
  win1_data.image_background = init_background();
  init_images_buttons(&win1_data);
  init_buttons(&win1_data);
  win1_data.list = koch(drawing_window, win1_data.n , win1_data.c);
  
  ez_window_dbuf(drawing_window, 1);
  ez_window_dbuf(ui_window, 1);
  ez_auto_quit(false);

  ez_set_data(drawing_window, &win1_data);

  ez_main_loop ();
  exit(0); 
}
