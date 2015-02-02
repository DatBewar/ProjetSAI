// Gestion des IA

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include <time.h>
#include <math.h>
#include "GL/glut.h"

#include "ia.h"
#include "definition.h"

void initIA()
{
	int cpt;

	tabIA = (ia*)malloc(sizeof(ia)*nb_ia);

	for(cpt = 0 ; cpt < nb_ia ; cpt++)
	{
		tabIA[cpt].position.x = 0;
		tabIA[cpt].position.y = 0;
		tabIA[cpt].position.z = 0;
		tabIA[cpt].direction.x = -1;
		tabIA[cpt].direction.y = 0;
		tabIA[cpt].direction.z = 0;
		tabIA[cpt].angleX = 0;
		tabIA[cpt].angleY = 0;
	}

	#ifdef _WIN32
	time_last_ia = GetTickCount64();
	#else
	struct timeval t;
	gettimeofday(&t, NULL);
	time_last_ia = t.tv_sec*1000;
	#endif
}

void init_Pos_IA()
{

}

void mouvement_IA(float time, int num_ia)
{
	int mouv;

	if(num_ia < nb_ia)
	{
		#ifdef _WIN32
		float t1 = GetTickCount64();
		#else
		struct timeval t;
		gettimeofday(&t, NULL);
		float t1 = t.tv_sec*1000;
		#endif

		if((t1 - time_last_ia) > 2000.0)
		{
			#ifndef _WIN32
			struct timeval t;
			gettimeofday(&t, NULL);
			float t1 = (t.tv_usec/1000) + t.tv_sec*1000;
			#endif

			srand(t1);

			mouv = rand()%4;

			tabIA[num_ia].direction.x = tabIA[num_ia].position.x;
			tabIA[num_ia].direction.y = tabIA[num_ia].position.y;
			tabIA[num_ia].direction.z = tabIA[num_ia].position.z;

			switch(mouv)
			{
				// Avance
				case 0 :	tabIA[num_ia].position.x += (VITESSE_MOUV*time)*sin(tabIA[num_ia].angleY);
							tabIA[num_ia].position.z += (VITESSE_MOUV*time)*cos(tabIA[num_ia].angleY);
							fprintf(stderr,"ia avance\n");
							break;
				// Recule
				case 1 :	tabIA[num_ia].angleY += DEF_PI;
							if(tabIA[num_ia].angleY > DEF_DEUX_PI)
							{
								tabIA[num_ia].angleY = 0;
							}
							tabIA[num_ia].position.x += (VITESSE_MOUV*time)*sin(tabIA[num_ia].angleY);
							tabIA[num_ia].position.z += (VITESSE_MOUV*time)*cos(tabIA[num_ia].angleY);
							fprintf(stderr,"ia demi tour\n");
							break;
				// Pas à gauche
				case 2 :	tabIA[num_ia].angleY += DEF_PI_SUR_DEUX;
							if(tabIA[num_ia].angleY > DEF_DEUX_PI)
							{
								tabIA[num_ia].angleY = 0;
							}
							tabIA[num_ia].position.x += (VITESSE_MOUV*time)*sin(tabIA[num_ia].angleY);
							tabIA[num_ia].position.z += (VITESSE_MOUV*time)*cos(tabIA[num_ia].angleY);
							fprintf(stderr,"ia direction gauche\n");
							break;
				// Pas à droite
				case 3 :	tabIA[num_ia].angleY += 3*DEF_PI_SUR_DEUX;
							if(tabIA[num_ia].angleY > DEF_DEUX_PI)
							{
								tabIA[num_ia].angleY = 0;
							}
							tabIA[num_ia].position.x += (VITESSE_MOUV*time)*sin(tabIA[num_ia].angleY);
							tabIA[num_ia].position.z += (VITESSE_MOUV*time)*cos(tabIA[num_ia].angleY);
							fprintf(stderr,"ia direction droite\n");
							break;
			}

			glutPostRedisplay();

			#ifdef _WIN32
			time_last_ia = t1;
			#else
			time_last_ia = t.tv_sec * 1000;
			#endif
		}
	}
}
