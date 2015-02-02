// Fonction d'affichage OpenGL

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "GL/glut.h"

#include "fct_affichage.h"
#include "camera.h"
#include "labyrinthe.h"
#include "etoile.h"
#include "nuage.h"

void trace_face_rectangulaire_vert(float x1, float y1, float z1, float x2, float y2, float z2, float tx, float ty, float tz, float color1, float color2, float color3)
{
	glPushMatrix();
	glTranslated(tx,ty,tz);
	glColor3ub(color1,color2,color3);
	if(affiche_information)
	{
		glBegin(GL_LINE_LOOP);
			glVertex3f(x1,y1,z1);
			glVertex3f(x1,y2,z1);
			glVertex3f(x2,y2,z2);
			glVertex3f(x2,y1,z2);
		glEnd();
	}
	else
	{
		glBegin(GL_QUADS);
			glVertex3f(x1,y1,z1);
			glVertex3f(x1,y2,z1);
			glVertex3f(x2,y2,z2);
			glVertex3f(x2,y1,z2);
		glEnd();
	}
	glPopMatrix();
}

void trace_face_rectangulaire_hori(float x1, float y1, float z1, float x2, float y2, float z2, float tx, float ty, float tz, float color1, float color2, float color3)
{
	glPushMatrix();
	glTranslated(tx,ty,tz);
	glColor3ub(color1,color2,color3);
	if(affiche_information)
	{
		glBegin(GL_LINE_LOOP);
			glVertex3f(x1,y1,z1);
			glVertex3f(x2,y1,z1);
			glVertex3f(x2,y1,z2);
			glVertex3f(x1,y1,z2);
		glEnd();
	}
	else
	{
		glBegin(GL_QUADS);
			glVertex3f(x1,y1,z1);
			glVertex3f(x2,y1,z1);
			glVertex3f(x2,y1,z2);
			glVertex3f(x1,y1,z2);
		glEnd();
	}
	glPopMatrix();
}

void trace_rectangle_3d(float x1, float y1, float z1, float x2, float y2, float z2, float tx, float ty, float tz, float color1, float color2, float color3)
{
	glPushMatrix();
		glTranslated(tx,ty,tz);
		trace_face_rectangulaire_vert(x1,y1,z1,x2,y2,z1,0,0,0,color1,color2,color3);
		trace_face_rectangulaire_vert(x2,y1,z1,x2,y2,z2,0,0,0,color1,color2,color3);

		trace_face_rectangulaire_hori(x1,y1,z1,x2,y1,z2,0,0,0,color1,color2,color3);
		trace_face_rectangulaire_hori(x1,y2,z1,x2,y2,z2,0,0,0,color1,color2,color3);

		trace_face_rectangulaire_vert(x1,y1,z1,x1,y2,z2,0,0,0,color1,color2,color3);
		trace_face_rectangulaire_vert(x1,y1,z2,x2,y2,z2,0,0,0,color1,color2,color3);
	glPopMatrix();
}

void trace_triangle(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, float tx, float ty, float tz, float color1, float color2, float color3)
{
	glPushMatrix();
		glTranslated(tx,ty,tz);
		glColor3ub(color1,color2,color3);
		if(affiche_information)
		{
			glBegin(GL_LINE_LOOP);
				glVertex3f( x1, y1, z1);
				glVertex3f( x2, y2, z2);
				glVertex3f( x3, y3, z3);
			glEnd();
		}
		else
		{
			glBegin(GL_TRIANGLES);
				glVertex3f( x1, y1, z1);
				glVertex3f( x2, y2, z2);
				glVertex3f( x3, y3, z3);
			glEnd();
		}
	glPopMatrix();
}

void trace_cylindre(float rb, float rt, float h, int nbf, float tx, float ty, float tz, float angle, float rx, float ry, float rz, float color1, float color2, float color3)
{
	GLUquadricObj* obj;
	glPushMatrix();
		glTranslated(tx,ty,tz);
		glRotated(angle, rx, ry, rz);
		glColor3ub(color1,color2,color3);
		if(affiche_information)
		{
			obj = gluNewQuadric();
			gluQuadricDrawStyle(obj, GLU_LINE);
			gluCylinder(obj,rb,rt,h,nbf,nbf);
		}
		else
		{
			obj = gluNewQuadric();
			gluCylinder(obj,rb,rt,h,nbf,nbf);
		}
	glPopMatrix();
}

