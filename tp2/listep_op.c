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


PLISTE lire_liste(char * nf){
	double x,y;
	int i;
	PLISTE new_list;
	EPOINT *end_point, *new_final;
    FILE* pnf = NULL;
    pnf = fopen(nf, "r");
    if (pnf != NULL)
    {
		fscanf(pnf,"%lf %lf\n", &x, &y);
		new_list = init_liste(x,y);
			printf("INIT\n");
			printf("new_list->x=%lf\nnew_list->y=%lf\nnew_list->next=%p\n", new_list->x, new_list->y, new_list->next);
			end_point = new_list;
		while(fscanf(pnf, "%lf %lf\n", &x, &y) != -1){
			//	printf("x = %lf y = %lf\n", x, y);
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
   
void afficher_list(PLISTE l){
			PLISTE current_point = l;
			while(current_point != NULL) {
			printf("INSERT\n");
			printf("maillon->x=%lf\nmaillon->y=%lf\nmaillon->next=%p\n", current_point->x, current_point->y, current_point->next); 
			current_point = current_point->next;
		} 
}
