/****************************************
 * Gestion du labyrinthe : 	-génération	*
 *										*
 * Auteurs :	-CROZE Erwan			*
 *				-DESHORS Axel			*
 * Date :	-27/03/2014					*
 ****************************************/

#ifndef _LABY_H_
#define _LABY_H_

#include "definition.h"

/* Fonctions : */

/* génération de labyrinthe */
laby 			creer_laby(int size_x, int size_y);				/* Allocation mémoire d'un labyrinthe de taille : largeur size_x et hauteur size_y */
laby			creer_labyrinthe(int largeur, int hauteur);		/* Création aléatoire d'un labyrinthe */


cell * 			return_cell(laby l, int x, int y);						/* Retourne une cellule retourne NULL si la cellule n'existe pas */

/* Affichage de labyrinthe */

void			affiche_term_laby(laby l); 	/* Affichage du labyrithe en mode console */

/* Gestion des collisions */
/* Retourne 1 si collision, 0 sinon */
/* Version 2 : gère la bounding box de l'entitée (la position est centrale par rapport a la bounding box) */
int				collide(laby l, float pos_x, float pos_z, float f_pos_x, float f_pos_z, float bounding_x, float bounding_z);	/* Gestion des collisions (pos_x/pos_y) = position caméra, (f_pos_x/f_pos_z) = futur position de caméra */ 

#endif /* _LABY_H_ */
