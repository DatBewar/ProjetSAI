#ifdef TEXTURE_N
/* includes */
#include "texture.h"


texture load_image(char * file_name, int size_x, int size_y)
{
	texture text = (texture)malloc(sizeof(struct texture_struct));
	FILE * f = NULL;

	text->pixels = (GLubyte *)malloc(sizeof(GLubyte) * size_x * size_y * 3);

	text->size_x = size_x;
	text->size_y = size_y;

	if((f = fopen(file_name, "rb")) != NULL) 
	{
		/* Chargement du fichier dans la mémoire */
		fread(text->pixels, size_x * size_y * 3, 1, f);
	}
	else
	{
		fprintf(stderr,"[Erreur] lors du chargement de %s.\n", file_name);
		return NULL;
	}

	return text;
}
#endif