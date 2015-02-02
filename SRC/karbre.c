// Définition des k-arbres

#include <stdio.h>

#include "karbre.h"
#include "fct_affichage.h"

void init_k_arbre()
{
	point depart; // point d'origine du carre
	float largeur_map;
	float longueur_map;

	largeur_map = (labyrinthe_3d->taille_x * SIZE_CELL) + (2*LARGEUR_RECT_ARBRE);
	longueur_map = (labyrinthe_3d->taille_y * SIZE_CELL) + (2*LARGEUR_RECT_ARBRE);

	if(largeur_map > longueur_map)
	{
		taille_carre_principal = largeur_map;
	}
	else
	{
		taille_carre_principal = longueur_map;
	}

	depart.y = 0.0;
	depart.x = -(labyrinthe_3d->taille_x * SIZE_CELL) - LARGEUR_RECT_ARBRE;
	depart.z = -LARGEUR_RECT_ARBRE;

	// Lancement de la creation de labyrinthe_3d'arbre
	k_arbre_carte = calcul_k_arbre(depart,taille_carre_principal);
}

int collision_rectangle(point p1, float t1h, float t1l, point p2, float t2h, float t2l)
{
	if ((p1.z + t1h) <= p2.z)
		return 0;
	if (p1.z >= (p2.z + t2h))
		return 0;
	if ((p1.x + t1l) <= p2.x)
		return 0;
	if (p1.x >= (p2.x + t2l))
		return 0;

	if((p1.x >= p2.x) && (p1.x + t1l <= p2.x+t2l) && (p1.z >= p2.z) && (p1.z + t1h <= p2.x+t2h))
	{
		return 2;
	}

	return 1;
}


