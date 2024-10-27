#include <stdio.h>
#include "map.h"
#include "tree.h"

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

    t_tree tree = createEmptyTree();
    p_node node = createNode(U_TURN, 2, 0);
    addNode(&tree, node, U_TURN);

    addNode(&tree, node, F_10);
    addNode(&tree, node, F_20);


    addNode(&tree, node->sons[0], F_30);

    addNode(&tree, node->sons[1], B_10);

    addNode(&tree, node->sons[1], T_LEFT);

    printNodeSon(*node->sons[1], 0);

    printf("\n\n\n");
    afficher_arbre(tree);

    return 0;
}