void trace_cylindre_arbre(float rb, float rt, float h, int nbf, float tx, float ty, float tz)
{
	trace_cylindre(rb, rt, h, nbf, tx, ty, tz, 90, -1, 0, 0, 177,160,137);
}

void trace_cone(double r, double h, int nbf, int tx, int ty, int tz, float angle, float rx, float ry, float rz, float color1, float color2, float color3)
{
	glPushMatrix();
		glTranslated(tx,ty,tz);
		glRotated(angle,rx,ry,rz);
		glColor3ub(color1,color2,color3);
		if(affiche_information)
		{
			glutWireCone(r,h,nbf,nbf);
		}
		else
		{
			glutSolidCone(r,h,nbf,nbf);
		}
	glPopMatrix();
}

void trace_cone_arbre(double r, double h, int nbf, int tx, int ty, int tz)
{
	trace_cone(r,h,nbf,tx,ty,tz,90,-1,0,0,27,79,8);
}

void trace_sphere(double r, int nbf, int tx, int ty, int tz, float color1, float color2, float color3)
{
	glPushMatrix();
		glTranslated(tx,ty,tz);
		glColor3ub(color1,color2,color3);
		if(affiche_information)
		{
			glutWireSphere(r,nbf,nbf);
		}
		else
		{
			glutSolidSphere(r,nbf,nbf);
		}
	glPopMatrix();
}

void trace_sphere_arbre(double r, int nbf, int tx, int ty, int tz)
{
	trace_sphere(r,nbf,tx,ty,tz,0,200,0);
}

void trace_axe_xyz(float tx, float ty, float tz)
{
	if(affiche_information)
	{
		glPushMatrix();
		glTranslated(position_camera.x + sin(angleY),position_camera.y-1,position_camera.z + cos(angleY));
		glBegin(GL_LINES);
			// VERT
			glColor3ub(0,255,0);
			glVertex3f(0,0,0);
			glVertex3f(vecteurZ.x,vecteurZ.y,vecteurZ.z);
		glBegin(GL_LINES);
			// ROUGE
			glColor3ub(255,0,0);
			glVertex3f(0,0,0);
			glVertex3f(vecteurY.x,vecteurY.y,vecteurY.z);
		glBegin(GL_LINES);
			// BLEU
			glColor3ub(0,0,255);
			glVertex3f(0,0,0);
			glVertex3f(vecteurX.x,vecteurX.y,vecteurX.z);
		glEnd();
		glPopMatrix();
	}
}

void affichage_texte(char * txt, void* font, float tx, float ty, float tz)
{
	int cpt;
	int lon = strlen(txt);

	glPushMatrix();

		glRasterPos3f(tx, ty, tz);
		glColor3ub(255, 255, 255);
		for(cpt = 0 ; cpt < lon ; cpt++)
		{
			glutBitmapCharacter(font,txt[cpt]);
		}

	glPopMatrix();
}

void affichage_msg_victoire()
{
	if(victoire)
	{
		affichage_texte(msg_victoire,GLUT_BITMAP_TIMES_ROMAN_24,position_laby_victoire.x+(SIZE_CELL>>1),10,position_laby_victoire.z+(SIZE_CELL>>1));
	}
}

void trace_viseur()
{
	glPushMatrix();
		//glTranslated(position_camera.x + sin(angleY),position_camera.y + cos(angleX),position_camera.z + cos(angleY));
		/*glBegin(GL_LINES);
			glColor3ub(150,200,50);
			glVertex3f((longueur_fenetre<<1)-3,(largeur_fenetre<<1),0);
			glVertex3f((longueur_fenetre<<1)+3,(largeur_fenetre<<1),0);
		glEnd();
		glBegin(GL_LINES);
			glColor3ub(150,200,50);
			glVertex3f((longueur_fenetre<<1),(largeur_fenetre<<1)-3,0);
			glVertex3f((longueur_fenetre<<1),(largeur_fenetre<<1)+3,0);
		glEnd();*/
		glColor3f(1.0f,1.0f, 1.0f);

		glBegin(GL_LINES);
		glVertex2i((longueur_fenetre<<1), (largeur_fenetre<<1)-1);
		glVertex2i((longueur_fenetre<<1), (largeur_fenetre<<1)+1);

		glVertex2i((longueur_fenetre<<1)-1, (largeur_fenetre<<1));
		glVertex2i((longueur_fenetre<<1)+1, (largeur_fenetre<<1));
		glEnd();

	glPopMatrix();
}

