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

double** convergence(Complexe z0_c, int width, int height, double xmin, double xmax, double ymin, double ymax, bool isJulia) {
	double **plan_divergence;
	/* Cette fonction calcule la suite zn+1 = zn²+ C
	 * le complexe  z_pow represente : zn²
	 * et p_cpx represente C
	 * */
	Complexe *p_cpx, *z, *z_pow;
	int i,j,n,k;
	
	//Facteurs de calcul de cordonnées en plan complexe
	double reel_factor = (xmax-xmin)/(width-1);
	double imaginaire_factor = (ymax-ymin)/(height-1);
	
	// Initialisation tableau plan_divergence
	plan_divergence = (double **) malloc(sizeof(double)*height);
	for (i=0; i<height; i++) {
		plan_divergence[i] = (double *)malloc(sizeof(double)*width);
	}
	
	for(i=0; i<height; i++) {
		for(j=0; j<width; j++) {
			z = create_complexe(xmin + j*reel_factor,ymax - i*imaginaire_factor); // Convertion du cordonnée pixel [i][j] en cordonnée complexe z
			// Si on demande la génération de fractale de julia
			if(isJulia) p_cpx = create_complexe(z0_c.reel,z0_c.imaginaire); // la constante C ( regarde ligne 165 )
			// Si on demande celui de mandelbrot
			else p_cpx = create_complexe(z0_c.reel+(xmin + j*reel_factor),z0_c.imaginaire+(ymax - i*imaginaire_factor)); // la constante C ( regarde ligne 165 )
			
			k=0; 
			for(n=0; n<MAX_ITER; n++) {
				z_pow = mul_cplx(z,z); // Calcul Zn²
				if(abs_cplx(z) <= L_CONVERGENCE) { // Si le (réel)²+(imaginaire)² <= 4
					k++;
					z = add_cplx(z_pow,p_cpx); // Zn+1 = Zn² +c  => avec Zn² = z_pow et C = p_cpx
				} else {
					plan_divergence[i][j] = k;
					break;
				}
			}
		}
	}
	
	return plan_divergence;
}

Image* generate_mandelbrot_julia(Complexe z0_c, int width, int height, double xmin, double xmax, double ymin, double ymax, bool isJulia, bool isColor) {
	Image *img;
	double **plan_divergence;
	int i,j;
	img = init_image(width,height);
	
	plan_divergence = convergence(z0_c, img->width, img->height, xmin, xmax, ymin, ymax, isJulia);

	for(i=0; i<img->height; i++) {
		for(j=0; j<img->width; j++) {
			Pixel* pix_temp = init_pixel(0,0,0); // en noir 
			if(isColor)
				ez_HSV_to_RGB((360/MAX_ITER)*plan_divergence[i][j], 1, 1, &pix_temp->r, &pix_temp->g, &pix_temp->b);
			else {
				if(plan_divergence[i][j]>1) { // en blanc
					pix_temp->r = 255; 
					pix_temp->g = 255;
					pix_temp->b = 255;
				}
			}
			
			set_pixel(img, pix_temp, i, j);
		}
	}

	return img;	
}
