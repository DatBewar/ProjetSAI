// Définition Struct, variable du projet

#ifndef _DEFINE_DEFINITION_H
#define _DEFINE_DEFINITION_H

#ifdef _WIN32
#include <Windows.h>
#else
#include <time.h>
#include <stdlib.h>
#endif

#include "GL/glut.h"

//////////////////// Structure ///////////////////
// Point
typedef struct struct_point
{
	float x,y,z;
}point;

// Arbre
typedef struct struct_arbre_aff
{
	int type_arbre; // Type d'arbre
	float r_tronc; // Rayon base du tronc
	float l_tronc; // Longueur du tronc
	float r_feuil; // Rayon pour les feuilles
	float l_feuil; // Longueur pour les feuilles
	point position; // Position de l'arbre
}arbre_aff;

// SOL ARBRE
typedef struct struct_sol_arbre_aff
{
	point position1; // Coin bas gauche
	point position2; // coin haut droit
}sol_arbre_aff;

// OISEAU
typedef struct struct_oiseau_aff
{
	point position;
	point position_depart;
	point old_position;
	int etat;
	float vitesse;
	float angle;
	float rotation;
	float long_aile;
	float last_time;
}oiseau_aff;

// IA
typedef struct struct_ia
{
	point position;
	point direction;
	float angleX;
	float angleY;
}ia;

// Définition des strucutres des cellules du labyrinthe

// Définition d'une cellule
struct cell_struct{
	unsigned char			mur;	/* Gestion des murs (ESON) */
	int						val;	/* Sert pour l'algo de génération du labyrinthe */
};

// Typedef d'une cellule
typedef struct cell_struct cell;

// Défénition du labyrinthe
struct laby_struct{
	cell **					cellules;	/* cellules du labyrinthe */
	int						taille_x, taille_y;	/* Taille du labyrinthe */
};

// Typedef du labyrinthe
typedef struct laby_struct * laby;

// Définition des structures des étoiles
typedef struct grille_etoiles_str {
	int			nb_etoiles;	/* Nombre d'étoile contenue */
	point *		etoile;		/* Les étoiles dans un tableau */
} * etoiles;

/* Définition des textures */
typedef struct texture_struct{
	int					size_x, size_y;	/* Taille de la texture */
	GLubyte			*	pixels;		/* Pixels de la texture */
} * texture;

/* Structure de nuage */
typedef struct nuage_struct {
	int					taille_x, taille_y;
	point				position;
	float				vitesse_x, vitesse_z;
	int					type;					/* Nuage blanc, gris ou pluvieux (1,2,3) */
	point *				gouttes;				/* NULL si type != 3 */
	float				rayon;					/* Détermine la grosseurs d'une nuage */
} nuage;

typedef struct weather_struct {
	nuage *				nuages;	/* Liste de nuage */
	float				min_x, min_z;		/* Zone des nuages */
	float				max_x, max_z;		
	int					nb_nuage;	/* Nombre de nuage */
	point *				gouttes;	/* Gouttes */
	int					nb_gouttes;	/* Gestion des gouttes */
} * weather;

/* Structure du k-arbre */
typedef struct struct_k_arbre
{
	int numA;						// Numero de noeud : pour la recuperation de la display liste à afficher
	point p[2];						// P1 : point bas gauche, P2 : point haut droit
	struct struct_k_arbre **fils;
} * noeud_k_arbre;

/* Structure de triangle */
typedef struct triangle_str {
	point p1,p2,p3;
} triangle;

/* Structure de carré */
typedef struct rect_str {
	point p1,p2;
} rect;


//////////////////////////////////////////////////

//////////////////// Define //////////////////////
#define FICHIER_CONFIG "config.cfg"
#define LARGEUR_FENETRE "larg_fen"
#define LONGUEUR_FENETRE "long_fen"
#define LIMITE_FPS "lim_fps"
#define OP_FULLSCREEN "fullscreen"
#define SENSIBILITEE "sens_souris"
#define NOMBRE_IA "nb_ia"
#define LONGUEUR_LABY "long_laby"
#define LARGEUR_LABY "larg_laby"
#define NB_FACETTE_MAX "nb_fac_max"
#define F_O_V "fov"
#define TAILLE_MAX_CHAR 99
#define VITESSE_MOUV 10
#define VITESSE_SOLEIL 20
#define NOMBRE_GOUTTES 100
#define NOMBRE_NUAGES 5
#define ROTATION_SOLEIL 5000
#define NB_ARBRE_MAX 10000
#define NB_TYPE_ARBRE 2
#define NB_OISEAUX_MAX 10
#define NB_ETOILES 100
#define NB_FACE_BOULE_ARBRE 20
#define NB_FACE_CONE_ARBRE 15
#define NB_FACE_TRONC_ARBRE 15
#define NB_FACE_MUR 10
#define LARGEUR_RECT_ARBRE 7000
#define DISTANCE_VUE 5000
#define DEF_PI 3.141592
#define DEF_DEUX_PI 6.28318
#define DEF_PI_SUR_DEUX 1.57079
#define DEF_TROIS_PI_SUR_DEUX 4.71238

/* Defined de tracage labyrinthe */
#define SIZE_WALL			16	/* Hauteur des murs */
#define SIZE_CELL			30	/* Largeur/Longueur d'une cellule */
//////////////////////////////////////////////////

/////////////////// Configuration ////////////////
int largeur_fenetre;
int longueur_fenetre;
int limite_fps;
int op_fullscreen;
float sensibilitee;
int nb_ia;
int longueur_labyrinthe;
int largeur_labyrinthe;
int nb_fac_max;
int fov;
//////////////////////////////////////////////////

//////////////////// Clavier/Souris //////////////
int touche_avancer;
int touche_reculer;
int touche_tourner_droite;
int touche_tourner_gauche;
int touche_pas_cote_droite;
int touche_pas_cote_gauche;
int touche_saute;
int touche_descend;
int touche_gestion_collision;
int touche_quitter;
int affiche_information;
int touche_bloquer_camera;
//////////////////////////////////////////////////

//////////////////// Joueur/Objet ////////////////
int id_fenetre;
laby labyrinthe_3d;
point position_joueur;
point position_joueur_bloque;
point position_camera;
point position_camera_bloque;
ia *tabIA;
int victoire;
point old_position_souris;
point position_soleil;
point position_lune;
point position_laby_victoire;
point vecteurUp;
point vecteurZ;
point vecteurX;
point vecteurY;
float angleX;
float angleY;
float angleY_bloque;
float rotation_soleil_carre;
float rotation_soleil_sur_deux;
int sensX;
int jour;
int nb_ia_actuel;
int nb_arbre_actuel;
int nb_oiseau_actuel;
arbre_aff *tab_arbre_aff;
sol_arbre_aff tab_sol_arbre_aff[4];
oiseau_aff tab_oiseau[NB_OISEAUX_MAX];
etoiles grille_etoiles;
weather w;
float taille_carre_principal;
noeud_k_arbre k_arbre_carte;
#ifdef _DEFINE_K_ARBRE_H
static int nb_noeud_actif;
#endif
char msg_victoire[20];
//////////////////////////////////////////////////

////////////////// Temps pour le calcul des mouvements
#ifdef _WIN32
double lastTime;
#else
struct timeval lastTime;
#endif
double currentTime;
//////////////////////////////////////////////////

// Initialisation de toutes les variables par defaults
void initDefinition();

// Point
point creer_point(float x, float y, float z);

// Calcul sur les vecteurs
point vecteur_positif(point p);
point calcul_vecteur(point p1, point p2);
point calcul_vectoriel(point p1, point p2);

#endif