void affichage_oiseaux()
{
	int cpt;
	float y,z;
	double x;

	for(cpt = 0 ; cpt < NB_OISEAUX_MAX ; cpt++)
	{
		y = tab_oiseau[cpt].long_aile/2;
		z = tab_oiseau[cpt].long_aile/3;
		x = sqrt((tab_oiseau[cpt].long_aile*tab_oiseau[cpt].long_aile)-(y*y));
		
		if(tab_oiseau[cpt].etat)
		{
			trace_triangle(x,y,0,0,0,z,0,0,-z,tab_oiseau[cpt].position.x,tab_oiseau[cpt].position.y,tab_oiseau[cpt].position.z,0,0,16);
			trace_triangle(-x,y,0,0,0,z,0,0,-z,tab_oiseau[cpt].position.x,tab_oiseau[cpt].position.y,tab_oiseau[cpt].position.z,0,0,16);
		}
		else if(!tab_oiseau[cpt].etat)
		{
			trace_triangle(x,-y,0,0,0,z,0,0,-z,tab_oiseau[cpt].position.x,tab_oiseau[cpt].position.y,tab_oiseau[cpt].position.z,0,0,16);
			trace_triangle(-x,-y,0,0,0,z,0,0,-z,tab_oiseau[cpt].position.x,tab_oiseau[cpt].position.y,tab_oiseau[cpt].position.z,0,0,16);
		}
	}
}

void affichage_ia()
{
	int cpt;

	for(cpt = 0 ; cpt < nb_ia ; cpt++)
	{
		trace_cylindre(5, 5, 20, 4, tabIA[cpt].position.x-5,tabIA[cpt].position.y,tabIA[cpt].position.z-5, 90, -1, 0, 0, 255,255,255);
		glPushMatrix();
		glTranslated(tabIA[cpt].position.x,tabIA[cpt].position.y,tabIA[cpt].position.z);
		glBegin(GL_LINES);
			// VERT
			glColor3ub(150,200,50);
			glVertex3f(tabIA[cpt].direction.x,tabIA[cpt].direction.y,tabIA[cpt].direction.z);
			glVertex3f(tabIA[cpt].position.x,tabIA[cpt].position.y,tabIA[cpt].position.z);
		glEnd();
		glPopMatrix();
	}
}

void affichage_soleil()
{
	trace_sphere(500,30,position_soleil.x,position_soleil.y,position_soleil.z,237,255,12);
	trace_sphere(500,30,position_lune.x,position_lune.y,position_lune.z,187,210,225);
}

void affichage_arbre_3d()
{
	int cpt;

	for(cpt = 0 ; cpt < 4 ; cpt++)
	{
		trace_face_rectangulaire_hori(	tab_sol_arbre_aff[cpt].position1.x,tab_sol_arbre_aff[cpt].position1.y,tab_sol_arbre_aff[cpt].position1.z,
										tab_sol_arbre_aff[cpt].position2.x,tab_sol_arbre_aff[cpt].position2.y,tab_sol_arbre_aff[cpt].position2.z,
										0,0,0,34,120,15);
	}

	for(cpt = 0 ; cpt < nb_arbre_actuel ; cpt++)
	{
		trace_cylindre_arbre(tab_arbre_aff[cpt].r_tronc,
					tab_arbre_aff[cpt].r_tronc-1,
					tab_arbre_aff[cpt].l_tronc,
					NB_FACE_TRONC_ARBRE,
					tab_arbre_aff[cpt].position.x,
					tab_arbre_aff[cpt].position.y,
					tab_arbre_aff[cpt].position.z);

		// Feuille
		switch(tab_arbre_aff[cpt].type_arbre)
		{
			// Sapin
			case 0: trace_cone_arbre(tab_arbre_aff[cpt].r_feuil,
						tab_arbre_aff[cpt].l_feuil,
						NB_FACE_CONE_ARBRE,
						tab_arbre_aff[cpt].position.x,
						tab_arbre_aff[cpt].position.y + tab_arbre_aff[cpt].l_tronc,
						tab_arbre_aff[cpt].position.z);
				break;

			// Arbre boule
			case 1:	trace_sphere_arbre(tab_arbre_aff[cpt].r_feuil,
						NB_FACE_BOULE_ARBRE,
						tab_arbre_aff[cpt].position.x,
						tab_arbre_aff[cpt].position.y + tab_arbre_aff[cpt].l_tronc
						+ tab_arbre_aff[cpt].r_feuil-2,
						tab_arbre_aff[cpt].position.z);
				break;
		}
	}
}

