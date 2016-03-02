#include <math.h>
#include "listep.h"
#include "listep_op.h"
#include "generate.h"

/*Génère le triangle de départ à partir du point inférieur
  gauche, le second point est à droite et le troisième est
  celui du haut                                           */
PLISTE init_triangle(int xx, int yy, int c) {
  PLISTE new_list;
  EPOINT *second_point;
  int temp_x, temp_y;

  new_list = init_liste(xx, yy); //Crée une liste avec le point gauche
  printf("%d %d\n", xx, yy); //DEBUG

  temp_x = xx+c; temp_y = yy; //Calcule les coordonnées du point de droite
  printf("%d %d\n", temp_x, temp_y); //DEBUG
  second_point = insert_after(new_list, temp_x, temp_y);

  //Calcule les coordonnées du point supérieur
  temp_x = (int)xx+(c/2);
  temp_y = (int)yy-((c*sqrt(3))/2); 
  printf("%d %d\n", temp_x, temp_y); //DEBUG
  insert_after(second_point, temp_x, temp_y);

  return new_list;
}
/*
PLISTE generer_etape(short int n, PLISTE lp) {
  
}

void koch(short int n, int x, int y, int c) {
  
}
*/
