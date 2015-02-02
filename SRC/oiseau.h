// Gestion de l'oiseau

#ifndef _DEFINE_OISEAU_H
#define _DEFINE_OISEAU_H

/* Creer un nombre definit dans la limite du possible d'oiseau selon les données indiquées
* Parametres :	nb nombre d'oiseaux voulu
*				long_ois : longueur des ailes
*				vit : vitesse de l'oiseau
*				rot : rayon de rotation
*				x,y,z : position
*/
void creation_N_Oiseau_Alea(int nb, float long_ois_max, float long_ois_min, float vit_max, float vit_min, float rot_max, float rot_min, float xmax, float xmin, float ymax, float ymin, float zmax, float zmin);

/* Ajoute ou modifie l'oiseau indiqué
* Parametre :	num(numero d'oiseau)
*				long_ois(longueur des ailes de l'oiseau)
*				x,y,z(position de l'oiseau
* Retourne 1 si on vient d'ajouter un oiseau, 0 sinon
*/
int ajoutOiseau(int num, float long_ois, float vit, float rot, float x, float y, float z);

/* Gere les deplacements de tous les oiseaux
*/
void gestionOiseau();

/* Gere le deplacement de l'oiseau num
* Parametre :	num(numero d'oiseau)
*/
void gestionOiseauNum(int num);

#endif