// Gestion du soleil

#include <stdlib.h>
#include <math.h>
#include "GL/glut.h"

#include "soleil.h"
#include "definition.h"

int get_moment_journee()
{
	// Dernier quart jour
	if(jour && position_soleil.x < -rotation_soleil_sur_deux)
	{
		return 1;
	}
	// Plein jour
	else if(jour && position_soleil.x < rotation_soleil_sur_deux && position_soleil.x > -rotation_soleil_sur_deux)
	{
		return 2;
	}
	// Premier quart jour
	else if(jour && position_soleil.x > rotation_soleil_sur_deux)
	{
		return 3;
	}
	// Premier quart nuit
	else if(!jour && position_soleil.x < -rotation_soleil_sur_deux)
	{
		return 4;
	}
	// Pleine nuit
	else if(!jour && position_soleil.x < rotation_soleil_sur_deux && position_soleil.x > -rotation_soleil_sur_deux)
	{
		return 5;
	}
	// Dernier quart jour
	else if(!jour && position_soleil.x > rotation_soleil_sur_deux)
	{
		return 6;
	}
	
	return -1;
}

void gestion_jour_nuit()
{
	// Dernier quart jour
	if(jour && position_soleil.x < -rotation_soleil_sur_deux)
	{
		glClearColor(44/(float)0xFF,117/(float)0xFF,255/(float)0xFF,1);
	}
	// Plein jour
	else if(jour && position_soleil.x < rotation_soleil_sur_deux && position_soleil.x > -rotation_soleil_sur_deux)
	{
		glClearColor(119/(float)0xFF,181/(float)0xFF,254/(float)0xFF,1);
	}
	// Premier quart jour
	else if(jour && position_soleil.x > rotation_soleil_sur_deux)
	{
		glClearColor(49/(float)0xFF,140/(float)0xFF,231/(float)0xFF,1);
	}
	// Premier quart nuit
	else if(!jour && position_soleil.x < -rotation_soleil_sur_deux)
	{
		glClearColor(0.0,51/(float)0xFF,102/(float)0xFF,1);
	}
	// Pleine nuit
	else if(!jour && position_soleil.x < rotation_soleil_sur_deux && position_soleil.x > -rotation_soleil_sur_deux)
	{
		glClearColor(15/(float)0xFF,5/(float)0xFF,107/(float)0xFF,1);
	}
	// Dernier quart jour
	else if(!jour && position_soleil.x > rotation_soleil_sur_deux)
	{
		glClearColor(1/(float)0xFF,49/(float)0xFF,180/(float)0xFF,1);
	}
	glutPostRedisplay();
}

void update_soleil(float time)
{
	double y;

	if(sensX)
	{
		position_soleil.x = position_soleil.x + (VITESSE_SOLEIL*time);
		if(position_soleil.x > ROTATION_SOLEIL)
		{
			sensX = 0;

			if(jour)
			{
				jour = 0;
			}
			else
			{
				jour = 1;
			}
		}
	}
	else
	{
		position_soleil.x = position_soleil.x - (VITESSE_SOLEIL*time);
		if(position_soleil.x < -ROTATION_SOLEIL)
		{
			sensX = 1;

			if(jour)
			{
				jour = 0;
			}
			else
			{
				jour = 1;
			}
		}
	}
	y = (double)rotation_soleil_carre - (double)(position_soleil.x*position_soleil.x);
	
	position_soleil.y = sqrt(y);

	if(!jour)
	{
		position_soleil.y = -position_soleil.y;
	}

	position_lune.x = -position_soleil.x;
	position_lune.y = -position_soleil.y;

	gestion_jour_nuit();
}