/*---------------------------------
  Affiche labyrinthe 3D with opengl
  ---------------------------------*/

/* Affichage d'une facette */
/* Couleur :	0 WHITE
				1 RED
				2 BLUE 
				3 GREEN */
void affiche_facette(point p1, point p2, point p3, point p4, float grey_level, int color, int board)
{

	if (grey_level != 0)
	{
		/* Faces carrée */
		switch (color)
		{
		case 0:glColor3f(grey_level,grey_level,grey_level);break;
		case 1:glColor3f(grey_level,0,0);break;
		case 2:glColor3f(0,0,grey_level);break;
		default:glColor3f(1,1,1);break;
		}
		
		

		/* Face avant */
		glBegin(GL_QUADS);
		glVertex3f(p1.x,p1.y,p1.z);
		glVertex3f(p2.x,p2.y,p2.z);
		glVertex3f(p3.x,p3.y,p3.z);
		glVertex3f(p4.x,p4.y,p4.z);
		glEnd();
	}

	/* Affichage des bords de la facette */
	if (board)
	{
		glColor3f(0,0,0);

		/* Tracage de ligne */
		glBegin(GL_LINE_LOOP);
		glVertex3f(p1.x,p1.y,p1.z);
		glVertex3f(p2.x,p2.y,p2.z);
		glVertex3f(p3.x,p3.y,p3.z);
		glVertex3f(p4.x,p4.y,p4.z);
		glEnd();
	}
}

void affiche_fenetre(point p1, point p2, point p3, point p4, float grey_level, int color, int board)
{
	if (grey_level != 0)
	{
		/* calcul de la fenetre */
		float distance_x = (p2.x - p1.x) / 3;
		float distance_y = (p4.y - p1.y) / 3;
		float distance_z = (p2.z - p1.z) / 3;

		/* Faces carrée */
		switch (color)
		{
		case 0:glColor3f(grey_level,grey_level,grey_level);break;
		case 1:glColor3f(grey_level,0,0);break;
		case 2:glColor3f(0,0,grey_level);break;
		default:glColor3f(1,1,1);break;
		}

		

		/* Fenetre */
		glBegin(GL_QUADS);
		glVertex3f(p1.x,p1.y,p1.z);
		glVertex3f(p2.x,p2.y,p2.z);
		glVertex3f(p2.x,p2.y + distance_y,p2.z);
		glVertex3f(p1.x,p1.y + distance_y,p1.z);
		
		glVertex3f(p4.x,p4.y,p4.z);
		glVertex3f(p4.x,p4.y - distance_y,p4.z);
		glVertex3f(p3.x,p3.y - distance_y,p2.z);
		glVertex3f(p3.x,p3.y,p3.z);

		if (distance_x != 0)
		{
			glVertex3f(p1.x,p1.y + distance_y,p1.z);
			glVertex3f(p1.x + distance_x,p1.y + distance_y,p1.z);
			glVertex3f(p1.x + distance_x,p1.y + (distance_y * 2),p1.z);
			glVertex3f(p1.x,p1.y + (distance_y * 2),p1.z);

			glVertex3f(p2.x,p2.y + distance_y,p2.z);
			glVertex3f(p2.x - distance_x,p2.y + distance_y,p2.z);
			glVertex3f(p2.x - distance_x,p2.y + (distance_y * 2),p2.z);
			glVertex3f(p2.x,p2.y + (distance_y * 2),p2.z);
		}
		else
		{
			glVertex3f(p1.x,p1.y + distance_y,p1.z);
			glVertex3f(p1.x,p1.y + distance_y,p1.z + distance_z);
			glVertex3f(p1.x,p1.y + (distance_y * 2),p1.z + distance_z);
			glVertex3f(p1.x,p1.y + (distance_y * 2),p1.z);

			glVertex3f(p2.x,p2.y + distance_y,p2.z);
			glVertex3f(p2.x,p2.y + distance_y,p2.z - distance_z);
			glVertex3f(p2.x,p2.y + (distance_y * 2),p2.z - distance_z);
			glVertex3f(p2.x,p2.y + (distance_y * 2),p2.z);
		}
		glEnd();
	}

	/* Affichage des bords de la facette */
	if (board)
	{
		glColor3f(0,0,0);

		/* Tracage de ligne */
		glBegin(GL_LINE_LOOP);
		glVertex3f(p1.x,p1.y,p1.z);
		glVertex3f(p2.x,p2.y,p2.z);
		glVertex3f(p3.x,p3.y,p3.z);
		glVertex3f(p4.x,p4.y,p4.z);
		glEnd();
	}
}

