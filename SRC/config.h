// Gestion configuration

#ifndef _DEFINE_CONFIG_H
#define _DEFINE_CONFIG_H

// Initialise la configuration par default
void initConfig();

// Tente de charger le fichier configuration
// Renvoie 0 si le fichier � bien �t� charg�, 1 sinon
int loadFichierConfig();

// Tente de sauvegarder le fichier configuration
// Renvoie 0 si le fichier � bien �t� enregistrer, 1 sinon
int saveFichierConfig();

#endif
