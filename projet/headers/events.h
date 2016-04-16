#ifndef __EVENTS__
#define __EVENTS__

#include "ez-draw.h"

extern Ez_window drawing_window, ui_window, popup_window;

void win1_on_expose(Ez_event *ev);
void win1_on_configure(Ez_event *ev);
void win1_on_keypress (Ez_event *ev);
void win1_on_button_press(Ez_event *ev);
void win1_on_motion(Ez_event *ev);
void win1_on_close(Ez_event *ev);
void win1_event(Ez_event *ev);

void win2_on_expose(Ez_event *ev);
void win2_on_button_press(Ez_event *ev);
void win2_on_close(Ez_event *ev);
void win2_event(Ez_event *ev);

void win3_on_expose(Ez_event *ev);
void win3_on_close(Ez_event *ev);
void win3_event(Ez_event *ev);

#endif
