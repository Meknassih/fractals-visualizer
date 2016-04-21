#include "headers/ez-draw.h"
#include "headers/util.h"
#include "headers/generate.h"
#include "headers/interface.h"
#include "headers/events.h"
#include "headers/animation.h"



void animation(Ez_window drawing_win, Win_Data *win1_data) {
	PLISTE *list_anim = win1_data->list_anim;
	int i;
	
	// Génération de toutes les étapes
	for(i=0;i < win1_data->n; i++) {
		list_anim[i] = koch(drawing_win, i, win1_data->c);
	}
	
	// Mode simultané
	if (win1_data->mode_anim == FINIE) {
		dessiner_liste(drawing_window, 3, win1_data->list_anim[win1_data->step_anim], ez_black, false);
	//Mode CIRCULAIRE		
	} else if (win1_data->mode_anim == CIRCULAIRE) { 
		dessiner_liste(drawing_window, 3, win1_data->list_anim[win1_data->step_anim], ez_black, false);
	}
}
