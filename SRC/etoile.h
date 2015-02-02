/* Gestion des étoiles dans le jeu */

#include "definition.h"

#ifndef _ETOILES_H_
#define _ETOILES_H_

/* Génération d'une grille d'étoile aléatoire */
etoiles generer_grille_etoile(int nb_etoiles, float x_min, float x_max, float y_min, float y_max, float z_min, float z_max);	/* dans un rectangle englobant */

etoiles genere_grille_etoile_centre(int nb_etoiles, float c_x, float c_y, float c_z, float r_min, float r_max); /* dans une sphère a partir d'un centre */

/* Afficher les étoiles */
void afficher_etoile(etoiles e);

#endif //_ETOILES_H_