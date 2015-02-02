# ProjetSAI
// Projet Universitaire Année 2013/2014
// Faculté des Sciences de Saint-Etienne
// Module : 	Synthse Animation Image
// Professeur : BERNARD Marc
// Auteurs : 	DESHORS Axel - axel.deshors@hotmail.fr
//				CROZE Erwan - erwancroze@gmail.com

Pour ce projet nous devions creer soit un labyrinthe, soit un circuit avec
pour contrainte principale une gestion d'affichage א l'aide d'un 4-arbres.
Nous avons choisi de faire un labyrinthe.

Un fichier de configuration nommי "config.cfg" permet de modifier quelques
parametres tel que la resolution de la fenetre, la sensibilitיe de la souris ou
encore la taille du labyrinthe. Nous avons ajoutי une gestion du temps Jour/Nuit,
la création de d'arbres de diffיrents types alיatoirement autour du labyrinthe,
des nuages parcourant la map et des oiseaux volent aléatoirement

Compilation
	Linux : make test_dir
			make

Deplacement
	Z ou fleche haut : Avancer
	S ou fleche bas : Reculer
	Q ou souris translation gauche : Tourner la vue א gauche
	D ou souris translation droite : Tourner la vue א droite
	A ou fleche gauche : Pas de cotי direction gauche
	E ou fleche droite : Pas de cotי direction droite
	C : Descendre (uniquement avec la gestion des collisions dיsactivי)
	Espace : Monter (uniquement avec la gestion des collisions dיsactivי)
	
Autre
	F1 : Affichage des Axes
	F2 : Blocage/Deblocage de la camera d'affichage par rapport au 4-arbres
	F3 : Desactivation/Activation de la gestion des collisions
	F4 : Mode plein יcran
	F8 : Quitte l'application	