noeud_k_arbre calcul_k_arbre(point depart,float taille)
{
	int test = 0;
	point p1,p2,p3,p4,pp;
	int cpt = 0;
	int i,j,color;
	int nbfacette = 0;
	noeud_k_arbre noeud = NULL;

	nb_noeud_actif++;

	noeud = (noeud_k_arbre)malloc(sizeof(struct struct_k_arbre));
	noeud->numA = nb_noeud_actif;
	noeud->fils = NULL;
	noeud->p[0] = depart;

	noeud->p[1].x = depart.x + taille;
	noeud->p[1].y = depart.y + taille;
	noeud->p[1].z = depart.z + taille;

	// Debut display list
	glNewList(noeud->numA,GL_COMPILE);

	// Analyse des arbres
	while(cpt < nb_arbre_actuel && nbfacette <= nb_fac_max)
	{
		if((tab_arbre_aff[cpt].position.x >= depart.x && tab_arbre_aff[cpt].position.z >= depart.z) &&
			(tab_arbre_aff[cpt].position.x <= depart.x + taille && tab_arbre_aff[cpt].position.z <= depart.z + taille))
		{
			test = 1;
			nbfacette += NB_FACE_TRONC_ARBRE;

			trace_cylindre_arbre(tab_arbre_aff[cpt].r_tronc,
					tab_arbre_aff[cpt].r_tronc-1,
					tab_arbre_aff[cpt].l_tronc,
					NB_FACE_TRONC_ARBRE,
					tab_arbre_aff[cpt].position.x,
					tab_arbre_aff[cpt].position.y,
					tab_arbre_aff[cpt].position.z);

			if(tab_arbre_aff[cpt].type_arbre == 0)
			{
				nbfacette += NB_FACE_CONE_ARBRE;

				trace_cone_arbre(tab_arbre_aff[cpt].r_feuil,
						tab_arbre_aff[cpt].l_feuil,
						NB_FACE_CONE_ARBRE,
						tab_arbre_aff[cpt].position.x,
						tab_arbre_aff[cpt].position.y + tab_arbre_aff[cpt].l_tronc,
						tab_arbre_aff[cpt].position.z);
			}
			else if(tab_arbre_aff[cpt].type_arbre == 1)
			{
				nbfacette += NB_FACE_BOULE_ARBRE;

				trace_sphere_arbre(tab_arbre_aff[cpt].r_feuil,
						NB_FACE_BOULE_ARBRE,
						tab_arbre_aff[cpt].position.x,
						tab_arbre_aff[cpt].position.y + tab_arbre_aff[cpt].l_tronc
						+ tab_arbre_aff[cpt].r_feuil-2,
						tab_arbre_aff[cpt].position.z);
			}
		}
		cpt++;
	}

	cpt = 0;

	// Analyse sols
	while(cpt < 4 && nbfacette <= nb_fac_max)
	{
		if(collision_rectangle(tab_sol_arbre_aff[cpt].position1,
				labyrinthe_3d->taille_y*SIZE_CELL + LARGEUR_RECT_ARBRE,
				labyrinthe_3d->taille_x*SIZE_CELL + (2*LARGEUR_RECT_ARBRE),
				depart,
				taille,
				taille) != 0)
		{
			test = 1;

			nbfacette++;

			trace_face_rectangulaire_hori(	tab_sol_arbre_aff[cpt].position1.x,tab_sol_arbre_aff[cpt].position1.y,tab_sol_arbre_aff[cpt].position1.z,
										tab_sol_arbre_aff[cpt].position2.x,tab_sol_arbre_aff[cpt].position2.y,tab_sol_arbre_aff[cpt].position2.z,
										0,0,0,34,120,15);
		}
		
		cpt++;
	}

	// Analyse laby
	for (i = 0; i < labyrinthe_3d->taille_x; i++)	/* pour chaque lignes */
	{		
		for (j = 0; j < labyrinthe_3d->taille_y; j++)	/* pour chaque colonne */
		{
			color = 0;
			if (i == 0 && j == 0)
				color = 1;
			if ((i == labyrinthe_3d->taille_x - 1) && (j == labyrinthe_3d->taille_y - 1))
				color = 2;

			pp = creer_point(i * SIZE_CELL,0,j * SIZE_CELL);

			if(collision_rectangle(pp,
				SIZE_CELL,
				SIZE_CELL,
				depart,
				taille,
				taille) != 0)
			{
				nbfacette += NB_FACE_MUR;
				/* Affichage du sol */
				affiche_facette(pp,creer_point((i+1) * SIZE_CELL,0,j * SIZE_CELL),creer_point((i+1) * SIZE_CELL ,0,(j+1) * SIZE_CELL),creer_point(i * SIZE_CELL,0,(j+1) * SIZE_CELL), 1, color, 1);

			}
				/* Mur NORD */
				if ((labyrinthe_3d->cellules[i][j].mur & 0x01) != 0)
				{
					 if(((pp.x >= depart.x) && (pp.x <= depart.x + taille) && (pp.z >= depart.z) && (pp.z <= depart.z + taille)) || ((pp.x >= depart.x) && (pp.x <= depart.x + taille) && (pp.z + SIZE_CELL >= depart.z) && (pp.z + SIZE_CELL <= depart.z + taille)))
					 {
						 nbfacette += NB_FACE_MUR;
						if (i == 0)
							affiche_fenetre(pp,creer_point(i * SIZE_CELL,0,(j+1) * SIZE_CELL),creer_point(i * SIZE_CELL,SIZE_WALL,(j+1) * SIZE_CELL),creer_point(i * SIZE_CELL,SIZE_WALL,j * SIZE_CELL), 0.5, 0, 0);
						else
							affiche_facette(pp,creer_point(i * SIZE_CELL,0,(j+1) * SIZE_CELL),creer_point(i * SIZE_CELL,SIZE_WALL,(j+1) * SIZE_CELL),creer_point(i * SIZE_CELL,SIZE_WALL,j * SIZE_CELL), 0.5, 0, 0);
					}
				}
			
				/* Mur OUEST */
				if ((labyrinthe_3d->cellules[i][j].mur & 0x02) != 0)
				{
					if(((pp.x >= depart.x) && (pp.x <= depart.x + taille) && (pp.z >= depart.z) && (pp.z <= depart.z + taille)) || ((pp.x + SIZE_CELL >= depart.x) && (pp.x + SIZE_CELL <= depart.x + taille) && (pp.z >= depart.z) && (pp.z <= depart.z + taille)))
					{
						nbfacette += NB_FACE_MUR;
						if (j == 0)
							affiche_fenetre(creer_point((i+1) * SIZE_CELL,0,j * SIZE_CELL),creer_point(i * SIZE_CELL,0,j * SIZE_CELL),creer_point(i * SIZE_CELL,SIZE_WALL,j * SIZE_CELL),creer_point((i+1) * SIZE_CELL,SIZE_WALL,j * SIZE_CELL), 0.6, 0, 0);
						else
							affiche_facette(creer_point((i+1) * SIZE_CELL,0,j * SIZE_CELL),creer_point(i * SIZE_CELL,0,j * SIZE_CELL),creer_point(i * SIZE_CELL,SIZE_WALL,j * SIZE_CELL),creer_point((i+1) * SIZE_CELL,SIZE_WALL,j * SIZE_CELL), 0.6, 0, 0);
					}
				}
			}

		pp = creer_point(i * SIZE_CELL,0,j * SIZE_CELL);

		if (((pp.x >= depart.x) && (pp.x <= depart.x + taille) && (pp.z + SIZE_CELL >= depart.z) && (pp.z + SIZE_CELL <= depart.z + taille)) || ((pp.x + SIZE_CELL >= depart.x) && (pp.x + SIZE_CELL <= depart.x + taille) && (pp.z  + SIZE_CELL >= depart.z) && (pp.z  + SIZE_CELL <= depart.z + taille)))
		{
			nbfacette += NB_FACE_MUR;
			/* On affiche le mur EST a la fin */
			affiche_fenetre(pp,creer_point((i+1) * SIZE_CELL,0,j * SIZE_CELL),creer_point((i+1) * SIZE_CELL,SIZE_WALL,j * SIZE_CELL),creer_point(i * SIZE_CELL,SIZE_WALL,j * SIZE_CELL), 0.7, 0, 0);
		}
	}
	for (j = 0; j < labyrinthe_3d->taille_y; j++)
	{
		pp = creer_point(i * SIZE_CELL,0,j * SIZE_CELL);

			color = 0;
			/* On affiche le mur SUD a la fin */
			if(((pp.x  + SIZE_CELL >= depart.x) && (pp.x  + SIZE_CELL <= depart.x + taille) && (pp.z >= depart.z) && (pp.z <= depart.z + taille)) || ((pp.x + SIZE_CELL >= depart.x) && (pp.x  + SIZE_CELL <= depart.x + taille) && (pp.z + SIZE_CELL >= depart.z) && (pp.z + SIZE_CELL <= depart.z + taille)))
			{
				nbfacette += NB_FACE_MUR;
				affiche_fenetre(creer_point(i * SIZE_CELL,0,j * SIZE_CELL),creer_point(i * SIZE_CELL,0,(j+1) * SIZE_CELL),creer_point(i * SIZE_CELL,SIZE_WALL,(j+1) * SIZE_CELL),creer_point(i * SIZE_CELL,SIZE_WALL,j * SIZE_CELL), 0.7, color, 0);
			}
	}

	// Fin display list
	glEndList();

	if(nbfacette > nb_fac_max)
	{
		taille = taille/2.f;

		if(taille > 50.f)
		{
			noeud->numA = -1;
			// Creation des fils
			noeud->fils = (noeud_k_arbre*)malloc(sizeof(noeud_k_arbre) * 4);

			p4 = depart;

			p2.x = depart.x + taille;
			p2.y = depart.y;
			p2.z = depart.z + taille;

			p3.x = depart.x + taille;
			p3.y = depart.y;
			p3.z = depart.z;

			p1.x = depart.x;
			p1.y = depart.y;
			p1.z = depart.z + taille;

			// Appel des k-fils
			noeud->fils[0] = calcul_k_arbre(p1,taille);
			noeud->fils[1] = calcul_k_arbre(p2,taille);
			noeud->fils[2] = calcul_k_arbre(p3,taille);
			noeud->fils[3] = calcul_k_arbre(p4,taille);
		}
	}
	else if(test == 0)
	{
		noeud->numA = -1;
	}

	return noeud;
}