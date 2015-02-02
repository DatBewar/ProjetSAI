// Fonction d'affichage OpenGL

#ifndef _DEFINE_FCT_AFFICHAGE_H
#define _DEFINE_FCT_AFFICHAGE_H

#include "definition.h"
#include "karbre.h"

/* Trace un rectangle vertical
* Parametres :	x1,y1,z1 : coin bas gauche
*				x2,y2,z2 : coin haut droit
*				tx,ty,tz : vecteur translation
*				color : couleur du rectangle
*/
void trace_face_rectangulaire_vert(float x1, float y1, float z1, float x2, float y2, float z2, float tx, float ty, float tz, float color1, float color2, float color3);

/* Trace un rectangle horizontal
* Parametres :	x1,y1,z1 : coin bas gauche
*				x2,y2,z2 : coin haut droit
*				tx,ty,tz : vecteur translation
*				color : couleur du rectangle
*/
void trace_face_rectangulaire_hori(float x1, float y1, float z1, float x2, float y2, float z2, float tx, float ty, float tz, float color1, float color2, float color3);

/* Trace un rectangle 3d
* Parametres :	x1,y1,z1 : coin avant bas gauche
*				x2,y2,z2 : coin arriere haut droit
*				tx,ty,tz : vecteur translation
*				color : couleur du rectangle 3d
*/
void trace_rectangle_3d(float x1, float y1, float z1, float x2, float y2, float z2, float tx, float ty, float tz, float color1, float color2, float color3);

/* Trace un triangle
* Parametres :	x1,y1,z1 : point haut
*				x2,y2,z2 : point gauche
*				x3,y3,z3 : point droit
*				tx,ty,tz : vecteur translation
*				color : couleur du rectangle 3d
*/
void trace_triangle(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, float tx, float ty, float tz, float color1, float color2, float color3);

/* Trace un cylindre
* Parametres :	rb : rayon base
*				rt : rayon haut
*				h : hauteur
*				nbf : nombre de faces
*				tx,ty,tz : vecteur translation
*				angle,rx,ry,rz : angle de rotation et axe sur lequel effectuer la rotation
*				color : couleur du cylindre
*/
void trace_cylindre(float rb, float rt, float h, int nbf, float tx, float ty, float tz, float angle, float rx, float ry, float rz, float color1, float color2, float color3);

/* Trace un cylindre pour un arbre
* Parametres :	rb : rayon base
*				rt : rayon haut
*				h : hauteur
*				nbf : nombre de faces
*				tx,ty,tz : vecteur translation
*/
void trace_cylindre_arbre(float rb, float rt, float h, int nbf, float tx, float ty, float tz);

/* Trace un cone
* Parametres :	r : rayon
*				h : hauteur
*				nbf : nombre de faces
*				tx,ty,tz : vecteur translation
*				angle,rx,ry,rz : angle de rotation et axe sur lequel effectuer la rotation
*				color : couleur du cylindre
*/
void trace_cone(double r, double h, int nbf, int tx, int ty, int tz, float angle, float rx, float ry, float rz, float color1, float color2, float color3);

/* Trace un cone pour un arbre
* Parametres :	r : rayon
*				h : hauteur
*				nbf : nombre de faces
*				tx,ty,tz : vecteur translation
*/
void trace_cone_arbre(double r, double h, int nbf, int tx, int ty, int tz);

/* Trace une sphere
* Parametres :	r : rayon
*				nbf : nombre de faces
*				tx,ty,tz : vecteur translation
*				color : couleur du cylindre
*/
void trace_sphere(double r, int nbf, int tx, int ty, int tz, float color1, float color2, float color3);

/* Trace une sphere pour un arbre
* Parametres :	r : rayon
*				nbf : nombre de faces
*				tx,ty,tz : vecteur translation
*/
void trace_sphere_arbre(double r, int nbf, int tx, int ty, int tz);

/* Affiche le texte donné
*/
void affichage_texte(char * txt, void* font, float tx, float ty, float tz);

void affichage_msg_victoire();

/* Trace un viseur pour le joueur
*/
void trace_viseur();

/* Affiche les oiseaux
*/
void affichage_oiseaux();

/* Affiche le soleil
*/
void affichage_soleil();

/* Affiche toutes les ia
*/
void affichage_ia();

/* Affiche tous les arbres
*/
void affichage_arbre_3d();

void affiche_opengl_laby(laby l);		/* Affichage du labyrinthe en 3D */

/* Utilisation d'une texture */
void draw_texture(texture t, point p1, point p2, point p3, point p4);
void affiche_facette(point p1, point p2, point p3, point p4, float grey_level, int color, int board);
void affiche_fenetre(point p1, point p2, point p3, point p4, float grey_level, int color, int board);

void draw_gouttes(point p);														/* affichage d'une goutte */
void draw_nuage(nuage * n);														/* Affichage d'un nuage */
void draw_weather(weather w);													/* Affichage du temps */

/* Fonction d'affichage principal
*/
void fct_affichage();

/* Retourne le triangle */
triangle retourne_triangle();
rect transf_triangle(triangle t);
void affiche_rect(rect r);

/* Affiche un noeud du karbre */
void affiche_noeud(noeud_k_arbre n);

/* Affichage avec le 4arbre */
void affiche_karbre();

#endif