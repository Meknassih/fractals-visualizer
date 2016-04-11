#include <math.h>
#include "headers/util.h"
#include "headers/cplx.h"
#include "headers/generate.h"


/*Génère le triangle de départ à partir du point inférieur
  gauche, le second point est à droite et le troisième est
  celui du haut                                           */
PLISTE init_triangle(Ez_window win, double c) {
  PLISTE new_list;
  EPOINT *second_point;
  double x1, y1, x2, y2, x3, y3;
  double x3_ex, y3_ex; //Au cas où nous aurions besoin des valeurs exactes
  int win_width, win_height;
  
  /* Récupère la taille actuelle de la fenêtre                        */
  ez_window_get_size(win, &win_width, &win_height);
  
  /* On calcule la position du point inférieur gauche de façon à ce
   * qu'il soit centré par rapport à la taille de la fenêtre récupérée
   * juste avant                                                      */
  x1 = round((win_width/2.0) - (c/2.0));
  y1 = round((win_height/2.0) - (c * (sqrt(3)/6)));
  printf("x1 %.0lf  y1 %.0lf\n", x1, y1); //DEBUG
  
  new_list = init_liste(x1, y1); //Crée une liste avec le point gauche

  x2 = x1+c; y2 = y1; //Calcule les coordonnées du point de droite
  second_point = insert_after(new_list, x2, y2);

  //Calcule les coordonnées du point supérieur
  //x3 = (int)xx+(c/2);
  //y3 = (int)yy-((c*sqrt(3))/2);
  x3_ex = (x1 + x2)*cos(60 * M_PI / 180) - (y2 - y1)*sin(60 * M_PI / 180);
  y3_ex = (y1 + y2)*cos(60 * M_PI / 180) + (x2- x1)*sin(60 * M_PI / 180);
  x3 = round(x3_ex);
  y3 = round(y3_ex);
  insert_after(second_point, x3, y3);

  return new_list;
}

void generer_etapes(PLISTE lp) {
  
  EPOINT *end_vertex = lp->next; //Point représentant la fin du segment
  EPOINT *begin_vertex = lp; //Point représentant le début du segment
  EPOINT *p1, *p2; //Points temporaires pour l'insertion dans la liste
  EPOINT premier_tiers, second_tiers, nouveau_sommet; //Points à créer
  int i = 0; //Compteur de segments sectionnés
  bool done = false; //Booléen vrai lorsque tous les segments sont traités
  //int x1, x2, y1, y2; //[(x1,y1),(x2,y2)] est le segment à sectionner en 3

  //Ignorer cette initialisation (aucun effet sur la procédure)
  premier_tiers.next = NULL;
  second_tiers.next = NULL;
  nouveau_sommet.next = NULL;
  
  while(!done) {
    printf("SEGMENT %d [(%.0lf,%.0lf),(%.0lf,%.0lf)]\n", i, begin_vertex->x, begin_vertex->y, end_vertex->x, end_vertex->y); //DEBUG
    
    /*Calculons les coordonnées des deux points produits par
     *la section du segment en 3                            */
    premier_tiers.x=round(begin_vertex->x + (1/3.0)*(end_vertex->x - begin_vertex->x));
    premier_tiers.y=round(begin_vertex->y + (1/3.0)*(end_vertex->y - begin_vertex->y));
    second_tiers.x=round(begin_vertex->x + (2/3.0)*(end_vertex->x - begin_vertex->x));
    second_tiers.y=round(begin_vertex->y + (2/3.0)*(end_vertex->y - begin_vertex->y));

    /*Détérminons maintenant le sommet du futur triangle équilatéral
     *dont les deux sommets inférieurs sont les précédents (je n'ai
     *pas pu faire plus simple)                                     */
    //nouveau_sommet.x = round(cos(60 * M_PI / 180) * (premier_tiers.x - second_tiers.x) - sin(60 * M_PI / 180) * (premier_tiers.y - second_tiers.y) + second_tiers.x);
    //nouveau_sommet.y = round(sin(60 * M_PI / 180) * (premier_tiers.x - second_tiers.x) + cos(60 * M_PI / 180) * (premier_tiers.y - second_tiers.y) + second_tiers.y);
	nouveau_sommet.x = round((premier_tiers.x + second_tiers.x)*cos(300 * M_PI / 180) - (second_tiers.y - premier_tiers.y)*sin(300 * M_PI / 180));
    nouveau_sommet.y = round((premier_tiers.y + second_tiers.y)*cos(300 * M_PI / 180) + (second_tiers.x - premier_tiers.x)*sin(300 * M_PI / 180));

    /*Ajoutons tout ce beau monde dans la liste chainée entre 
     *les points begin_vertex et end_vertex du segment       */
    p1 = insert_after(begin_vertex, premier_tiers.x, premier_tiers.y);
    p2 = insert_after(p1, nouveau_sommet.x, nouveau_sommet.y);
    insert_after(p2, second_tiers.x, second_tiers.y);

    /*On avance au prochain segment dont le début
     *est la fin du segment actuel               */
    if (end_vertex->next != NULL && end_vertex != lp) {
      begin_vertex = end_vertex;
      end_vertex = end_vertex->next;
    } else if (end_vertex == lp) {
      /*On termine la boucle lorsqu'on revient au début
       *de la liste des points (lp : premier point     */
      done = true;
    } else { 
      /*On boucle la liste de points avec le début du dernier
       *segment étant le dernier point de la liste et la fin
       *de ce segment étant le premier point de la liste     */
      begin_vertex = end_vertex;
      end_vertex = lp;
    }
    i++;
  }
}

