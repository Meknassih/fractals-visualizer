#include "headers/ez-draw.h"
#include "headers/ez-image.h"
#include "headers/interface.h"
#include "headers/generate.h"
#include "headers/events.h"
#include "headers/cplx.h"
#include "headers/animation.h"

/****************************************************
 *Gestion d'évènements pour la fenêtre de dessin    *
 ****************************************************/
void win1_on_expose(Ez_event *ev) {
  Win_Data *win1_data = ez_get_data(ev->win);
	int i;

	if(win1_data->active_button[B_KOCH] && !win1_data->active_button[B_ANIME1] && !win1_data->active_button[B_ANIME2]) {
		if (win1_data->zooming)
			for (i=0; i<win1_data->zoom_part_count; i++)
				dessiner_liste(ev->win, 1, win1_data->zoom_list[i], ez_blue, true);
		else {
			dessiner_liste(ev->win, 1, win1_data->list, ez_blue, false);
			dessiner_frame(ev->win, 2, ez_grey);
		}
		ez_set_thick(3); //DEBUG
		ez_set_color(ez_red); //DEBUG
		ez_draw_point(ev->win, win1_data->width/2, win1_data->height/2); //DEBUG
	}
	else if (win1_data->active_button[B_MANDELBROT])
		print_mandelbrot_julia(ev->win, 1, win1_data->mandelbrot, 0);
	else if (win1_data->active_button[B_JULIA])
		print_mandelbrot_julia(ev->win, 1, win1_data->julia, 1);
	else if (win1_data->active_button[B_ANIME1] && !win1_data->active_button[B_STOPANIM])
		animation(ev->win, win1_data);
	else if (win1_data->active_button[B_ANIME2] && !win1_data->active_button[B_STOPANIM]) {
		animation(ev->win, win1_data);
		printf("Step anim : 	%d \n", win1_data->step_anim); // debug
	}
}


void win1_on_configure(Ez_event *ev) {
  Win_Data *win1_data = ez_get_data(ev->win);

  if (win1_data->configure_count > 1) {
    printf("ConfigureNotify ! %i\n", win1_data->configure_count++);

    win1_data->list = redimensionner_flocon(win1_data->list, ev->width, ev->height , &win1_data->width, &win1_data->height);
    ez_set_data(ev->win, win1_data);
    ez_send_expose(ev->win);
  }
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
    ez_set_data(ev->win, win1_data);
    ez_window_set_size(ev->win, WIDTH_MAIN, HEIGHT_MAIN);
    break;
  }
}

void win1_on_button_press(Ez_event *ev) {
  Win_Data *win_data = ez_get_data(ev->win);
  int i;
  
  switch (ev->mb) {
  case 1: //Clic gauche
    if (zoom(win_data, ev->mx, ev->my)) //Renverra faux si aucun point dans la frame
      win_data->zooming = true;
    break;
  case 3: //Clic droit
    //Réinitialise les données de zoom
    win_data->zooming = false;
    win_data->zoom_part_count = 0;
    for (i=0; i<win_data->zoom_part_count; i++) {
      free(win_data->zoom_list[i]);
      win_data->zoom_list[i] = NULL;
    }
    break;
  }

  ez_set_data(ev->win, win_data);
  ez_send_expose(ev->win);
}

void win1_on_timer(Ez_event *ev) {
	Win_Data *win_data = ez_get_data(ev->win);

	if (win_data->step_anim < win_data->n)
		win_data->step_anim+=1;
	if (win_data->step_anim == win_data->n)
		win_data->step_anim=0;
		
	
	ez_set_data(ev->win, win_data);
	ez_send_expose(ev->win);
	ez_start_timer(ev->win, win_data->delay_anim);
}

void win1_on_motion(Ez_event *ev) {
  Win_Data *win_data = ez_get_data(ev->win);
  if(win_data->active_button[B_KOCH]) {
		win_data->x1_frame = ev->mx - (win_data->width/win_data->factor)/2;
		win_data->y1_frame = ev->my - (win_data->height/win_data->factor)/2;
		win_data->x2_frame = ev->mx + (win_data->width/win_data->factor)/2;
		win_data->y2_frame = ev->my + (win_data->height/win_data->factor)/2;
		ez_set_data(ev->win, win_data);
		ez_send_expose(ev->win);
	}
}

void win1_on_close(Ez_event *ev) {
	ez_quit();
}

void win1_event(Ez_event *ev) {
  switch(ev->type) {
  case Expose: 
    win1_on_expose(ev);
    break;
  case TimerNotify:
    win1_on_timer(ev);
    break;
  case ConfigureNotify:
    win1_on_configure(ev);
    break;
  case KeyPress:
    win1_on_keypress(ev);
    break;
  case ButtonPress:
    win1_on_button_press(ev);
    break;
  case MotionNotify:
    win1_on_motion(ev);
    break;
  case WindowClose:
	win1_on_close(ev);
	break;
  }
}

/****************************************************
 *Gestion d'évènement pour l'interface d'utilisateur*
 ****************************************************/

