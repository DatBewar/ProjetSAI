#include "nuage.h"

/* stdlib */
#include <stdlib.h>
#include <time.h>

#include "fct_affichage.h"

void ajouter_goute(weather w, float x, float y, float z)
{
	int i;
	for (i = 0; i < w->nb_gouttes; i++)
	{
		if (w->gouttes[i].y <= 0)
		{
			w->gouttes[i] = creer_point(x,y,z);
			return;	/* Sortie de la fonction */
		}

	}
}

weather create_weather(int nb_nuages, float height_min, float height_max, int taille_min, int taille_max, float rayon, float min_x, float min_z, float max_x, float max_z)
{
	weather w = (weather)malloc(sizeof(struct weather_struct));
	int i = 0;

	srand(time(NULL));

	/* min et max */
	w->min_x = min_x;
	w->max_x = max_x;
	w->min_z = min_z;
	w->max_z = max_z;

	w->nb_nuage = nb_nuages;
	w->nuages = (nuage *)malloc(sizeof(nuage) * nb_nuages);

	w->nb_gouttes = NOMBRE_GOUTTES;
	w->gouttes = (point *)malloc(sizeof(point) * w->nb_gouttes);

	/* init des gouttes */
	for (i = 0; i < w->nb_gouttes; i++)
	{
		w->gouttes[i].y = 0;
	}
	/* Définition aléatoire */
	for (i = 0; i < nb_nuages; i++)
	{
		w->nuages[i].type = rand()%2;

		w->nuages[i].taille_x = rand()%(int)(taille_max - taille_min) + taille_min;
		w->nuages[i].taille_y = rand()%(int)(taille_max - taille_min) + taille_min;

		w->nuages[i].position.y = rand()%(int)(height_max - height_min) + height_min;
		w->nuages[i].rayon = rand()%10 + 10;


		/* gestion des x/z */
		w->nuages[i].position.x = rand()%(int)(max_x - min_x) + min_x;
		w->nuages[i].position.z = rand()%(int)(max_z - min_z) + min_z;

		w->nuages[i].vitesse_x = rand()%10 - 2;

		if (w->nuages[i].vitesse_x < 2 && w->nuages[i].vitesse_x > 0)
			w->nuages[i].vitesse_x = 2;
		else if (w->nuages[i].vitesse_x > -2 && w->nuages[i].vitesse_x < 0)
			w->nuages[i].vitesse_x = -2;

		w->nuages[i].vitesse_z =  rand()%10;


	}

	return w;
}

void update_weather(weather w, float time_h)
{
	int i = 0;

	for (i = 0; i < w->nb_nuage; i++)
	{
		w->nuages[i].position.x += w->nuages[i].vitesse_x * time_h;
		w->nuages[i].position.z += w->nuages[i].vitesse_z * time_h;

		/*  téléportation si les nuages sont au bout */
		if (w->nuages[i].position.x > w->max_x)
			w->nuages[i].position.x = w->min_x;
		else if (w->nuages[i].position.x < w->min_x)
			w->nuages[i].position.x = w->max_x;
		else if (w->nuages[i].position.z > w->max_z)
			w->nuages[i].position.z = w->min_z;
		else if (w->nuages[i].position.z < w->min_z)
			w->nuages[i].position.z = w->max_z;

		/* Gestion des gouttes */

		if (w->nuages[i].type == 1)
		{
			/* chance d'ajouter une goutte */
			if ((rand()%10) == 1)
			{
				float x = (rand()%(int)(w->nuages[i].taille_x * 2) - w->nuages[i].taille_x) * (w->nuages[i].rayon / 2);
				float z = (rand()%(int)w->nuages[i].taille_y) * (w->nuages[i].rayon / 2);
				ajouter_goute(w, w->nuages[i].position.x + x, w->nuages[i].position.y, w->nuages[i].position.z + z);
			}
		}
	}

	for (i = 0; i < w->nb_gouttes; i++)
	{
		if (w->gouttes[i].y > 0)
			w->gouttes[i].y -= 50 * time_h;
	}
}