#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include "list.h"
#include "map.h"


//////////////////////////
// Fonctions d'affichage//
//////////////////////////

// Affiche le message de demmarage du jeu
void afficherDemarrage();

// Affiche la localisation du robot et les coordonées de la phase
void afficherInfosRobot(t_localisation robot_loc, t_position base_station_loc);

// Affiche la liste des mouvements disponibles dans la phase
void afficherMouvements(h_std_list move_list, int nbMoveSelect);

// Affiche le message de début de phase
void afficherDebutPhase(int phase, t_map map, t_localisation robot_loc);

// Affiche la carte avec les coûts de chaque cases
void afficherCarteAvecCouts(t_map map);

// Affiche le résultat de fin de phase
void AfficherResultats(int success);

// Affiche la progression d'une tâche
void afficherProgression(int pourcentage);

// Affiche le menu du jeu
void afficherMenu(t_map* map, int* nbMaxMove, int* nbMoveSelect, int* methode);




/////////////////////
// Autres fonctions//
/////////////////////

// Fonction de lancement du jeu
void jouer(t_map, int, int, int methode);

// Permet de modifier les options du jeu
void options(int* nbMaxMove, int* nbMoveSelect, t_map* map,int* methode);

// Fonction pour sortir du programme
void quitter();

// Fonction pour modifier les nombres de mouvement tirés et choisis
void demanderNombreMouvements(int* nbMaxMove, int* nbMoveSelect);

// Fonction pour modifier la carte
void modifierCarte(t_map* map);

// Fonction qui concatène le nom du fichier avec le chemin
char* concatPath(const char* path, const char* filename);

#endif //AFFICHAGE_H
