// Gestion de l'oiseau

#include <stdio.h>
#include <math.h>
#include <sys/time.h>

#include "oiseau.h"

#include "definition.h"

void creation_N_Oiseau_Alea(int nb, float long_ois_max, float long_ois_min, float vit_max, float vit_min, float rot_max, float rot_min, float xmax, float xmin, float ymax, float ymin, float zmax, float zmin)
{
	int test;
	float x,y,z,lo,vo,ro;
	int cpt = 0;

	#ifdef _WIN32
	float t1 = GetTickCount64();
	#else
	struct timeval t;
	gettimeofday(&t, NULL);
	float t1 = t.tv_usec * t.tv_sec;
	#endif

	srand(t1);

	while(cpt < nb && cpt < NB_OISEAUX_MAX)
	{
		x=0;y=0;z=0;

		if(nb_oiseau_actuel < NB_OISEAUX_MAX)
		{
			// Aile
			if(long_ois_max == 0 && long_ois_min == 0)
			{
				lo = 0.f;
			}
			else
			{
				lo = rand()%(int)(long_ois_max-long_ois_min)+long_ois_min;
			}
			// Vitesse
			if(vit_max == 0 && vit_min == 0)
			{
				vo = 0.f;
			}
			else
			{
				vo = rand()%(int)(vit_max-vit_min)+vit_min;
				vo = vo/10000.f;
			}	
			// Rotation
			if(rot_min == 0 && rot_max == 0)
			{
				ro = 0.f;
			}
			else
			{
				ro = rand()%(int)(rot_max-rot_min)+rot_min;
			}

			// Position X
			if(xmin == 0 && xmax == 0)
			{
				x = 0;
			}
			else
			{
				test = rand()%20;
				x = rand()%(int)(xmax-xmin)+xmin;
				if(test < 10)
				{
					x = -x;
				}
			}
			// Position Y
			if(ymin == 0 && ymax == 0)
			{
				y = 0;
			}
			else
			{
				y = rand()%(int)(ymax-ymin)+ymin;
			}
			// Position Z
			if(zmin == 0 && zmax == 0)
			{
				z = 0;
			}
			else
			{
				test = rand()%20;
				z = rand()%(int)(zmax-zmin)+zmin;
				if(test < 10)
				{
					z = -z;
				}
			}

			if(ajoutOiseau(cpt, lo, vo, ro, x, y, z) == 1)
			{
				nb_oiseau_actuel++;
			}
		}

		cpt++;
	}

}

int ajoutOiseau(int num, float long_ois, float vit, float rot, float x, float y, float z)
{
	if(num < NB_OISEAUX_MAX && long_ois > 5)
	{
		tab_oiseau[num].long_aile = long_ois;

		tab_oiseau[num].position.x = x;
		tab_oiseau[num].position.y = y;
		tab_oiseau[num].position.z = z + long_ois;

		tab_oiseau[num].old_position.x = tab_oiseau[num].position.x;
		tab_oiseau[num].old_position.y = tab_oiseau[num].position.y;
		tab_oiseau[num].old_position.z = tab_oiseau[num].position.z;

		tab_oiseau[num].position_depart.x = tab_oiseau[num].position.x;
		tab_oiseau[num].position_depart.y = tab_oiseau[num].position.y;
		tab_oiseau[num].position_depart.z = tab_oiseau[num].position.z;
		
		tab_oiseau[num].vitesse = vit;

		if(rot > 20)
		{
			tab_oiseau[num].rotation = rot;
		}

		if(nb_oiseau_actuel < num)
		{
			nb_oiseau_actuel = num+1;
			return 1;
		}
	}
	return 0;
}

void gestionOiseau()
{
	int cpt;

	for( cpt = 0 ; cpt < nb_oiseau_actuel ; cpt++)
	{
		gestionOiseauNum(cpt);
	}
}

void gestionOiseauNum(int num)
{
	if(num < NB_OISEAUX_MAX)
	{
		if(tab_oiseau[num].long_aile != 0)
		{
			#ifdef _WIN32
			float t1 = GetTickCount64();
			#else
			struct timeval t;
			gettimeofday(&t, NULL);
			float t1 = t.tv_sec*1000;
			#endif

			if((t1 - tab_oiseau[num].last_time) > 1000.0)
			{
				if(tab_oiseau[num].etat)
				{
					tab_oiseau[num].etat = 0;
				}
				else
				{
					tab_oiseau[num].etat = 1;
				}
				#ifdef _WIN32
				tab_oiseau[num].last_time = t1;
				#else
				tab_oiseau[num].last_time = t.tv_sec*1000;
				#endif
			}

			tab_oiseau[num].old_position.x = tab_oiseau[num].position.x;
			tab_oiseau[num].old_position.z = tab_oiseau[num].position.z;

			tab_oiseau[num].angle += tab_oiseau[num].vitesse;

			if(tab_oiseau[num].angle > DEF_DEUX_PI)
			{
				tab_oiseau[num].angle = 0.0;
			}
			else if( tab_oiseau[num].angle < 0.0)
			{
				tab_oiseau[num].angle = DEF_DEUX_PI;
			}

			tab_oiseau[num].position.x = tab_oiseau[num].position_depart.x + tab_oiseau[num].rotation * sin(tab_oiseau[num].angle);
			tab_oiseau[num].position.z = tab_oiseau[num].position_depart.z + tab_oiseau[num].rotation * cos(tab_oiseau[num].angle);

		}
	}
}
