#ifndef __INTERFACE__
#define __INTERFACE__

#include "ez-draw.h"
#include "ez-image.h"
#include "util.h"


// Largeur et hauteur du MENU
#define WIDTH_UI 320
#define HEIGHT_UI 550

// Type de bouttons
typedef enum {
	B_NONE = -1,
	B_KOCH,B_MANDELBROT,B_JULIA,
	B_ANIME1,B_ANIME2,B_ANIME3,B_STOPANIM,
	B_ZOOM4,B_ZOOM6,B_ZOOM8,B_ZOOM10,
	B_PIXMAP,B_PPM,B_SAVE,B_LOAD,
	B_ISMAND_COLOR,
	B_N, B_C, B_DELAY, B_Z0C_REEL, B_Z0C_IMAGINAIRE	
} button;


int ** createTable(int l);
void create_buttons(int *count_buttons, int **bptab, int nbr_buttons, int largeur_button, int hauteur_button, int x, int y);
void draw_buttons(Ez_window ui_win, Ez_window drawing_win);
void draw_text(Ez_window ui_win, Ez_window drawing_win);
button get_button_id(int **bptab, int count_buttons, int mx, int my);
void execute_button_press(Ez_window drawing_win, button id_button);
Ez_image * init_background();
void init_images_buttons(Win_Data *win1_data);
void init_buttons(Win_Data *win1_data);
void init_active_buttons_zoom_text_entry(Win_Data *win1_data, bool r);
void valid_text_entry(Win_Data *win1_data);
int text_input(Ez_event *ev, char *s);
void text_display(Ez_window win, int x, int y, char *s1, char *s2);

#endif
