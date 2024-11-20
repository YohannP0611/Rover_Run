//
// Created by mendo on 20/11/2024.
//

#include "affichage.h"

#include "node.h"

// Affiche le message de demmarage du jeu
void afficherDemarrage() {
    printf("*************************************\n");
    printf("*        DEMARRAGE DU JEU...        *\n");
    printf("*************************************\n");
    for (int i = 0; i < 3; i++) {
        printf(".");
        fflush(stdout);
        _sleep(1);
    }
    printf("\n\n");
}

// Affiche la localisation du robot et les coordonées de la phase
void afficherInfosRobot(t_localisation robot_loc, t_position base_station_loc) {
    printf("*************************************\n");
    printf("*       Informations du robot       *\n");
    printf("*************************************\n");
    printf("* Orientation actuelle : %s\t    *\n", getOrientationAsString(robot_loc.ori));
    printf("* Position actuelle :               *\n");
    printf("*\tx : %d    \t\t    *\n", robot_loc.pos.x);
    printf("*\ty : %d    \t\t    *\n", robot_loc.pos.y);
    printf("*                                   *\n");
    printf("* Position de la base :             *\n");
    printf("*\tx : %d    \t\t    *\n", base_station_loc.x);
    printf("*\ty : %d    \t\t    *\n", base_station_loc.y);
    printf("*************************************\n\n");
}

// Affiche la liste des mouvements disponibles dans la phase
void afficherMouvements(h_std_list move_list, int nbMoveSelect) {
    printf("=====================================\n");
    printf("|    Mouvements disponibles (%d)     |\n", nbMoveSelect);
    printf("=====================================\n");
    printf("| %-10s | %-10s\n", "Numero", "Mouvement\t    |");
    printf("-------------------------------------\n");

    p_cell tmp = move_list.head;
        while (tmp != NULL) {
            printf("| %-10.1d | %-10s\t    |\n", tmp->move, getMoveAsString(tmp->move));
            tmp = tmp->next;
        }

    printf("-------------------------------------\n\n");
}

// Affiche le message de début de phase
void afficherDebutPhase(int phase) {
    printf("=========================================\n");
    printf("          Debut de la phase %d\n", phase);
    printf("=========================================\n\n");
}

// Affiche la carte avec les coûts de chaque cases
void afficherCarteAvecCouts(t_map map) {

    printf("*************************************\n");
    printf("*          Couts de la carte        *\n");
    printf("*************************************\n\n");

    for (int i = 0; i < map.y_max; i++) {
        for (int j = 0; j < map.x_max; j++) {
            printf("%-5d ", map.costs[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");
    printf("-------------------------------------\n\n\n");
}

// Affiche le résultat de fin de phase
void PrintEnd(int success) {
        printf("===============================================\n");
    if (success) {
        printf("              MISSION REUSSIE !\n");
    } else {
        printf("MISSION ECHOUEE : le robot est perdu ou detruit\n");
    }
        printf("===============================================\n\n");

}

void afficherProgression(int pourcentage) {
    printf("[");
    int completed = pourcentage / 10; // Une case pour chaque 10%
    for (int i = 0; i < 10; i++) {
        if (i < completed) {
            printf("#"); // Rempli
        } else {
            printf(" "); // Vide
        }
    }
    printf("] %d%%\n", pourcentage);
}

// Affiche le menu du jeu
void afficherMenu(t_map map, int* nbMaxMove, int* nbMoveSelect) {
    int choix = 0;
    do {
        printf("\n\n\n");
        printf("\n\n\n");
        printf("*********************************\n");
        printf("*        Rover Run - Menu       *\n");
        printf("*********************************\n");
        printf("* 1. Jouer                      *\n");
        printf("* 2. Instructions               *\n");
        printf("* 3. Options                    *\n");
        printf("* 4. Quitter                    *\n");
        printf("*********************************\n");
        printf("\n\n\n");
        printf("Entrez votre choix : ");
        scanf("%d", &choix);
        for (int i = 0; i < 15; i++) {
            printf("\n\n\n");
        }


        switch (choix) {
            case 1: jouer(map, *nbMaxMove, *nbMoveSelect); break;
            case 2: instructions(); break;
            case 3: options(nbMaxMove, nbMoveSelect); break;
            case 4: quitter(); break;
            default:
                printf("Choix invalide. Veuillez réessayer.\n");
            getchar(); // Pause pour afficher le message
            break;
        }

    } while (choix != 4);
}