void affiche_opengl_laby(laby l)
{
	/* Compteurs */
	int i, j;
	int color = 1;

	if (l == NULL)
	{
		fprintf(stderr,"Laby inexistant\n");
		return;
	}

	/* Affichage du labyrinthe */
	for (i = 0; i < l->taille_x; i++)	/* pour chaque lignes */
	{		
		/* Affichage du haut, de la base et gauche de la cellule */
		for (j = 0; j < l->taille_y; j++)	/* pour chaque colonne */
		{
			color = 0;
			if (i == 0 && j == 0)
				color = 1;
			if ((i == l->taille_x - 1) && (j == l->taille_y - 1))
				color = 2;

			/* Affichage du sol */
			affiche_facette(creer_point(i * SIZE_CELL,0,j * SIZE_CELL),creer_point((i+1) * SIZE_CELL,0,j * SIZE_CELL),creer_point((i+1) * SIZE_CELL ,0,(j+1) * SIZE_CELL),creer_point(i * SIZE_CELL,0,(j+1) * SIZE_CELL), 1, color, 1);

			
			/* Mur NORD */
			if ((l->cellules[i][j].mur & 0x01) != 0)
			{
				if (i == 0)
					affiche_fenetre(creer_point(i * SIZE_CELL,0,j * SIZE_CELL),creer_point(i * SIZE_CELL,0,(j+1) * SIZE_CELL),creer_point(i * SIZE_CELL,SIZE_WALL,(j+1) * SIZE_CELL),creer_point(i * SIZE_CELL,SIZE_WALL,j * SIZE_CELL), 0.5, 0, 0);
				else
					affiche_facette(creer_point(i * SIZE_CELL,0,j * SIZE_CELL),creer_point(i * SIZE_CELL,0,(j+1) * SIZE_CELL),creer_point(i * SIZE_CELL,SIZE_WALL,(j+1) * SIZE_CELL),creer_point(i * SIZE_CELL,SIZE_WALL,j * SIZE_CELL), 0.5, 0, 0);
			}

			/* Mur OUEST */
			if ((l->cellules[i][j].mur & 0x02) != 0)
			{
				if (j == 0)
					affiche_fenetre(creer_point((i+1) * SIZE_CELL,0,j * SIZE_CELL),creer_point(i * SIZE_CELL,0,j * SIZE_CELL),creer_point(i * SIZE_CELL,SIZE_WALL,j * SIZE_CELL),creer_point((i+1) * SIZE_CELL,SIZE_WALL,j * SIZE_CELL), 0.6, 0, 0);
				else
					affiche_facette(creer_point((i+1) * SIZE_CELL,0,j * SIZE_CELL),creer_point(i * SIZE_CELL,0,j * SIZE_CELL),creer_point(i * SIZE_CELL,SIZE_WALL,j * SIZE_CELL),creer_point((i+1) * SIZE_CELL,SIZE_WALL,j * SIZE_CELL), 0.6, 0, 0);
			}
		}
		/* On affiche le mur EST a la fin */
		affiche_fenetre(creer_point(i * SIZE_CELL,0,j * SIZE_CELL),creer_point((i+1) * SIZE_CELL,0,j * SIZE_CELL),creer_point((i+1) * SIZE_CELL,SIZE_WALL,j * SIZE_CELL),creer_point(i * SIZE_CELL,SIZE_WALL,j * SIZE_CELL), 0.7, 0, 0);
		
	}
	for (j = 0; j < l->taille_y; j++)
	{
		color = 0;
		/* On affiche le mur SUD a la fin */
		affiche_fenetre(creer_point(i * SIZE_CELL,0,j * SIZE_CELL),creer_point(i * SIZE_CELL,0,(j+1) * SIZE_CELL),creer_point(i * SIZE_CELL,SIZE_WALL,(j+1) * SIZE_CELL),creer_point(i * SIZE_CELL,SIZE_WALL,j * SIZE_CELL), 0.7, color, 0);
	}
}

