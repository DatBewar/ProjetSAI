/* Gestion des nuages dans le jeu */


#ifndef _NUAGE_H_
#define _NUAGE_H_

#include "definition.h"

weather create_weather(int nb_nuages, float height_min, float height_max, int taille_min, int taille_max, float rayon, float min_x, float min_z, float max_x, float max_z);		/* génère un temps aléatoire */

void update_weather(weather w, float time_h);									/* Update du temps */
#endif
