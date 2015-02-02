// Définition Struct, variable du projet

#include "definition.h"

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/time.h>

void initDefinition()
{
	int cpt;

	strcpy(msg_victoire,"Victoire");

	#ifdef _DEFINE_K_ARBRE_H
	nb_noeud_actif = 0;
	#endif
	taille_carre_principal = 0.0;
	k_arbre_carte = NULL;

	// Init touche
	touche_avancer = 0;
	touche_reculer = 0;
	touche_tourner_droite = 0;
	touche_tourner_gauche = 0;
	touche_pas_cote_droite = 0;
	touche_pas_cote_gauche = 0;
	touche_saute = 0;
	touche_descend = 0;
	touche_gestion_collision = 0;
	touche_quitter = 0;
	affiche_information = 0;
	touche_bloquer_camera = 0;

	// Init Joueur/Objet
	labyrinthe_3d = NULL;
	id_fenetre = 0;

	angleX = DEF_PI_SUR_DEUX;
	angleY = 0.0;

	rotation_soleil_carre = ROTATION_SOLEIL * ROTATION_SOLEIL;
	rotation_soleil_sur_deux = ROTATION_SOLEIL >> 1;

	victoire = 0;
	sensX = 0;
	jour = 1;

	nb_ia_actuel = 0;
	tabIA = NULL;

	position_joueur.x = 5.0;
	position_joueur.y = 10.0;
	position_joueur.z = 5.0;

	position_joueur_bloque = position_joueur;

	position_laby_victoire.x = 0;
	position_laby_victoire.y = 0;
	position_laby_victoire.z = 0;

	position_camera.x = sin(angleY);
	position_camera.y = cos(angleX);
	position_camera.z = cos(angleY);

	position_camera_bloque = position_camera;

	position_soleil.x = sin(angleY);
	position_soleil.y = 1600;
	position_soleil.z = SIZE_CELL * (longueur_labyrinthe>>1);

	position_lune.x = -position_soleil.x;
	position_lune.y = -position_soleil.y;
	position_lune.z = 0.0;

	old_position_souris.x = longueur_fenetre >> 1;
	old_position_souris.y = largeur_fenetre >> 1;
	old_position_souris.z = 0;

	vecteurUp.x = 0.0;
	vecteurUp.y = 1.0;
	vecteurUp.z = 0.0;

	vecteurZ.x = 0.0;
	vecteurZ.y = 0.0;
	vecteurZ.z = 1.0;

	vecteurX.x = 1.0;
	vecteurX.y = 0.0;
	vecteurX.z = 0.0;

	vecteurY.x = 0.0;
	vecteurY.y = 1.0;
	vecteurY.z = 0.0;

	nb_arbre_actuel = 0;
	nb_oiseau_actuel = 0;
	tab_arbre_aff = NULL;

	for(cpt = 0 ; cpt < 4 ; cpt++)
	{
		tab_sol_arbre_aff[cpt].position1.x = 0;
		tab_sol_arbre_aff[cpt].position1.y = 0;
		tab_sol_arbre_aff[cpt].position1.z = 0;

		tab_sol_arbre_aff[cpt].position2.x = 0;
		tab_sol_arbre_aff[cpt].position2.y = 0;
		tab_sol_arbre_aff[cpt].position2.z = 0;
	}

	#ifdef _WIN32
	lastTime = GetTickCount();
	currentTime = 0.0;
	#else
	gettimeofday(&lastTime, NULL);
	currentTime = 0.0;
	#endif

	for(cpt = 0 ; cpt < NB_OISEAUX_MAX ; cpt++)
	{
		tab_oiseau[cpt].etat = 0;
		tab_oiseau[cpt].long_aile = 0.0;
		tab_oiseau[cpt].position.x = 0.0;
		tab_oiseau[cpt].position.y = 0.0;
		tab_oiseau[cpt].position.z = 0.0;
		tab_oiseau[cpt].old_position.x = 0.0;
		tab_oiseau[cpt].old_position.y = 0.0;
		tab_oiseau[cpt].old_position.z = 0.0;
		tab_oiseau[cpt].rotation = 30.0;
		tab_oiseau[cpt].angle = DEF_PI_SUR_DEUX;

		#ifdef _WIN32
		tab_oiseau[cpt].last_time = GetTickCount64();
		#else
		tab_oiseau[cpt].last_time = lastTime.tv_sec*1000;
		#endif
	}
}

point creer_point(float x, float y, float z)
{
	point p;

	p.x = x;
	p.y = y;
	p.z = z;

	return p;
}

point vecteur_positif(point p)
{
	if(p.x < 0)
	{
		p.x = -p.x;
	}
	if(p.y < 0)
	{
		p.y = -p.y;
	}
	if(p.z < 0)
	{
		p.z = -p.z;
	}
	return p;
}

point calcul_vecteur(point p1, point p2)
{
	p1.x -= p2.x;
	p1.y -= p2.y;
	p1.z -= p2.z;

	return p1;
}

point calcul_vectoriel(point p1, point p2)
{
	point p;

	p.x = (p1.y * p2.z) - (p1.z * p2.y);
	p.y = (p1.z * p2.x) - (p1.x * p2.z);
	p.z = (p1.x * p2.y) - (p1.y * p2.x);

	return p;
}
