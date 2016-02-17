#include "listep_op.h"

PLISTE init_liste(double xx, double yy) {
  PLISTE new_list;

  new_list=(PLISTE)malloc(sizeof(EPOINT));

  new_list->x = xx;
  new_list->y = yy;
  new_list->next = NULL;

  return new_list;
}

EPOINT * insert_after(EPOINT * elt, double xx, double yy) {
  EPOINT *new_point;

  new_point=(EPOINT*)malloc(sizeof(EPOINT));
  new_point->x = xx;
  new_point->y = yy;
  new_point->next = NULL;
  elt->next = new_point;
  
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
