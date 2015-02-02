// Gestion arbre

#include <stdlib.h>
#include <math.h>
#include <sys/time.h>

#include "arbre.h"
#include "definition.h"

int arbre_a_distance(float x, float y, float z, int rayon, int longut, int longuf)
{
	int cpt = 0;
	float dist;
	point p1;

	p1.x = x;
	p1.y = y;
	p1.z = z;

	while(cpt < nb_arbre_actuel)
	{
		dist = sqrt(((tab_arbre_aff[cpt].position.x-p1.x) * (tab_arbre_aff[cpt].position.x-p1.x)) + ((tab_arbre_aff[cpt].position.y-p1.y) * (tab_arbre_aff[cpt].position.y-p1.y)) + ((tab_arbre_aff[cpt].position.z-p1.z) * (tab_arbre_aff[cpt].position.z-p1.z)));
		
		if( (y < (tab_arbre_aff[cpt].position.y + tab_arbre_aff[cpt].l_feuil + tab_arbre_aff[cpt].l_tronc))||(tab_arbre_aff[cpt].position.y < (y+longut+longuf)))
		{
			if(dist < (rayon+tab_arbre_aff[cpt].r_feuil))
			{
				return 1;
			}
		}
		cpt++;
	}

	return 0;
}

void creation_arbre_alea(float rMinX, float rMaxX, float rMinY, float rMaxY, float rMinZ, float rMaxZ, float tMinB, float tMaxB, float tMinL, float tMaxL, float fMinR, float fMaxR, float fMinL, float fMaxL)
{
	float x,y,z,tB,tL,fR,fL=0;
	int cpt = 0;
	int choixT,test = 0;

	#ifdef _WIN32
	float t1 = GetTickCount64();
	#else
	struct timeval t;
	gettimeofday(&t, NULL);
	float t1 = t.tv_usec * t.tv_sec;
	#endif

	x=0;y=0;z=0;

	if(nb_arbre_actuel < NB_ARBRE_MAX)
	{
		srand(t1);

		// Tronc Base
		if(tMinB == 0 && tMaxB == 0)
		{
			tB = 0;
		}
		else
		{
			tB = rand()%(int)(tMaxB-tMinB)+tMinB;
		}
		// Tronc Longueur
		if(tMinL == 0 && tMaxL == 0)
		{
			tL = 0;
		}
		else
		{
			tL = rand()%(int)(tMaxL-tMinL)+tMinL;
		}	
		// Feuillage Rayon
		if(fMinR == 0 && fMaxR == 0)
		{
			fR = 0;
		}
		else
		{
			fR = rand()%(int)(fMaxR-fMinR)+fMinR;
		}
		// Feuillage Longueur
		if(fMinL == 0 && fMaxL == 0)
		{
			fL = 0;
		}
		else
		{
			fL = rand()%(int)(fMaxL-fMinL)+fMinL;
		}		

		do
		{
			// Position X
			if(rMinX == 0 && rMaxX == 0)
			{
				x = 0;
			}
			else
			{
				x = rand()%(int)(rMaxX-rMinX)+rMinX;
			}
			// Position Y
			if(rMinY == 0 && rMaxY == 0)
			{
				y = 0;
			}
			else
			{
				y = rand()%(int)(rMaxY-rMinY)+rMinY;
			}
			// Position Z
			if(rMinZ == 0 && rMaxZ == 0)
			{
				z = 0;
			}
			else
			{
				z = rand()%(int)(rMaxZ-rMinZ)+rMinZ;
			}
			cpt++;
			// Vérification emplacement possible
			if((arbre_a_distance(x,y,z,fR,fL,tL) == 0))
			{
				test = 1;
			}
			else if(cpt >= NB_ARBRE_MAX)
			{
				test = 2;
			}
		}
		while(test == 0);

		if(test < 2)
		{
			choixT = rand() % NB_TYPE_ARBRE;

			nb_arbre_actuel++;

			tab_arbre_aff = (arbre_aff*)realloc(tab_arbre_aff,sizeof(arbre_aff)*(nb_arbre_actuel));

			tab_arbre_aff[nb_arbre_actuel-1].type_arbre = choixT;
			tab_arbre_aff[nb_arbre_actuel-1].r_tronc = tB;
			tab_arbre_aff[nb_arbre_actuel-1].l_tronc = tL;
			tab_arbre_aff[nb_arbre_actuel-1].r_feuil = fR;
			// arbre boule
			if(choixT == 1)
			{
				tab_arbre_aff[nb_arbre_actuel-1].l_feuil = fR;
			}
			// sapin
			else
			{
				tab_arbre_aff[nb_arbre_actuel-1].l_feuil = fL;
			}
			tab_arbre_aff[nb_arbre_actuel-1].position.x = x;
			tab_arbre_aff[nb_arbre_actuel-1].position.y = y;
			tab_arbre_aff[nb_arbre_actuel-1].position.z = z;
		}
	}
}