void draw_texture(texture t, point p1, point p2, point p3, point p4)
{
	/* Vérification de null_pointer */
	if (t == NULL)
		return;

	/* Texture spec */
	glTexImage2D(GL_TEXTURE_2D, 0, 3, t->size_x, t->size_y, 0, GL_RGB, GL_UNSIGNED_BYTE, t->pixels);

	/* Texture management */
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glEnable(GL_TEXTURE_2D);

	glColor3f(1,1,1);

	glBegin(GL_QUADS);
	glTexCoord2d(0,0);glVertex3d(p1.x,  p1.y, p1.z);
	glTexCoord2d(0,1);glVertex3d(p2.x,  p2.y, p2.z);
	glTexCoord2d(1,1);glVertex3d(p3.x,  p3.y, p3.z);
	glTexCoord2d(1,0);glVertex3d(p4.x,  p4.y, p4.z);
	glEnd();
}

void draw_gouttes(point p)
{
	if (p.y > 0)
	{
		affiche_facette(creer_point(p.x - 0.2, p.y, p.z), creer_point(p.x + 0.2, p.y, p.z),creer_point(p.x + 0.2, p.y + 3, p.z),creer_point(p.x - 0.2, p.y + 3, p.z), 1,2,0);
	}
}

void draw_nuage(nuage * n)
{
	int i, y;
	float z = n->position.z, x_g = n->position.x - (n->rayon / 2), x_d = n->position.x + (n->rayon / 2);

	float color;

	if (n->type == 0)
		color = 255;
	else
		color = 100;
		

	for (i = 0; i < n->taille_y; i++)
	{
		/* On dessine tout les cercles composants les nuages */
		for (y = 0; y < n->taille_x / 2; y++)
		{
			trace_sphere(n->rayon, 8, x_d, n->position.y, z, color,color,color);
			trace_sphere(n->rayon, 8, x_g, n->position.y, z, color,color,color);
			x_g -= n->rayon;
			x_d += n->rayon;
		}
		/* Affichage des gouttes */
		x_g = n->position.x - (n->rayon / 2), x_d = n->position.x + (n->rayon / 2);
		z += (n->rayon);
	}
}

void draw_weather(weather w)
{
	int i = 0;

	for (i = 0; i < w->nb_nuage; i++)
	{
		draw_nuage(& w->nuages[i]);
	}

	for (i = 0; i < w->nb_gouttes; i++)
	{
		draw_gouttes(w->gouttes[i]);
	}
}

void affiche_triangle(triangle t)
{
	/* Tracage de ligne */
	//glBegin(GL_LINE_LOOP);
	glBegin(GL_TRIANGLES);
	glVertex3f(t.p1.x,t.p1.y,t.p1.z);
	glVertex3f(t.p2.x,t.p2.y,t.p2.z);
	glVertex3f(t.p3.x,t.p3.y,t.p3.z);
	glEnd();
}


void fct_affichage()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	// Update de la position de la camera
	update_camera();

	gluLookAt(position_joueur.x,position_joueur.y,position_joueur.z,position_camera.x,position_camera.y,position_camera.z,0,1,0);

	affichage_soleil();

	affichage_oiseaux();

	//affichage_arbre_3d();

	affichage_ia();

	afficher_etoile(grille_etoiles);

	draw_weather(w);

	//trace_viseur();

	//affiche_opengl_laby(labyrinthe_3d);
	affichage_msg_victoire();

	affiche_karbre();

	trace_axe_xyz(0,0,0);
	//affiche_triangle(retourne_triangle());
	//affiche_rect(transf_triangle(retourne_triangle()));
	glutSwapBuffers();
}

/* Retourne le triangle de vision de caméra */
/*
		+ <-p1
	   / \
	  /	  \<- c (cote)
p2-> +-----+ <-p3
	  taille
*/
triangle retourne_triangle()
{
	triangle t;
	float angle = (180 * angleY_bloque - DEF_PI_SUR_DEUX) / DEF_PI;
	float my_fov = fov / 2;	/* FOV pour le calcul de l'angle du triangle */
	float y_view = 5;	/* position le triangle sur la vue */

	t.p1 = creer_point(position_joueur_bloque.x, y_view /* Non important */, position_joueur_bloque.z);

	/* Point en bas a gauche */
	 t.p2.x = t.p1.x + 2000 * sin(DEF_PI * (angle + my_fov) / 180);
	 t.p2.y = y_view; 
	 t.p2.z = t.p1.z + 2000 * cos(DEF_PI * (angle + my_fov) / 180);

	 /* Point en bas a droite */
	 t.p3.x = t.p1.x + 2000 * sin(DEF_PI * (angle - my_fov) / 180);
	 t.p3.y = y_view;
	 t.p3.z = t.p1.z + 2000 * cos(DEF_PI * (angle - my_fov) / 180);

	return t;
}


