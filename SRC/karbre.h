// Définition des k-arbres

#ifndef _DEFINE_K_ARBRE_H
#define _DEFINE_K_ARBRE_H

#include "definition.h"

/* Init les variables pour le k-arbre
*/
void init_k_arbre();

/* Calcul si il y a collision entre deux rectangles
*/
int collision_rectangle(point p1, float t1h, float t1l, point p2, float t2h, float t2l);

/* Calcule le k-arbre de la map
*  Parametres :	depart : position coin bas gauche pour le calcul du carré
*				taille : taille du carre
*  Retourne : TODO un arbre
*/
noeud_k_arbre calcul_k_arbre(point depart,float taille);

#endif