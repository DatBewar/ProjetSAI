// Gestion de la camera

#include <math.h>

#include "camera.h"
#include "definition.h"

void update_camera()
{
	position_camera.x = position_joueur.x + sin(angleY);
	position_camera.y = position_joueur.y + cos(angleX);
	position_camera.z = position_joueur.z + cos(angleY);

	if(touche_bloquer_camera == 0)
	{
		position_camera_bloque = position_camera;
	}
}