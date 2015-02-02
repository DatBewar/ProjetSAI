/* Include */
#include "labyrinthe.h"

/* libstd */
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/* opengl */
#include <GL/glut.h>

/* Allocation mémoire d'un labyrinthe */
laby creer_laby(int size_x, int size_y)
{
	int i = 0;

	laby l = (laby)malloc(sizeof(struct laby_struct));

	/* Création des cellules du tableau */
	cell ** tab = (cell **)malloc(sizeof(cell *) * size_y);
	cell * tab2 = (cell *)malloc(sizeof(cell) * size_x * size_y);

	while (i < size_y)
	{
		tab[i] = &tab2[i * size_y];

		/* Incrémentation */
		i++;
	}

	l->cellules = tab;

	l->taille_x = size_x;
	l->taille_y = size_y;

	//fprintf(stderr,"Allocation terminee :[%i,%i], %i ocets alloue\n",l->taille_x, l->taille_y, sizeof(cell) * l->taille_x * l->taille_y);

	return l;
}

int val_cellule(int i, int j, laby l)
{

	if ((i >= 0) && (j >= 0) && (i < l->taille_x) && (j < l->taille_y))
		return l->cellules[i][j].val;

	return -1; 
}

int est_dans(int i, int tab[4])
{
	int y = 0;

	/* On tire les numéros aléatoire */
	for (y = 0; y < 4; y++)
	{
		if (i == tab[y])
			return 1;
	}

	return 0;
}

void laby_aleatoire(int i, int j, laby l)
{
	int w = 0;	/* Nombre de cases adjacentes */
	int y = 0;
	int val[4] = {-1,-1,-1,-1}; /* Nombres tirés */

	/* On avance dans la cellule i,j */
	l->cellules[i][j].val = 1;

	/* On tire les numéros aléatoire */
	for (y = 0; y < 4; y++)
	{
		int x = -1;

		while (est_dans(x,val))
		{
			x = rand()%4;
		}

		val[y] = x;
	}


	/* Vérification des cellules a coté */
	/* On choisit une cellule aléatoire et on progresse */
	/* Faire pour chaqu'une des cellules */
	for (w = 0; w < 4; w++)
	{
		/* On choisit une porte aléatoire */
		//	* 0 *
		//	1   2
		//	* 3 *	
		
		/* Affichage de la cellule sous la forme
			*0*
			1 3, trou = " "
			*2*, mur = "*"
			Gestion des murs : 0000
							   ESON
		*/

		switch (val[w]) 
		{
		case 0: 
		/* case ouest */
		if (val_cellule(i,j-1,l) == 0)
		{
			l->cellules[i][j].mur &= 0xFD;			/* ouverture de la porte ouest */
			l->cellules[i][j-1].mur &= 0xFB;			/* ouverture de la porte est de la case d'a coté */
			laby_aleatoire(i,j-1,l);
		}
		break;
		case 1: 
		/* case est */
		if (val_cellule(i,j+1,l) == 0)
		{
			l->cellules[i][j].mur &= 0xF7;		/* On ouvre la porte est */
			l->cellules[i][j+1].mur &= 0xFD;		/* On ouvre la porte ouest de la case d'a coté */
			laby_aleatoire(i,j+1,l);
		}
		break;
		case 2:
 		/* case sud */
		if (val_cellule(i+1,j,l) == 0)
		{
			l->cellules[i][j].mur &= 0xFB;	/* On ouvre la porte sud */
			l->cellules[i+1][j].mur &= 0xFE;	/* On ouvre la porte nord de la case d'a coté */
			laby_aleatoire(i+1,j,l);
		}
		break;
		case 3: 
		/* case nord */
		if (val_cellule(i-1,j,l) == 0)
		{
			l->cellules[i][j].mur &= 0xFE;		/* On ouvre la porte nord */
			l->cellules[i-1][j].mur &= 0xFB;	/* On ouvre la porte sud d'a coté */
			laby_aleatoire(i-1,j,l);
		}
		break;
		default: fprintf(stderr,"Erreur : w = %i, val = %i\n", w, val[w]); break;
		}
	}
}

laby creer_labyrinthe(int size_x, int size_y)
{
	laby l = creer_laby(size_x, size_y);

	int i, j;

	/* On met des murs sur toute les cellules et init de la valeur a zéro */
	for (i = 0; i < l->taille_x; i++)
	{
		for (j = 0; j < l->taille_y; j++)
		{
			l->cellules[i][j].mur = 15;
			l->cellules[i][j].val = 0;
		}
	}

	position_laby_victoire.x = (l->taille_x - 1)*SIZE_CELL;
	position_laby_victoire.z = (l->taille_y - 1)*SIZE_CELL;

	srand(time(NULL)); // initialisation de rand

	laby_aleatoire(rand()%size_x,rand()%size_y,l);

	return l;
	
}


