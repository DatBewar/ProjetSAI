// Gestion du soleil

#ifndef _DEFINE_SOLEIL_H
#define _DEFINE_SOLEIL_H

/* Retourne le moment de la journée */
int get_moment_journee();

/* Gere la couleur du background selon le soleil
*/
void gestion_jour_nuit();

/* Modifie la position du soleil selon le temps
*/
void update_soleil(float time);

#endif