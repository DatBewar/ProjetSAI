// Gestion des inputs : Clavier/Souris

#ifndef _INPUT_H
#define _INPUT_H

// Gestion des touches appuyées
// Parametres : touche code ASCII touche, x/y emplacement souris
void gestionClavierAppuieNormal(unsigned char touche, int x, int y);

// Gestion des touches relachées
// Parametres : touche code ASCII touche, x/y emplacement souris
void gestionClavierRelacheNormal(unsigned char touche, int x, int y);

// Gestion des touches appuyées code GLUT
// Parametres : touche code GLUT touche, x/y emplacement souris
void gestionClavierAppuieSpecial(int touche, int x, int y);

// Gestion des touches relachées code GLUT
// Parametres : touche code GLUT touche, x/y emplacement souris
void gestionClavierRelacheSpecial(int touche, int x, int y);

// Gestion des mouvements de la souris
// Parametres : x/y emplacement souris
void gestionSouris(int x, int y);

#endif