void win2_on_expose(Ez_event *ev) {
  Win_Data *win1_data = ez_get_data(drawing_window);
  (void) ev;
  
  ez_image_paint(ui_window, win1_data->image_background, 0,0); // Dessine le background du menu
  draw_buttons(ui_window, drawing_window); // dessine tous les bouttons
  draw_text(ui_window, drawing_window); // dessine le text
}

void win2_on_keypress(Ez_event *ev) {
  Win_Data *win1_data = ez_get_data(drawing_window);
  
  int k = text_input (ev, win1_data->temp_buf);
  if (k == 2) {
    strncpy (win1_data->buf, win1_data->temp_buf, BUF_MAX);
    ez_set_data(drawing_window, win1_data);
  }
  if (k > 0) ez_send_expose (ev->win);
}

void win2_on_button_press(Ez_event *ev) {
  Win_Data *win1_data = ez_get_data(drawing_window);
  button id_button;
  
  id_button = get_button_id(win1_data->bptab, win1_data->count_buttons, ev->mx, ev->my); // récupère l'id du boutton cliqué
  if (id_button != B_NONE){ // Si le boutton existe
    execute_button_press(drawing_window, id_button); // On éxécute l'action du boutton
    ez_send_expose(ev->win);
  }
  ez_set_data(drawing_window, win1_data); // renvoie les données à la fenêtre
}

void win2_on_close(Ez_event *ev) {
	ez_quit(); //TODO: juste cacher la fenêtre puis la rouvrir lors de la regénération
}

void win2_event(Ez_event *ev) {
  switch(ev->type) {
  case Expose: 
    win2_on_expose(ev);
    break;
  /*case ConfigureNotify:
    win2_on_configure(ev);
    break;*/
  case KeyPress:
    win2_on_keypress(ev);
    break;
  case ButtonPress:
    win2_on_button_press(ev);
    break;
  case WindowClose:
	win2_on_close(ev);
	break;
  }
}

/****************************************************
 *Gestion d'évènement pour la fenêtre pop-up        *
 ****************************************************/
void win3_on_expose(Ez_event *ev) {
	Win_Data *win1_data = ez_get_data(drawing_window);
	
	ez_set_nfont(1);
	ez_set_color(ez_black);
	// POPUP saisi de texte pour SAVE & LOAD
	if(win1_data->active_button[B_SAVE] || win1_data->active_button[B_LOAD]) { 
		ez_draw_text(ev->win, EZ_MC, WIDTH_POPUP/2, (HEIGHT_POPUP/2)-20, "Entrez le nom du fichier :");
		text_display(popup_window, WIDTH_POPUP/2-50, (HEIGHT_POPUP/2)-5, win1_data->temp_buf, win1_data->buf);
		if(win1_data->active_button[B_PPM])
			ez_draw_text(ev->win, EZ_MR, WIDTH_POPUP-2, HEIGHT_POPUP/2, ".ppm");
		else if(win1_data->active_button[B_PIXMAP])
			ez_draw_text(ev->win, EZ_MR, WIDTH_POPUP-2, HEIGHT_POPUP/2, ".pix");
		ez_set_nfont(0);
		ez_set_color(ez_grey);
		ez_draw_text(ev->win, EZ_MC, WIDTH_POPUP/2, (HEIGHT_POPUP/2)+20, "ENTREE pour valider");
		
	// POPUP pour les autres saisi de valeurs
	} else {
		ez_draw_text(ev->win, EZ_MC, WIDTH_POPUP/2, (HEIGHT_POPUP/2)-20, "Entrez la valeur :");
		text_display(popup_window, WIDTH_POPUP/2-50, (HEIGHT_POPUP/2)-5, win1_data->temp_buf, win1_data->buf);
		ez_set_nfont(0);
		ez_set_color(ez_grey);
		ez_draw_text(ev->win, EZ_MC, WIDTH_POPUP/2, (HEIGHT_POPUP/2)+20, "ENTREE pour valider");
	}

	ez_set_data(drawing_window, win1_data); 
}

void win3_on_keypress(Ez_event *ev) {
	Win_Data *win1_data = ez_get_data(drawing_window);
	int k = text_input(ev, win1_data->temp_buf);

	/* Lorsque l'utilisateur clique sur ENTREE */ 
	if (k == 2) {
		strncpy(win1_data->buf, win1_data->temp_buf, BUF_MAX); // récupère le texte saisi
		valid_text_entry(win1_data); // valide le texte saisi 
		ez_set_data(drawing_window, win1_data); // envoie les donner a win1_data
		ez_send_expose(ui_window); // Afficher la nouvelle valeur sur l'interface graphique
		ez_send_expose(drawing_window); // Dessine sur notre fenêtre d'affichage de fractals
	}

	if (k > 0) ez_send_expose(ev->win);
}

void win3_on_close(Ez_event *ev) {
	ez_window_show(ev->win, false);
}

void win3_event(Ez_event *ev) {
	switch(ev->type) {
	case Expose:
		win3_on_expose(ev);
		break;
	case KeyPress:
		win3_on_keypress(ev);
		break;
    case WindowClose:
		win3_on_close(ev);
		break;
	}
}



