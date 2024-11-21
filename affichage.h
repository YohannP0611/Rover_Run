#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include "list.h"
#include "map.h"



// Affiche le message de demmarage du jeu
void afficherDemarrage();

// Affiche la localisation du robot et les coordonées de la phase
void afficherInfosRobot(t_localisation robot_loc, t_position base_station_loc);

// Affiche la liste des mouvements disponibles dans la phase
void afficherMouvements(h_std_list move_list, int nbMoveSelect);

// Affiche le message de début de phase
void afficherDebutPhase(int phase);

// Affiche la carte avec les coûts de chaque cases
void afficherCarteAvecCouts(t_map map);

// Affiche le résultat de fin de phase
void PrintEnd(int success);

void afficherProgression(int pourcentage);

// Affiche le menu du jeu
void afficherMenu(t_map* map, int* nbMaxMove, int* nbMoveSelect, int* methode);

#endif //AFFICHAGE_H
