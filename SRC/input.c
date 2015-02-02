// Gestion des inputs : Clavier/Souris

#include <stdlib.h>
#include <stdio.h>
#include "GL/glut.h"

#include "input.h"
#include "definition.h"
#include "camera.h"
#include "fct_affichage.h"

void gestionClavierAppuieNormal(unsigned char touche, int x, int y)
{
	switch(touche)
	{
		case 'i' :				if(affiche_information)
								{
									affiche_information = 0;
								}
								else
								{
									affiche_information = 1;
								}
								glutPostRedisplay();
								break;
								
		case 'a' :				touche_pas_cote_gauche = 1;
								break;

		case 'e' :				touche_pas_cote_droite = 1;
								break;

		case 'z' :				touche_avancer = 1;
								break;

		case 's' :				touche_reculer = 1;
								break;

		case 'q' :				touche_tourner_gauche = 1;
								break;

		case 'd' :				touche_tourner_droite = 1;
								break;

		case ' ' :				touche_saute = 1;
								break;

		case 'c':				touche_descend = 1;
								break;
	}
}

void gestionClavierRelacheNormal(unsigned char touche, int x, int y)
{
	switch(touche)
	{
		case 'a' :				touche_pas_cote_gauche = 0;
								break;

		case 'e' :				touche_pas_cote_droite = 0;
								break;

		case 'z' :				touche_avancer = 0;
								break;

		case 's' :				touche_reculer = 0;
								break;

		case 'q' :				touche_tourner_gauche = 0;
								break;

		case 'd' :				touche_tourner_droite = 0;
								break;

		case ' ' :				touche_saute = 0;
								break;

		case 'c':				touche_descend = 0;
								break;
	}
}

void gestionClavierAppuieSpecial(int touche, int x, int y)
{
	switch(touche)
	{
		case GLUT_KEY_F1 :		if(affiche_information)
								{
									affiche_information = 0;
								}
								else
								{
									affiche_information = 1;
								}
								glutPostRedisplay();
								break;
		case GLUT_KEY_F2 :		if(touche_bloquer_camera)
								{
									touche_bloquer_camera = 0;
								}
								else
								{
									touche_bloquer_camera = 1;
								}
								break;
		case GLUT_KEY_F3 :		if(touche_gestion_collision)
								{
									touche_gestion_collision = 0;
									
								}
								else
								{
									touche_gestion_collision = 1;
									
								}
								break;
		case GLUT_KEY_F4 :		if(op_fullscreen)
								{
									op_fullscreen = 0;
								}
								else
								{
									op_fullscreen = 1;
									glutFullScreen();
								}
								break;
		case GLUT_KEY_F8 :		touche_quitter = 1;
								break;
		case GLUT_KEY_LEFT :	touche_pas_cote_gauche = 1;
								break;

		case GLUT_KEY_RIGHT :	touche_pas_cote_droite = 1;
								break;

		case GLUT_KEY_UP :		touche_avancer = 1;
								break;

		case GLUT_KEY_DOWN :	touche_reculer = 1;
								break;
		
		case GLUT_KEY_PAGE_UP :	touche_saute = 1;
								break;

		case GLUT_KEY_PAGE_DOWN:touche_descend = 1;
								break;
	}
}

void gestionClavierRelacheSpecial(int touche, int x, int y)
{
	switch(touche)
	{
		case GLUT_KEY_LEFT :	touche_pas_cote_gauche = 0;
								break;

		case GLUT_KEY_RIGHT :	touche_pas_cote_droite = 0;
								break;

		case GLUT_KEY_UP :		touche_avancer = 0;
								break;

		case GLUT_KEY_DOWN :	touche_reculer = 0;
								break;

		case GLUT_KEY_PAGE_UP :	touche_saute = 0;
								break;

		case GLUT_KEY_PAGE_DOWN:touche_descend = 0;
								break;
	}
}

void gestionSouris(int x, int y)
{
	int xD;
	int yD;
	int mx = longueur_fenetre >> 1;
	int my = largeur_fenetre >> 1;

	if( (x != old_position_souris.x) || (y != old_position_souris.y) )
	{
		xD = old_position_souris.x - x;
		yD = old_position_souris.y - y;

		angleX -= (float)yD * sensibilitee;
		angleY += (float)xD * sensibilitee;
		
		if(angleX > DEF_PI)
		{
			angleX = DEF_PI;
		}
		else if(angleX < 0)
		{
			angleX = 0;
		}
		// 2 Pi
		if(angleY > DEF_DEUX_PI)
		{
			angleY = 0;
		}
		else if(angleY < 0)
		{
			angleY = DEF_DEUX_PI;
		}

		if(touche_bloquer_camera == 0)
		{
			angleY_bloque = angleY;
		}
		
		// Reset souris au milieu de l'écran
		glutWarpPointer(mx,my);
		glutPostRedisplay();
	}
}