void creation_N_arbre(int nbA, float rMinX, float rMaxX, float rMinY, float rMaxY, float rMinZ, float rMaxZ, float tMinB, float tMaxB, float tMinL, float tMaxL, float fMinR, float fMaxR, float fMinL, float fMaxL)
{
	int cpt;

	for(cpt = 0; cpt < nbA ; cpt++)
	{
		creation_arbre_alea(rMinX, rMaxX, rMinY, rMaxY, rMinZ, rMaxZ, tMinB, tMaxB, tMinL, tMaxL, fMinR, fMaxR, fMinL, fMaxL);
	}
}

void creation_rectangle_arbre_laby(float tMinB, float tMaxB, float tMinL, float tMaxL, float fMinR, float fMaxR, float fMinL, float fMaxL)
{
	int nb_arbre_larg = 400;
	int nb_arbre_long = 1500;

	// Creation des 4 rectangles autour du labyrinthe
	// Rectangle bas
	tab_sol_arbre_aff[0].position1.x = 0;
	tab_sol_arbre_aff[0].position1.z = -LARGEUR_RECT_ARBRE;

	tab_sol_arbre_aff[0].position2.x = SIZE_CELL * largeur_labyrinthe;
	tab_sol_arbre_aff[0].position2.z = 0;
	
	// Creation des arbres pour ce rectangle
	creation_N_arbre(nb_arbre_larg,tab_sol_arbre_aff[0].position1.x,tab_sol_arbre_aff[0].position2.x,tab_sol_arbre_aff[0].position1.y,tab_sol_arbre_aff[0].position2.y,tab_sol_arbre_aff[0].position1.z,tab_sol_arbre_aff[0].position2.z-fMinL,
					tMinB, tMaxB, tMinL, tMaxL, fMinR, fMaxR, fMinL, fMaxL);

	// Rectangle droit
	tab_sol_arbre_aff[1].position1.x = SIZE_CELL * largeur_labyrinthe;
	tab_sol_arbre_aff[1].position1.z = -LARGEUR_RECT_ARBRE;

	tab_sol_arbre_aff[1].position2.x = SIZE_CELL * largeur_labyrinthe + LARGEUR_RECT_ARBRE;
	tab_sol_arbre_aff[1].position2.z = SIZE_CELL * longueur_labyrinthe + LARGEUR_RECT_ARBRE;

	// Creation des arbres pour ce rectangle
	creation_N_arbre(nb_arbre_long,tab_sol_arbre_aff[1].position1.x + fMinL,tab_sol_arbre_aff[1].position2.x,tab_sol_arbre_aff[1].position1.y,tab_sol_arbre_aff[1].position2.y,tab_sol_arbre_aff[1].position1.z,tab_sol_arbre_aff[1].position2.z,
					tMinB, tMaxB, tMinL, tMaxL, fMinR, fMaxR, fMinL, fMaxL);

	// Rectangle haut
	tab_sol_arbre_aff[2].position1.x = 0;
	tab_sol_arbre_aff[2].position1.z = SIZE_CELL * longueur_labyrinthe;

	tab_sol_arbre_aff[2].position2.x = SIZE_CELL * largeur_labyrinthe;
	tab_sol_arbre_aff[2].position2.z = SIZE_CELL * longueur_labyrinthe + LARGEUR_RECT_ARBRE;

	// Creation des arbres pour ce rectangle
	creation_N_arbre(nb_arbre_larg,tab_sol_arbre_aff[2].position1.x,tab_sol_arbre_aff[2].position2.x,tab_sol_arbre_aff[2].position1.y,tab_sol_arbre_aff[2].position2.y,tab_sol_arbre_aff[2].position1.z + fMinL,tab_sol_arbre_aff[2].position2.z,
					tMinB, tMaxB, tMinL, tMaxL, fMinR, fMaxR, fMinL, fMaxL);

	// Rectangle gauche
	tab_sol_arbre_aff[3].position1.x = -LARGEUR_RECT_ARBRE;
	tab_sol_arbre_aff[3].position1.z = -LARGEUR_RECT_ARBRE;

	tab_sol_arbre_aff[3].position2.x = 0;
	tab_sol_arbre_aff[3].position2.z = SIZE_CELL * longueur_labyrinthe + LARGEUR_RECT_ARBRE;

	// Creation des arbres pour ce rectangle
	creation_N_arbre(nb_arbre_long,tab_sol_arbre_aff[3].position1.x,tab_sol_arbre_aff[3].position2.x - fMinL,tab_sol_arbre_aff[3].position1.y,tab_sol_arbre_aff[3].position2.y,tab_sol_arbre_aff[3].position1.z,tab_sol_arbre_aff[3].position2.z,
					tMinB, tMaxB, tMinL, tMaxL, fMinR, fMaxR, fMinL, fMaxL);

}