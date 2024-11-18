#include <stdio.h>
#include "map.h"
#include "tree.h"
#include <time.h>


int main() {

    t_map map;

    // Fonction pour créer une carte aléatoirement (peut faire crash le programme de temps en temps)
    createRandomMap("..\\maps\\example2.map", randomNumber(7, 16), randomNumber(6, 15));

    // The following preprocessor directive checks if the code is being compiled on a Windows system.
    // If either _WIN32 or _WIN64 is defined, it means we are on a Windows platform.
    // On Windows, file paths use backslashes (\), hence we use the appropriate file path for Windows.
#if defined(_WIN32) || defined(_WIN64)
    map = createMapFromFile("..\\maps\\example1.map");
#else
    map = createMapFromFile("../maps/example1.map");
#endif

    printf("Map created with dimensions %d x %d\n", map.y_max, map.x_max);
    for (int i = 0; i < map.y_max; i++)
    {
        for (int j = 0; j < map.x_max; j++)
        {
            printf("%d ", map.soils[i][j]);
        }
        printf("\n");
    }
    // printf the costs, aligned left 5 digits
    for (int i = 0; i < map.y_max; i++)
    {
        for (int j = 0; j < map.x_max; j++)
        {
            printf("%-5d ", map.costs[i][j]);
        }
        printf("\n");
    }
    displayMap(map);

    int running = 0;



        printf("\n\n\n");



        srand(time(NULL));


        // Exemple de tableau d'éléments avec leurs pourcentages initiaux
        tabMove items[] = {
            {F_10, 20.0},
            {F_20, 15.0},
            {F_30, 20.0},
            {B_10, 15.0},
            {T_RIGHT, 10.0},
            {T_LEFT, 10.0},
            {U_TURN, 10.0}
        };
        // Nombre de mouvements au total
        int nbMove = 7;

        // Nombre de mouvements tiré
        int nbMaxMove = 5;

        // Nombre de mouvement sélectionné
        int nbMoveSelect = 1;

        printf("Nombre de tirage pour les mouvement :");
        scanf(" %d", &nbMaxMove);

        printf("Nombre de mouvement disponible dans une phase :");
        scanf(" %d", &nbMoveSelect);



        printf("\n\n\n");

        // Définition des données initiales
        int x_init = randomNumber(0, map.x_max-1);
        int y_init = randomNumber(0, map.y_max-1);
        t_orientation  orientation_init = randomNumber(0, 3);

        // Définition des coordonnées de base du robot
        t_localisation robot_loc = loc_init(x_init, y_init, orientation_init);



        // Position de la base
        t_position base_station_loc = getBaseStationPosition(map);

        displayMap(map);

        // printf the costs, aligned left 5 digits
        for (int i = 0; i < map.y_max; i++)
        {
            for (int j = 0; j < map.x_max; j++)
            {
                printf("%-5d ", map.costs[i][j]);
            }
            printf("\n");
        }

        printf("\n\n\n");

        t_localisation root_loc_auto = loc_init(x_init, y_init, orientation_init);

        t_localisation root_loc = loc_init(x_init, y_init, orientation_init);



    if (running == 1) {

        h_std_list* move_list = createListEmpty();

        // Sélectionner n éléments
        for (int i = 0; i < nbMaxMove; i++) {
            t_move selected = selectRandomMove(items, nbMove);
            addTailList(move_list, selected);
            printf("Element selectionne : %d\n", selected);
        }






    }

    while (running == 0) {

        while (robot_loc.pos.x != base_station_loc.x || robot_loc.pos.y != base_station_loc.y) {

            printf("Debut de la phase...\n\n\n");

            printf("Orientation : %s\n", getOrientationAsString(robot_loc.ori));
            printf("Point de depart du robot au debut de la phase :\n\tx : %d\n\ty : %d\n\n", robot_loc.pos.x,
                   robot_loc.pos.y);

            printf("Coordonees de la base :\n\tx : %d\n\ty : %d\n\n", base_station_loc.x, base_station_loc.y);

            h_std_list *move_list = createListEmpty();

            // Sélectionner n éléments
            for (int i = 0; i < nbMaxMove; i++) {
                t_move selected = selectRandomMove(items, nbMove);
                addTailList(move_list, selected);
                printf("Element selectionne : %d\n", selected);
            }

            char guidage;

            printf("\n\n\n\nActiver le systeme de guidage automatique ? [Y/n] : ");
            scanf(" %c", &guidage);
            printf("\n");

            if (guidage == 'Y') {

                // Création de l'arbre de phase (Méthode 1)
                p_tree ptr_phase_tree_auto = createTree(move_list, map, robot_loc, nbMoveSelect);

                //p_tree ptr_phase_tree_auto = createTreeV2(move_list, map, robot_loc, nbMoveSelect);

                // Détermination du noeud avec le chemin le moins coûteux
                p_node node = searchBetterPathNode(*ptr_phase_tree_auto);


                if (node->case_cost > 12999) {
                    printf("Aucun chemin ne mene a la base (perte de signal du robot ou destruction de celui-ci\n");
                } else {
                    printf("Le chemin le moins couteux est : ");

                    // Affichage du chemin
                    printPath(*node);

                    printf("\n\n");
                    printNodeSonV2(*node);

                    // Affichage de la suite de mouvement correspondante
                    printf("\n\nSoit la suite de mouvement : [");
                    for (int i = 0; i < node->depth; i++) {
                        printf("%s - ", getMoveAsString(node->path[i]));
                    }
                    printf("%s]\n\n\n", getMoveAsString(node->path[node->depth]));

                    // Affectation des nouvelles coordonnées pour le robot (coordonnées de la case de fin de phase)
                    robot_loc = loc_init(node->localisation.pos.x, node->localisation.pos.y, node->localisation.ori);
                }

                if (robot_loc.pos.x != base_station_loc.x || robot_loc.pos.y != base_station_loc.y) {
                    printf("----------------------------------------------------------------\n\n\n");
                }

            } else {
                printf("Activation negative... ");

                // Création de l'arbre de phase manuel
                t_tree phase_tree_manuel = createEmptyTree();
                addRoot(&phase_tree_manuel, ROOT, 1, move_list, robot_loc, map);

                p_node node = phase_tree_manuel.root;

                while (phase_tree_manuel.depth != nbMoveSelect || robot_loc.pos.x != base_station_loc.x || robot_loc.pos.y != base_station_loc.y) {

                    printf("Orientation : %s\n", getOrientationAsString(robot_loc.ori));
                    printf("Point de depart du robot au debut de la phase :\n\tx : %d\n\ty : %d\n\n", robot_loc.pos.x,
                           robot_loc.pos.y);

                    printf("Coordonees de la base :\n\tx : %d\n\ty : %d\n\n", base_station_loc.x, base_station_loc.y);

                    printf("Choisir un mouvement [numéro du mouvement dans la liste] :");

                    int movement;

                    scanf(" %d", &movement);

                    addNodeV2(&phase_tree_manuel, node, findElt(*move_list, movement), map, nbMoveSelect);

                    // Détermination du noeud avec le chemin le moins coûteux
                    node = searchBetterPathNode(phase_tree_manuel);


                    if (node->case_cost > 12999) {
                        printf("Aucun chemin ne mene a la base (perte de signal du robot ou destruction de celui-ci\n");
                    } else {
                        printf("Le chemin le moins couteux est : ");

                        // Affichage du chemin
                        printPath(*node);

                        printf("\n\n");
                        printNodeSonV2(*node);

                        // Affichage de la suite de mouvement correspondante
                        printf("\n\nSoit la suite de mouvement : [");
                        for (int i = 0; i < node->depth; i++) {
                            printf("%s - ", getMoveAsString(node->path[i]));
                        }
                        printf("%s]\n\n\n", getMoveAsString(node->path[node->depth]));

                        // Affectation des nouvelles coordonnées pour le robot (coordonnées de la case de fin de phase)
                        robot_loc = loc_init(node->localisation.pos.x, node->localisation.pos.y, node->localisation.ori);
                    }

                    node = node->sons[node->nbSons - 1];
                }

                if (robot_loc.pos.x != base_station_loc.x || robot_loc.pos.y != base_station_loc.y) {
                    printf("----------------------------------------------------------------\n\n\n");
                }

            }
        }


        displayMap(map);

        running = -1;

    }
    return 0;
}
