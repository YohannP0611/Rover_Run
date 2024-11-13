#include <stdio.h>
#include "map.h"
#include "tree.h"
#include <time.h>

int main() {
    t_map map = createMapFromFile("..\\maps\\example1.map");
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
    for (int i = 0; i < map.x_max; i++)
    {
        for (int j = 0; j < map.y_max; j++)
        {
            printf("%-5d ", map.costs[j][i]);
        }
        printf("\n");
    }
    displayMap(map);



    int running = 1;

    if (running == 1) {

        printf("\n\n\n");

        int nbMaxMove = 5;

        srand(time(NULL));


        // Exemple de tableau d'éléments avec leurs pourcentages initiaux
        tabMove items[] = {
            {F_10, 30.0},
            {F_20, 25.0},
            {F_30, 20.0},
            {B_10, 15.0},
            {T_RIGHT, 10.0},
            {T_LEFT, 10.0}
        };

        int nbMove = 6;

        h_std_list* move_list = createListEmpty();

        // Sélectionner n éléments
        for (int i = 0; i < nbMaxMove; i++) {
            t_move selected = selectRandomMove(items, nbMove);
            addTailList(move_list, selected);
            printf("Element selectionne : %d\n", selected);
        }

        printf("\n\n\n");

        t_tree tree = createEmptyTree();

        addRoot(&tree, U_TURN, nbMaxMove, move_list);

        displayHList(*tree.root->avails);

        p_node node = tree.root;


        addNode(&tree, node, F_10);

        printf("\n\n");
        displayHList(*tree.root->sons[0]->avails);

        addNode(&tree, node, F_20);

        printf("\n\n");
        displayHList(*tree.root->sons[1]->avails);


        addNode(&tree, node->sons[0], F_30);

        printf("\n\n");
        displayHList(*node->sons[0]->sons[0]->avails);

        addNode(&tree, node->sons[1], B_10);

        printf("\n\n");
        displayHList(*node->sons[1]->sons[0]->avails);

        addNode(&tree, node->sons[1], T_LEFT);

        printf("\n\n");
        displayHList(*node->sons[1]->sons[1]->avails);

        printf("\n\n");
        printNodeSon(*node);
        printf("\n\n\n");

        printNodeSon(*node->sons[1]);

        printf("\n\n\n");
        printNode(*node->sons[0]->sons[0], 1);

        printf("\n\n\n");

        p_tree phase_tree = createPhaseTree(move_list);

        printf("\n\n\n");
        printNodeSon(*phase_tree->root);
        printf("\n\n\n");
        printNodeSon(*phase_tree->root->sons[0]);
        printNodeSon(*phase_tree->root->sons[0]->sons[0]);

        printf("profondeur de l'arbre : %d\n", phase_tree->depth);


        printf("\n\n\n");printf("\n\n\n");printf("\n\n\n");printf("\n\n\n");

        int x_init = 4;
        int y_init = 4;
        t_orientation  orientation_init = SOUTH;

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

        t_localisation root_loc = loc_init(x_init, y_init, orientation_init);
        createCostCasePhaseTree(move_list, map, root_loc);



    }


    if (running == 0) {
        int nbMaxMove = 5;

        srand(time(NULL));


        // Exemple de tableau d'éléments avec leurs pourcentages initiaux
        tabMove items[] = {
            {F_10, 30.0},
            {F_20, 25.0},
            {F_30, 20.0},
            {B_10, 15.0},
            {T_RIGHT, 10.0},
            {T_LEFT, 10.0}
        };

        int nbMove = 6;

        h_std_list* move_list = createListEmpty();

        // Sélectionner n éléments
        for (int i = 0; i < nbMaxMove; i++) {
            t_move selected = selectRandomMove(items, nbMove);
            addTailList(move_list, selected);
            printf("Element selectionne : %d\n", selected);
        }


        int x_init = 3;
        int y_init = 1;
        t_orientation  orientation_init = SOUTH;

        t_tree tree_cost = createEmptyTree();


        addCostRoot(&tree_cost, U_TURN, nbMaxMove, move_list, loc_init(x_init,y_init,orientation_init), map);

        p_node node = tree_cost.root;


        printf("%d\n", node->localisation.pos.x);
        printf("%d\n", node->localisation.pos.x);
        printf("%d\n", map.costs[node->localisation.pos.x][node->localisation.pos.y]);
        printCostCaseNode(*node, 0);

        //addCostCaseNode(&tree_cost, node, F_10, map);

        printf("x : %d\n", node->localisation.pos.x);
        printf("y : %d\n", node->localisation.pos.y);


        printf("valide : %d\n", isValidLocalisation(node->localisation.pos, map.x_max, map.y_max));

        printf("valide : %d\n", isValidLocalisation(node->localisation.pos, map.x_max, map.y_max));

        printf("x : %d\n", node->localisation.pos.x);
        printf("y : %d\n", node->localisation.pos.y);
        printf("cost : %d\n", map.costs[node->localisation.pos.x][node->localisation.pos.y]);
        printf("ori : %s\n", getOrientationAsString(node->localisation.ori));

        addCostCaseNode(&tree_cost, node, T_RIGHT, map);
        printf("\n\n\n");



        printCostCaseNode(*node->sons[0], 0);

        printf("ori : %s\n", getOrientationAsString(node->sons[0]->localisation.ori));

        printf("ori : %s\n", getOrientationAsString(rotate(node->sons[0]->localisation.ori, T_RIGHT)));
        updateLocalisation(&node->sons[0]->localisation, T_RIGHT);
        printf("ori : %s\n", getOrientationAsString(node->sons[0]->localisation.ori));
        updateLocalisation(&node->sons[0]->localisation, F_10);

        printf("x : %d\n", node->sons[0]->localisation.pos.x);
        printf("y : %d\n", node->sons[0]->localisation.pos.y);
        printf("\n\n\n");

        printCostCaseNode(*node->sons[0], 0);
    }
    return 0;
}