void affiche_term_laby(laby l)
{
	int i, j;

	if (l == NULL)
	{
		fprintf(stderr,"Laby inexistant\n");
		return;
	}

	/* Affichage du labyrinthe */

	fprintf(stderr,"Affichage de %i, %i\n",l->taille_x,l->taille_y);

	for (i = 0; i < l->taille_x; i++)
	{		
		/* Affichage du haut */
		for (j = 0; j < l->taille_y; j++)
		{
			fprintf(stderr,"+");

			if ((l->cellules[i][j].mur & 0x01) != 0)
				fprintf(stderr,"--");
			else
				fprintf(stderr,"  ");
		}
		fprintf(stderr,"+\n");

		/* Affichage gauche */
		for (j = 0; j < l->taille_y; j++)
		{
			/* gauche */
			if ((l->cellules[i][j].mur & 0x02) != 0)
				fprintf(stderr,"|");
			else
				fprintf(stderr," ");


			fprintf(stderr,"  ");
		}
		fprintf(stderr,"|\n");
	}
	for (j = 0; j < l->taille_y; j++)
	{
		fprintf(stderr,"+--");
	}
	fprintf(stderr,"+\n");
}

cell * return_cell(laby l, int i, int j)
{
	if ((i >= 0) && (j >= 0) && (i < l->taille_x) && (j < l->taille_y))
		return & l->cellules[i][j];

	return NULL; 
}

int collide(laby l, float pos_x, float pos_z, float f_pos_x, float f_pos_z, float bounding_x, float bounding_z)
{
	/* Gestion des position dans le labyrinthe (en coordonnée) */
	int px = (int)pos_x/SIZE_CELL;
	int pz = (int)pos_z/SIZE_CELL;

	int fpx = (int)f_pos_x/SIZE_CELL;
	int fpz = (int)f_pos_z/SIZE_CELL;

	/* Calcul de la boite englobante */
	int fpx_basse = (f_pos_x - bounding_x)/SIZE_CELL; 
	int fpx_haute = (f_pos_x + bounding_x)/SIZE_CELL; 
	int fpz_basse = (f_pos_z - bounding_x)/SIZE_CELL; 
	int fpz_haute = (f_pos_z + bounding_x)/SIZE_CELL; 

	/* Pointeur sur cellules */
	cell * c1 = return_cell(l,px,pz);	/* Cellule actuelle */
	cell * c2 = return_cell(l,fpx,fpz);	/* Cellule suivante */

	/* Gestion des coordonnées de la caméra */
	/*fprintf(stderr,"position actuelle (%i,%i)->(%i,%i)\n",px, pz,fpx,fpz);
	fprintf(stderr,"position actuelle x: (float)%f, (int)%i\n",pos_x, px);
	fprintf(stderr,"position actuelle z: (float)%f, (int)%i\n",pos_z, pz);
	fprintf(stderr,"mur : %i\n", c1->mur);*/

	if (((f_pos_x - bounding_x) < 0) || ((f_pos_z - bounding_z) < 0) || ((f_pos_x + bounding_x) > l->taille_x * SIZE_CELL) || ((f_pos_z + bounding_z) > l->taille_y * SIZE_CELL))
	{
		//fprintf(stderr,"Le personnage essaie de sortir du labyrinthe\n");
		return 1;
	}

	if (c1 == NULL)
	{
		//fprintf(stderr,"Erreur! position du personnage en dehors du labyrinthe\n");
		return 0;
	}

	//affiche_term_laby(l);
	
	/* Gestion des murs sinon */
	
	// Mur nord
	if ((fpx_basse < px) && ((c1->mur & 0x01) != 0))
	{
		//fprintf(stderr,"(%i,%i)->(%i,%i) : Mur au nord, %i [%i]\n", px, pz, fpx_basse, fpz, c1->mur, (c1->mur & 0x01));
		return 1;
	}
	
	// Mur sud
	c2 = return_cell(l,fpx_haute,fpz);	/* Cellule suivante */
	if (((c2 == NULL) || (fpx_haute > px)) && ((c2->mur & 0x01) != 0))
	{
		//fprintf(stderr,"(%i,%i)->(%i,%i) : Mur au sud, %i [%i]\n", px, pz, fpx_haute, fpz, c1->mur, (c1->mur & 0x01));
		return 1;
	}
	
	// Mur ouest
	if ((fpz_basse  < pz) && ((c1->mur & 0x02) != 0))
	{
		//fprintf(stderr,"(%i,%i)->(%i,%i) : Mur a l'ouest, %i [%i]\n", px, pz, fpx, fpz_basse, c1->mur, (c1->mur & 0x02));
		return 1;
	}
	
	// Mur est
	c2 = return_cell(l,fpx,fpz_haute);	/* Cellule suivante */
	if (((c2 == NULL) || (fpz_haute > pz)) && ((c2->mur & 0x02) !=  0))
	{
		//fprintf(stderr,"(%i,%i)->(%i,%i) : Mur a l'est, %i [%i]\n", px, pz, fpx, fpz_haute, c1->mur, (c2->mur & 0x02));
		return 1;
	}	
	
	return 0;
}
