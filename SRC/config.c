// Gestion configuration

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "config.h"
#include "definition.h"

void initConfig()
{
	// Init variable config
	largeur_fenetre = 600;
	longueur_fenetre = 800;
	limite_fps = 60;
	op_fullscreen = 0;
	sensibilitee = 0.005f;
	nb_ia = 0;
	longueur_labyrinthe = 20;
	largeur_labyrinthe = 20;
	nb_fac_max = 1000;
	fov = 60;
}

int loadFichierConfig()
{
	int i;
	float f;
	FILE *file = NULL;
	char ligne[TAILLE_MAX_CHAR] = "";
	char *mot;
	char *buffer;

	initConfig();

	file = fopen(FICHIER_CONFIG,"r");

	if(file != NULL)
	{
		buffer = (char*)malloc(sizeof(char)*TAILLE_MAX_CHAR);

		while(fgets(ligne,TAILLE_MAX_CHAR,file) != NULL)
		{
			mot = strtok(ligne," ");
			// LARGEUR FENETRE
			memcpy(buffer,LARGEUR_FENETRE,sizeof(LARGEUR_FENETRE));
			if(strcmp(buffer,mot) == 0)
			{
				mot = strtok(NULL," ");
				i = atoi(mot);
				
				if( i <= 1080 && i >= 600 )
				{
					largeur_fenetre = i;
				}
			}
			else 	
			{
				// LONGUEUR FENETRE
				memcpy(buffer,LONGUEUR_FENETRE,sizeof(LONGUEUR_FENETRE));
				if(strcmp(mot,LONGUEUR_FENETRE) == 0)
				{
					mot = strtok(NULL," ");
					i = atoi(mot);
				
					if( i <= 1920 && i >= 800 )
					{
						longueur_fenetre = i;
					}
				}
				else
				{
					// LIMITE FPS
					memcpy(buffer,LIMITE_FPS,sizeof(LIMITE_FPS));
					if(strcmp(mot,LIMITE_FPS) == 0)
					{
						mot = strtok(NULL," ");
						i = atoi(mot);
				
						if( i <= 60 && i >= 30 )
						{
							limite_fps = i;
						}

					}
					else
					{
						// FULLSCREEN
						memcpy(buffer,OP_FULLSCREEN,sizeof(OP_FULLSCREEN));
						if(strcmp(mot,OP_FULLSCREEN) == 0)
						{
							mot = strtok(NULL," ");
							i = atoi(mot);
				
							if( i <= 1 && i >= 0 )
							{
								op_fullscreen = i;
							}
						}
						else
						{
							// SENSIBILITEE
							memcpy(buffer,SENSIBILITEE,sizeof(SENSIBILITEE));
							if(strcmp(mot,SENSIBILITEE) == 0)
							{
								mot = strtok(NULL," ");
								f = atof(mot);
				
								if( f <= 10.0 && f >= 0.0000001 )
								{
									sensibilitee = f;
								}
							}
							else
							{
								// NOMBRE D IA
								memcpy(buffer,NOMBRE_IA,sizeof(NOMBRE_IA));
								if(strcmp(mot,NOMBRE_IA) == 0)
								{
									mot = strtok(NULL," ");
									i = atoi(mot);
				
									if( i <= 20 && i >= 0 )
									{
										nb_ia = i;
									}
								}
								else
								{
									// LONGUEUR LABYRINTHE
									memcpy(buffer,LONGUEUR_LABY,sizeof(LONGUEUR_LABY));
									if(strcmp(mot,LONGUEUR_LABY) == 0)
									{
										mot = strtok(NULL," ");
										i = atoi(mot);
				
										if( i <= 100 && i >= 20 )
										{
											longueur_labyrinthe = i;
										}
									}
									else
									{
										// LARGEUR LABYRINTHE
										memcpy(buffer,LARGEUR_LABY,sizeof(LARGEUR_LABY));
										if(strcmp(mot,LARGEUR_LABY) == 0)
										{
											mot = strtok(NULL," ");
											i = atoi(mot);
				
											if( i <= 100 && i >= 20 )
											{
												largeur_labyrinthe = i;
											}
										}
										else
										{
											// NOMBRE FACETTES MAX
											memcpy(buffer,NB_FACETTE_MAX,sizeof(NB_FACETTE_MAX));
											if(strcmp(mot,NB_FACETTE_MAX) == 0)
											{
												mot = strtok(NULL," ");
												i = atoi(mot);
				
												if( i <= 10000 && i >= 5 )
												{
													nb_fac_max = i;
												}
											}
											else
											{
												// FOV
												memcpy(buffer,F_O_V,sizeof(F_O_V));
												if(strcmp(mot,F_O_V) == 0)
												{
													mot = strtok(NULL," ");
													i = atoi(mot);
				
													if( i <= 120 && i >= 60 )
													{
														fov = i;
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}

		fclose(file);

		free(buffer);

		return 0;
	}

	return 1;
}

int saveFichierConfig()
{
	FILE *file = NULL;
	char chaine[TAILLE_MAX_CHAR] = "";
	char mot[TAILLE_MAX_CHAR] = "";

	file = fopen(FICHIER_CONFIG,"w");

	if(file != NULL)
	{

		memcpy(chaine,LARGEUR_FENETRE,sizeof(LARGEUR_FENETRE));
		fputs(chaine,file);
		fputc(' ',file);
		sprintf(mot,"%i",largeur_fenetre);
		memcpy(chaine,mot,sizeof(mot));
		fputs(chaine,file);
		fputc('\n',file);

		memcpy(chaine,LONGUEUR_FENETRE,sizeof(LONGUEUR_FENETRE));
		fputs(chaine,file);
		fputc(' ',file);
		sprintf(mot,"%i",longueur_fenetre);
		memcpy(chaine,mot,sizeof(mot));
		fputs(chaine,file);
		fputc('\n',file);

		memcpy(chaine,LIMITE_FPS,sizeof(LIMITE_FPS));
		fputs(chaine,file);
		fputc(' ',file);
		sprintf(mot,"%i",limite_fps);
		memcpy(chaine,mot,sizeof(mot));
		fputs(chaine,file);
		fputc('\n',file);

		memcpy(chaine,OP_FULLSCREEN,sizeof(OP_FULLSCREEN));
		fputs(chaine,file);
		fputc(' ',file);
		sprintf(mot,"%i",op_fullscreen);
		memcpy(chaine,mot,sizeof(mot));
		fputs(chaine,file);
		fputc('\n',file);

		memcpy(chaine,SENSIBILITEE,sizeof(SENSIBILITEE));
		fputs(chaine,file);
		fputc(' ',file);
		sprintf(mot,"%f",sensibilitee);
		memcpy(chaine,mot,sizeof(mot));
		fputs(chaine,file);
		fputc('\n',file);

		memcpy(chaine,NOMBRE_IA,sizeof(NOMBRE_IA));
		fputs(chaine,file);
		fputc(' ',file);
		sprintf(mot,"%i",nb_ia);
		memcpy(chaine,mot,sizeof(mot));
		fputs(chaine,file);
		fputc('\n',file);

		memcpy(chaine,LONGUEUR_LABY,sizeof(LONGUEUR_LABY));
		fputs(chaine,file);
		fputc(' ',file);
		sprintf(mot,"%i",longueur_labyrinthe);
		memcpy(chaine,mot,sizeof(mot));
		fputs(chaine,file);
		fputc('\n',file);

		memcpy(chaine,LARGEUR_LABY,sizeof(LARGEUR_LABY));
		fputs(chaine,file);
		fputc(' ',file);
		sprintf(mot,"%i",largeur_labyrinthe);
		memcpy(chaine,mot,sizeof(mot));
		fputs(chaine,file);
		fputc('\n',file);

		memcpy(chaine,NB_FACETTE_MAX,sizeof(NB_FACETTE_MAX));
		fputs(chaine,file);
		fputc(' ',file);
		sprintf(mot,"%i",nb_fac_max);
		memcpy(chaine,mot,sizeof(mot));
		fputs(chaine,file);
		fputc('\n',file);

		memcpy(chaine,F_O_V,sizeof(F_O_V));
		fputs(chaine,file);
		fputc(' ',file);
		sprintf(mot,"%i",fov);
		memcpy(chaine,mot,sizeof(mot));
		fputs(chaine,file);

		fclose(file);
		return 0;
	}
	
	return 1;
}