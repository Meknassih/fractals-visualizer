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
double** convergence(Complexe z0_c, int width, int height, double xmin, double xmax, double ymin, double ymax, bool isJulia);
Image* generate_mandelbrot_julia(Complexe z0_c, int width, int height, double xmin, double xmax, double ymin, double ymax, bool isJulia, bool isColor);
#endif