void affiche_rect(rect r)
{
	glColor3f(0,0,1);

	glBegin(GL_QUADS);
	glTexCoord2d(0,0);glVertex3d(r.p1.x,  r.p1.y, r.p1.z);
	glTexCoord2d(0,1);glVertex3d(r.p2.x,  r.p1.y, r.p1.z);
	glTexCoord2d(1,1);glVertex3d(r.p2.x,  r.p1.y, r.p2.z);
	glTexCoord2d(1,0);glVertex3d(r.p1.x,  r.p1.y, r.p2.z);
	glEnd();
}


/* transforme un triangle en carré */
/* Fonction xmin,xmax,ymin,ymax */
rect transf_triangle(triangle t)
{
	rect r;
	float x_min, x_max;
	float z_min, z_max;

	/* détermination de x_min */
	if (t.p1.x < t.p2.x)
		x_min = t.p1.x;
	else
		x_min = t.p2.x;

	if (x_min > t.p3.x)
		x_min = t.p3.x;

	/* détermination de y_min */
	if (t.p1.z < t.p2.z)
		z_min = t.p1.z;
	else
		z_min = t.p2.z;

	if (z_min > t.p3.z)
		z_min = t.p3.z;

	/* Détermination de x_max */
	if (t.p1.x > t.p2.x)
		x_max = t.p1.x;
	else
		x_max = t.p2.x;

	if (x_max < t.p3.x)
		x_max = t.p3.x;

	/* détermination de y_max */
	if (t.p1.z > t.p2.z)
		z_max = t.p1.z;
	else
		z_max = t.p2.z;

	if (z_max < t.p3.z)
		z_max = t.p3.z;

	r.p1.x = x_min;
	r.p1.y = -1;
	r.p1.z = z_min;

	r.p2.x = x_max;
	r.p2.y = -1;
	r.p2.z = z_max;

	return r;

}

void affiche_arbre_bis(float min_x, float max_x, float min_z, float max_z, noeud_k_arbre n)
{
	int collide = collision_rectangle(n->p[0], n->p[1].z - n->p[0].z, n->p[1].x - n->p[0].x, creer_point(min_x, 0, min_z), max_z - min_z, max_x - min_x);

	// Le carré du noeud est totalement dedans
	if (collide == 2)
	{
		affiche_noeud(n);
	}
	else if (collide == 1) // Partiellement dedans
	{
		if (n->numA == -1) // On peu continuer...
		{
			if (n->fils != NULL)
			{
				affiche_arbre_bis(min_x, max_x, min_z, max_z, n->fils[0]);
				affiche_arbre_bis(min_x, max_x, min_z, max_z, n->fils[1]);
				affiche_arbre_bis(min_x, max_x, min_z, max_z, n->fils[2]);
				affiche_arbre_bis(min_x, max_x, min_z, max_z, n->fils[3]);
			}
		}
		else
			affiche_noeud(n);
	}
}

/* Fonction d'affichage avec le karbre (k_arbre_carte) et la caméra : vue -> position_camera_bloque, position : position_joueur */
void affiche_karbre()
{
	rect r = transf_triangle(retourne_triangle());

	affiche_arbre_bis(r.p1.x, r.p2.x, r.p1.z, r.p2.z, k_arbre_carte);
}

/* Affiche le noeud */
void affiche_noeud(noeud_k_arbre n)
{
	if (n->numA == -1)	/* aucune display_list sur ce noeud */
	{
		if (n->fils != NULL)
		{
			/* On affiche les listes des noeuds */
			affiche_noeud(n->fils[0]);
			affiche_noeud(n->fils[1]);
			affiche_noeud(n->fils[2]);
			affiche_noeud(n->fils[3]);
		}
	}
	else
	{
		glCallList(n->numA);	/* Affichage de la liste */
	}
}