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
    for (int i = 0; i < map.y_max; i++)
    {
        for (int j = 0; j < map.x_max; j++)
        {
            printf("%-5d ", map.costs[i][j]);
        }
        printf("\n");
    }
    displayMap(map);

    printf("\n\n\n");

    int nbMaxMove = 4;

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


    printf("\n\n\n");printf("\n\n\n");printf("\n\n\n");printf("\n\n\n");
    printPhaseTree(*phase_tree);

    return 0;
}
