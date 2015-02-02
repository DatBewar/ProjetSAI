// Gestion arbre

#ifndef _DEFINE_ARBRE_H
#define _DEFINE_ARBRE_H

/* Vérifie si à la position et les informations données il y a intersection avec un autre arbre
* Parametres :	X,Y,Z, Position
*				rayon, rayon du feuillage de l'arbre
*				longut, longueur du tronc de l'arbre
*				longuf, longueur du feuillage de l'arbre
* Renvoie 1 si un arbre intersecte avec les données indiquées
*/
int arbre_a_distance(float x, float y, float z, int rayon, int longut, int longuf);

/* Génération aléatoire des arbres par rapport à des bornes
* Parametres : 	X,Y,Z Quadrilatere d'emplacement
*		tB taille de la base du tronc
*		tL longueur du tronc
*		fR rayon du feuillage
*		fL longueur du feuillage
*/
void creation_arbre_alea(float rMinX, float rMaxX, float rMinY, float rMaxY, float rMinZ, float rMaxZ, float tMinB, float tMaxB, float tMinL, float tMaxL, float fMinR, float fMaxR, float fMinL, float fMaxL);

/* Creation de N arbre aleatoire
*/
void creation_N_arbre(int nbA, float rMinX, float rMaxX, float rMinY, float rMaxY, float rMinZ, float rMaxZ, float tMinB, float tMaxB, float tMinL, float tMaxL, float fMinR, float fMaxR, float fMinL, float fMaxL);

/* Creation des rectangles d'arbre entourant le labyrinthe
*/
void creation_rectangle_arbre_laby(float tMinB, float tMaxB, float tMinL, float tMaxL, float fMinR, float fMaxR, float fMinL, float fMaxL);

#endif