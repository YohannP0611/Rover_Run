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
    p_node node = createNode(U_TURN, 3, 0);
    addNode(&tree, node, U_TURN);
    printNode(*tree.root);

    addNode(&tree, node, F_10);
    addNode(&tree, node, F_20);

    printNode(*tree.root->sons[0]);
    printNode(*tree.root->sons[1]);

    addNode(&tree, node->sons[0], F_30);
    printNode(*tree.root->sons[0]->sons[0]);
    addNode(&tree, node->sons[1], B_10);
    printNode(*tree.root->sons[1]->sons[0]);


    return 0;
}
