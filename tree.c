#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "tree.h"

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

void addNode(p_tree tree, p_move parent_node_path, int parent_depth, t_move move, int nb_sons) {

    p_node new_node = createNode(move, nb_sons, parent_depth++);
    p_node tmp = findNode(parent_node_path, *tree, parent_depth);
    int j = 0;
    while (j < tmp->nbSons) {
        if (tmp->sons[j] == NULL) {
            tmp->sons[j] = new_node;
        }
        j++;
    }
}

p_node findNode(p_move path, t_tree tree, int depth) {
    p_node tmp = tree.root;

    while(tmp->depth != depth) {
        int i = 0;
        while (i < tmp->nbSons) {
            if (tmp->move == tmp->sons[i]->move) {
                tmp = tmp->sons[i];
            }
            i++;
        }
    }
    return tmp;
}