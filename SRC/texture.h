/* Gestion des textures (load) */
/* Compatible opengl */

#ifdef TEXTURE_N
#ifndef _TEXTURES_H_
#define _TEXTURES_H_

/* stdlib */
#include <stdio.h>
#include <stdlib.h>

/* Include opengl */
#include "GL/glut.h"

/* Define texture */
#include "definition.h"

/* Chargement de textures */
texture			load_image(char * file_name, int size_x, int size_y);	/* Mise en mémoire d'une image .RAW (avec spécification de la taille) */

#endif /* _TEXTURES_H_ */
#endif
