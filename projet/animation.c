#include "headers/ez-draw.h"
#include "headers/util.h"
#include "headers/generate.h"
#include "headers/interface.h"
#include "headers/events.h"
#include "headers/animation.h"



void animation(Ez_window drawing_win, Expose_Mode mode, int n) {
	Win_Data *win1_data = ez_get_data(drawing_win);
	PLISTE *list_anim = win1_data->list_anim;
	EPOINT *dernier_point, *avantdernier_point;
	int i;
	
	// Génération de toutes les étapes
	for(i=0;i <n; i++) {
		list_anim[i] = koch(drawing_win, i, win1_data->c);
	}
	
	// Mode simultané
	if (win1_data->mode_anim == SIMULTANE) { 
		for (i=0; i<n; i++) { // Pour chaque liste
			ez_set_color(ez_get_HSV(i*80,1,1));
			ez_set_thick(4);

			avantdernier_point = list_anim[i];
			dernier_point = list_anim[i]->next;
			//Trace des segments entre les points jusqu'à fin de liste
			while (dernier_point != NULL) {
				ez_draw_line(drawing_win, avantdernier_point->x , avantdernier_point->y, dernier_point->x, dernier_point->y);
				avantdernier_point = dernier_point;
				dernier_point = dernier_point->next;
			}
			//Relie le dernier point au premier
			ez_draw_line(drawing_win, avantdernier_point->x, avantdernier_point->y, list_anim[i]->x, list_anim[i]->y);
		}
	} else if (win1_data->mode_anim == SEQUENTIEL) { //Mode séquentiel
		ez_set_color(ez_black);
		ez_set_thick(4);

		avantdernier_point = list_anim[win1_data->step_anim];
		dernier_point = list_anim[win1_data->step_anim]->next;
		//Trace des segments entre les points jusqu'à fin de liste
		while (dernier_point != NULL) {
			ez_draw_line(drawing_win, avantdernier_point->x , avantdernier_point->y, dernier_point->x, dernier_point->y);
			avantdernier_point = dernier_point;
			dernier_point = dernier_point->next;
		}
		//Relie le dernier point au premier
		ez_draw_line(drawing_win, avantdernier_point->x, avantdernier_point->y, list_anim[win1_data->step_anim]->x, list_anim[win1_data->step_anim]->y);
	}
}