PLISTE koch(Ez_window win, int n, double c) {
  PLISTE lp;
	
  lp = init_triangle(win ,c);
  if(n > 0) {
    while(n>0){
      generer_etapes(lp);
      n--;
    } 
  } else {
    printf("Aucune étape à génerer !\n");
  }
	
  return lp;
}

/* **************************************************************** */
/* ************************ Période 2 ***************************** */
/* **************************************************************** */

Complexe*** convertir_complexe(int width, int height) {
	int i,j;
	Complexe ***plan_complexe;
	
	plan_complexe = malloc(sizeof(Complexe**)*height);
	for (i=0; i<height; i++) {
		plan_complexe[i] = malloc(sizeof(Complexe*)*width);
	}
	for (i=0; i<height; i++) {
		for (j=0; j<width; j++) {
			plan_complexe[i][j] = create_complexe((double)i, (double)j);
		}
	}

	return plan_complexe;
}

double** convergence(Complexe ***plan_complexe, Complexe z0, int width, int height) {
	int k=1,i,j;
	double **plan_divergence;
	Complexe *z1,*z2,*z_pow;
	z1 = create_complexe(z0.reel, z0.imaginaire);
	z2 = create_complexe(0,0);
	z_pow = create_complexe(0,0); // Z(n-1) au carrée
	
	// Initialisation tableau plan_divergence

	plan_divergence = malloc(sizeof(double*)*height);
	for (i=0; i<height; i++) {
		plan_divergence[i] = malloc(sizeof(double)*width);
	}
	
	// Calcul de divergence
	for (i=0; i<height; i++) {
		for (j=0; j<width; j++) { 
			
			while(k<=MAX_ITER) {
				z_pow = mul_cplx(z1,z1);
				z2 = add_cplx(z_pow,plan_complexe[i][j]);
				
				if(abs_cplx(z2)<=L_CONVERGENCE) {
					k++;
					free(z1);
					z1 = create_complexe(z2->reel,z2->imaginaire); 
				 } else {
					plan_divergence[i][j] = k;
					break;
				 }
			}
			if (k>MAX_ITER) plan_divergence[i][j] = k; 
			
		}
	}
	
	free(z1);
	free(z2);
	free(z_pow);
	
	return plan_divergence;
}

Image* generate_mandelbrot(Complexe z0, double xmin, double xmax, double ymin, double ymax) {
	Complexe ***plan_complexe;
	double **plan_divergence;
	int i, j;
	Image *img;
	img = init_image(xmax-xmin, ymax-ymin);
	
	plan_complexe = convertir_complexe(img->width, img->height); // Normalement ça fonctione parfaitement
	plan_divergence = convergence(plan_complexe, z0, img->width, img->height); // ça pose un problème, ça renvoie tjr la meme valeur k
	
	for (i=0; i<img->height; i++) {
		for (j=0; j<img->width; j++) {
			Pixel* pix_temp = init_pixel(255,255,255);
			printf("plan_divergence[%d][%d] = %lf\n", i,j, plan_divergence[i][j]); // Debug
			ez_HSV_to_RGB((360/MAX_ITER)*plan_divergence[i][j], 1, 1, &pix_temp->r, &pix_temp->g, &pix_temp->b);
			printf("r : %d, g : %d, b : %d\n", pix_temp->r, pix_temp->g, pix_temp->b); // Debug
			set_pixel(img, pix_temp, i, j);
		}
	}
	
	return img;
}
