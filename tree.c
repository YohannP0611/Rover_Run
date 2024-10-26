#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "tree.h"

#include <time.h>

t_tree createEmptyTree() {
    t_tree tree;
    tree.root = NULL;
    return tree;
}

void deleteTree(p_tree tree) {
    if(tree->root != NULL) {
        deleteNode(tree->root);
        printf("Arbe supprimé\n");
    }
}

void addNode(p_tree tree, p_node node, t_move move) {

    if (tree->root == NULL) {
        tree->root = node;
        node->path = (p_move) malloc(sizeof(t_move));
        node->path[0] = node->move;
    }
    else {

        p_node new_node = createNode(move, node->nbSons, node->depth + 1);
        p_node tmp = findNode(*tree, node->path, node->depth);
        printf("bonjour");

        int j = 0;
        while (j < tmp->nbSons ) {
            if (tmp->sons[j] == NULL) {
                tmp->sons[j] = new_node;

                for (int k = 0; k < tmp->depth + 1; k++) {
                    new_node->path[k] = tmp->path[k];
                }
                new_node->path[tmp->depth + 1] = new_node->move;
                printNode(*new_node);
                return;
            }
            j++;
        }
    }
}



p_node findNode( t_tree tree, p_move path, int depth) {

    p_node tmp = tree.root;

    if (tmp->sons == NULL) {
        return tmp;
    }

    int j = 0;
    while(j < depth) {

            int i = 0;

            while (i < tmp->nbSons) {

                if (tmp->sons[i] != NULL) {

                    if (tmp->path[j] == tmp->sons[i]->move) {
                        printf("r");
                        tmp = tmp->sons[i];

                    }
                }

                i++;
            }
            j++;
    }
    return tmp;
}