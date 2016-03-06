#include "headers/util.h"

PLISTE init_liste(double xx, double yy) {
  PLISTE new_list;

  new_list=(PLISTE)malloc(sizeof(EPOINT));

  new_list->x = xx;
  new_list->y = yy;
  new_list->next = NULL;

  return new_list;
}

EPOINT * insert_after(EPOINT * elt, double xx, double yy) {
  EPOINT *new_point, *new_next; //DEBUG new_next

  new_point=(EPOINT*)malloc(sizeof(EPOINT));
  new_point->x = xx;
  new_point->y = yy;
  if (elt->next == NULL) { //Si 'elt' était le dernier de la liste
    new_point->next = NULL; //(xx,yy) n'a pas de successeur (il devient dernier)
    printf("Added (%.0lf,%.0lf) after (%.0lf,%.0lf)\n", xx, yy, elt->x, elt->y); //DEBUG
  } else { //Si 'elt' était en milieu de chaine
    //Le point suivant 'elt' devient le successeur de (xx,yy)
    new_point->next = elt->next;
    new_next = new_point->next; //DEBUG
    printf("Added (%.0lf,%.0lf) between (%.0lf,%.0lf) and (%.0lf,%.0lf)\n", xx, yy, elt->x, elt->y, new_next->x, new_next->y); //DEBUG
  }
  elt->next = new_point; //Le point suivant elt devient le point (xx,yy)
  
  return new_point;
}

EPOINT * remove_after(EPOINT * elt) {
  free(elt->next);
  elt->next = NULL;
  
  return elt;
}

void ecrire_liste(char * nf, PLISTE pl) {
  FILE *pnf;
  EPOINT *current_point;

  pnf=fopen(nf, "w");
  if (pnf==NULL) {
    printf("Impossible d'ouvrir le fichier\n");
    return;
  }
  current_point=pl;
  while(current_point != NULL) {
    fprintf(pnf, "%lf %lf\n", current_point->x, current_point->y);
    current_point = current_point->next;
  }
  printf("Liste ecrite dans %s\n", nf);
}

PLISTE lire_liste(char * nf){
  double x,y;
  PLISTE new_list;
  EPOINT *end_point;
  FILE* pnf = NULL;
  pnf = fopen(nf, "r");
  if (pnf != NULL)
    {
      fscanf(pnf,"%lf %lf\n", &x, &y);
      new_list = init_liste(x,y);
      end_point = new_list;
      while(fscanf(pnf, "%lf %lf\n", &x, &y) != -1){
	//printf("x = %lf y = %lf\n", x, y);
	end_point->next = insert_after(end_point, x,y);
	end_point = end_point->next;
      }
    }
  else
    {
      // On affiche un message d'erreur si on veut
      printf("Impossible d'ouvrir le fichier\n");
    }
  return new_list;
}

void afficher_liste(PLISTE l){
  PLISTE current_point = l;
  int i=0;
  while(current_point != NULL) {
    printf("--N°:%d\nmaillon->x=%lf\nmaillon->y=%lf\nmaillon->next=%p\n", i, current_point->x, current_point->y, current_point->next); 
    current_point = current_point->next;
  } 
}

void dessiner_liste(Ez_window window, int thickness, PLISTE list, Ez_uint32 color) {
	EPOINT *dernier_point, *avantdernier_point;

	ez_set_color(color);
	ez_set_thick(thickness);

	avantdernier_point = list;
	dernier_point = list->next;
	while (dernier_point != NULL) {
		ez_draw_line(window, avantdernier_point->x , avantdernier_point->y, dernier_point->x, dernier_point->y);
		avantdernier_point = dernier_point;
		dernier_point = dernier_point->next;
	}
	ez_draw_line(window, avantdernier_point->x, avantdernier_point->y, list->x, list->y);
}

