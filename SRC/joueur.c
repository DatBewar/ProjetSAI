// Gestion Joueur

#include <stdlib.h>
#include <math.h>
#include "GL/glut.h"

#include "joueur.h"

#include "labyrinthe.h"
#include "definition.h"

void mouvement_joueur(float time)
{
	point p;
	point futur;
	int mouv = 0;

	futur.x = position_joueur.x;
	futur.y = position_joueur.y;
	futur.z = position_joueur.z;

	if(touche_pas_cote_gauche && touche_avancer)
	{
		futur.x = position_joueur.x + (VITESSE_MOUV*time)*sin(angleY);
		futur.z = position_joueur.z + (VITESSE_MOUV*time)*cos(angleY);

		p = calcul_vectoriel(calcul_vecteur(position_camera,futur),vecteurUp);
		futur.x -= p.x * (VITESSE_MOUV*time);
		futur.z -= p.z * (VITESSE_MOUV*time);
		mouv = 1;
	}
	else if(touche_pas_cote_gauche && touche_reculer)
	{
		futur.x = position_joueur.x - (VITESSE_MOUV*time)*sin(angleY);
		futur.z = position_joueur.z - (VITESSE_MOUV*time)*cos(angleY);

		p = calcul_vectoriel(calcul_vecteur(position_camera,futur),vecteurUp);
		futur.x -= p.x * (VITESSE_MOUV*time);
		futur.z -= p.z * (VITESSE_MOUV*time);
		mouv = 1;
	}
	else if(touche_pas_cote_droite && touche_avancer)
	{
		futur.x = position_joueur.x + (VITESSE_MOUV*time)*sin(angleY);
		futur.z = position_joueur.z + (VITESSE_MOUV*time)*cos(angleY);

		p = calcul_vectoriel(calcul_vecteur(position_camera,futur),vecteurUp);
		futur.x += p.x * (VITESSE_MOUV*time);
		futur.z += p.z * (VITESSE_MOUV*time);
		mouv = 1;
	}
	else if(touche_pas_cote_droite && touche_reculer)
	{
		futur.x = position_joueur.x - (VITESSE_MOUV*time)*sin(angleY);
		futur.z = position_joueur.z - (VITESSE_MOUV*time)*cos(angleY);

		p = calcul_vectoriel(calcul_vecteur(position_camera,futur),vecteurUp);
		futur.x += p.x * (VITESSE_MOUV*time);
		futur.z += p.z * (VITESSE_MOUV*time);
		mouv = 1;
	}
	else
	{
		if(touche_avancer)
		{
			futur.x = position_joueur.x + (VITESSE_MOUV*time)*sin(angleY);
			futur.z = position_joueur.z + (VITESSE_MOUV*time)*cos(angleY);
			mouv = 1;
		}
		else if(touche_reculer)
		{
			futur.x = position_joueur.x -(VITESSE_MOUV*time)*sin(angleY);
			futur.z = position_joueur.z -(VITESSE_MOUV*time)*cos(angleY);
			mouv = 1;
		}

		if(touche_tourner_droite)
		{
			angleY -= sensibilitee*10;
			// 2 Pi
			if(angleY < 0)
			{
				angleY = DEF_DEUX_PI;
			}
			glutPostRedisplay();
		}
		else if(touche_tourner_gauche)
		{
			angleY += sensibilitee*10;
			// 2 Pi
			if(angleY > DEF_DEUX_PI)
			{
				angleY = 0;
			}
			glutPostRedisplay();
		}

		if(touche_pas_cote_gauche)
		{
			p = calcul_vectoriel(calcul_vecteur(position_camera,futur),vecteurUp);
			futur.x = position_joueur.x - p.x * (VITESSE_MOUV*time);
			futur.z = position_joueur.z - p.z * (VITESSE_MOUV*time);
			mouv = 1;
		}
		else if(touche_pas_cote_droite)
		{
			p = calcul_vectoriel(calcul_vecteur(position_camera,futur),vecteurUp);
			futur.x = position_joueur.x + p.x * (VITESSE_MOUV*time);
			futur.z = position_joueur.z + p.z * (VITESSE_MOUV*time);
			mouv = 1;
		}
	}

	if(touche_gestion_collision)
	{
		if(touche_saute)
		{
			position_joueur.y += (VITESSE_MOUV*time);
			glutPostRedisplay();
		}
		else if(touche_descend)
		{
			position_joueur.y -= (VITESSE_MOUV*time);
			if(position_joueur.y < 10.0)
			{
				position_joueur.y = 10.0;
			}
			glutPostRedisplay();
		}

		position_joueur.x = futur.x;
		position_joueur.z = futur.z;

		glutPostRedisplay();
	}
	else if(mouv && !collide(labyrinthe_3d,position_joueur.x,position_joueur.z,futur.x,futur.z, 1.0,1.0))
	{
		position_joueur.x = futur.x;
		position_joueur.z = futur.z;

		glutPostRedisplay();
	}

	if(touche_bloquer_camera == 0)
	{
		position_joueur_bloque = position_joueur;
	}

}
