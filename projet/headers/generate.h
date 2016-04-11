#ifndef __GENERATE__
#define __GENERATE__

#include "cplx.h"

extern Ez_window drawing_window, ui_window;

//COMMENT
PLISTE init_triangle(Ez_window win, double c);
//COMMENT
void generer_etapes(PLISTE lp);
//COMMENT
PLISTE koch(Ez_window win, int n, double c);

/* **************************************************************** */
/* ************************ Période 2 ***************************** */
/* **************************************************************** */
Complexe*** convertir_complexe(int width, int height);
double** convergence(Complexe ***plan, Complexe z0, int width, int height);
Image* generate_mandelbrot(Complexe z, double xmin, double xmax, double ymin, double ymax);
#endif
