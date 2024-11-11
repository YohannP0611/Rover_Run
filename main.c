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

    int nbMaxMove = 6;

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

    // Sélectionner 10 éléments
    for (int i = 0; i < nbMaxMove; i++) {
        int selected = selectRandomMove(items, nbMove);
        printf("Element selectionne : %d\n", selected);
    }

    printf("\n\n\n");

    t_tree tree = createEmptyTree();
    p_node node = createNode(U_TURN, nbMaxMove, 0);

    addNode(&tree, node, U_TURN, nbMaxMove);

    addNode(&tree, node, F_10, nbMaxMove-1);
    addNode(&tree, node, F_20, nbMaxMove-1);


    addNode(&tree, node->sons[0], F_30, nbMaxMove-2);

    addNode(&tree, node->sons[1], B_10, nbMaxMove-2);

    addNode(&tree, node->sons[1], T_LEFT, nbMaxMove-2);


    printNodeSon(*node);
    printf("\n\n\n");

    printNodeSon(*node->sons[1]);

    printf("\n\n\n");
    printNode(*node->sons[0]->sons[0], 1);


    return 0;
}
