#include "etoile.h"

/* stdlib */
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

/* tracage */
#include "soleil.h"
#include "fct_affichage.h"

etoiles generer_grille_etoile(int nb_etoiles, float x_min, float x_max, float y_min, float y_max, float z_min, float z_max)
{
	etoiles e = (etoiles)malloc(sizeof(struct grille_etoiles_str));
	int i;

	srand(time(NULL));

	e->nb_etoiles = nb_etoiles;

	e->etoile = (point *)malloc(sizeof(struct struct_point) * nb_etoiles);

	// Boucle de création des étoiles
	for (i = 0; i < nb_etoiles; i++)
	{
		// On génère une étoile aléatoire 
		e->etoile[i] = creer_point(rand() % (int)(x_max - x_min) + x_min, rand() % (int)(y_max - y_min) + y_min, rand() % (int)(z_max -z_min) + z_min);
	}

	return e;
}

etoiles genere_grille_etoile_centre(int nb_etoiles, float c_x, float c_y, float c_z, float r_min, float r_max)
{
	etoiles e = (etoiles)malloc(sizeof(struct grille_etoiles_str));
	int i;

	float x, y, z;

	srand(time(NULL));

	e->nb_etoiles = nb_etoiles;

	e->etoile = (point *)malloc(sizeof(struct struct_point) * nb_etoiles);

	// Boucle de création des étoiles
	for (i = 0; i < nb_etoiles; i++)
	{
		/* Calcul de la distance de l'étoile par rapport au centre */
		float rad = rand()%(int)(r_max - r_min) + r_min;
		float alpha = rand()%(int)180;
		float beta = rand()%(int)360;

		x = rad * cos(alpha);
		y = rad * sin(alpha);
		z = rad * cos(beta);

		if (y < 0)
			y = -y;

		e->etoile[i] = creer_point(x + c_x, y + c_y ,z + c_z);
	}

	return e;
}

void afficher_etoile(etoiles e)
{
	int journee = get_moment_journee();
	int i = 0;

	if (e == NULL)
		return;

	if (journee == 4 || journee == 5 || journee == 6)
	{
		for (i = 0; i < e->nb_etoiles; i++)
		{
			trace_sphere(3,5,e->etoile[i].x, e->etoile[i].y,e->etoile[i].z,255,255,255);
		}
	}
}