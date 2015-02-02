// Test fonctions bases OpenGl

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "GL/glut.h"

#include "definition.h"

#include "config.h"
#include "camera.h"
#include "input.h"
#include "fct_affichage.h"
#include "arbre.h"
#include "joueur.h"
#include "ia.h"
#include "soleil.h"
#include "oiseau.h"
#include "labyrinthe.h"
#include "etoile.h"
#include "nuage.h"
#include "karbre.h"

void verification_victoire()
{
	if((position_joueur.x > position_laby_victoire.x && position_joueur.z > position_laby_victoire.z ) &&
		(position_joueur.x < position_laby_victoire.x + SIZE_CELL && position_joueur.z < position_laby_victoire.z + SIZE_CELL))
	{
		if(victoire == 0)
		{
			fprintf(stderr,"Victoire !\n");
		}
		victoire = 1;
	}
}

void loop()
{
	if(touche_quitter)
	{
		// On détruit la fenetre
		glutDestroyWindow(id_fenetre);
		exit(EXIT_SUCCESS);
	}
	else
	{
		#ifdef _WIN32
		DWORD time_now;
		time_now = GetTickCount();
		
		if((time_now - lastTime) != 0)
		{
			currentTime = (float) (time_now - lastTime) / 1000.0;
		}
		#else
		struct timeval time_now;
		gettimeofday(&time_now, NULL);
		if((time_now.tv_sec  - lastTime.tv_sec) > 0)
		{
			currentTime = (time_now.tv_sec  - lastTime.tv_sec)*1000 + (time_now.tv_usec - lastTime.tv_usec)/1000;
		}
		currentTime = 0.1;
		#endif

		// Mouvement joueur
		mouvement_joueur(currentTime);
		//mouvement_IA(currentTime,0);
		gestionOiseau();
		update_camera();
		
		update_soleil(currentTime);
		update_weather(w, currentTime);

		verification_victoire();

		lastTime = time_now;
	}
}

/* Gestion des events si la fenetre est visible ou non
*/
void visibilite(int state)
{
	if(state == GLUT_VISIBLE)
	{
		glutIdleFunc(&loop);
		glutKeyboardFunc(&gestionClavierAppuieNormal);
		glutKeyboardUpFunc(&gestionClavierRelacheNormal);
		glutSpecialFunc(&gestionClavierAppuieSpecial);
		glutSpecialUpFunc(&gestionClavierRelacheSpecial);
		glutPassiveMotionFunc(&gestionSouris);
	}
	else
	{
		glutIdleFunc(NULL);
		glutKeyboardFunc(NULL);
		glutKeyboardUpFunc(NULL);
		glutSpecialFunc(NULL);
		glutSpecialUpFunc(NULL);
		glutPassiveMotionFunc(NULL);
	}
}

int main(int argc, char** argv)
{
	// Chargement de la config
	loadFichierConfig();
	saveFichierConfig();

	// Init
	initDefinition();
	initIA();

	creation_N_Oiseau_Alea(8,50,8,10,1,100,1200,-(SIZE_CELL*20),(SIZE_CELL*longueur_labyrinthe)+(SIZE_CELL*5),SIZE_WALL+20,200,-(SIZE_CELL*20),(SIZE_CELL*largeur_labyrinthe)+(SIZE_CELL*5));

	// Initialisation de Glut
	glutInit(&argc, argv);

	// Initialisation du mode d'affichage de Glut
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_ALPHA);

	// Initialisation des données de la fenetre
	glutInitWindowSize(longueur_fenetre,largeur_fenetre);
	glutInitWindowPosition(50,50);
	
	// Creation de la fenetre
	id_fenetre = glutCreateWindow("Projet SAI");
	glutWindowStatusFunc(visibilite);

	glEnable(GL_DEPTH_TEST);
	glutSetCursor(GLUT_CURSOR_NONE);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Définition de la zone visible
	gluPerspective(fov,longueur_fenetre/largeur_fenetre, 0.1, DISTANCE_VUE);

	// Affichage
	glutDisplayFunc(&fct_affichage);
	if(op_fullscreen)
	{
		glutFullScreen();
	}

	// Gestion clavier
	glutKeyboardFunc(&gestionClavierAppuieNormal);
	glutKeyboardUpFunc(&gestionClavierRelacheNormal);
	glutSpecialFunc(&gestionClavierAppuieSpecial);
	glutSpecialUpFunc(&gestionClavierRelacheSpecial);

	// Gestion souris
	glutWarpPointer(old_position_souris.x,old_position_souris.y);
	glutPassiveMotionFunc(&gestionSouris);
	
	// Boucle de jeu
	glutIdleFunc(&loop);

	fprintf(stderr,"Chargement ...\n");

	// Init labyrinthe
	labyrinthe_3d = creer_labyrinthe(largeur_labyrinthe,longueur_labyrinthe);

	// Creation de l'environnement
	creation_rectangle_arbre_laby( 3, 5, 10, 20, 10, 20, 30, 60);
	grille_etoiles = genere_grille_etoile_centre(NB_ETOILES, (labyrinthe_3d->taille_x * SIZE_CELL)/2,0, (labyrinthe_3d->taille_y * SIZE_CELL)/2,35 * SIZE_CELL, 60 * SIZE_CELL);
	w = create_weather(NOMBRE_NUAGES, 200,300, 4,10, 10, -(labyrinthe_3d->taille_x * SIZE_CELL) / 2, -(labyrinthe_3d->taille_y * SIZE_CELL) / 2, (labyrinthe_3d->taille_x * SIZE_CELL) + ( (labyrinthe_3d->taille_x * SIZE_CELL) / 2) , (labyrinthe_3d->taille_x * SIZE_CELL) + ( (labyrinthe_3d->taille_x * SIZE_CELL) / 2));

	// Creation de l'arbre
	init_k_arbre();

	glutMainLoop();

	return 1;
}
