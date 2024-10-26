#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "node.h"

t_node *createNode(t_move move, int nb_sons, int depth) {
    t_node* node = (t_node*) malloc(sizeof (t_node));
    node->move = move;
    node->nbSons = nb_sons;
    node->depth = depth;
    node->sons = (t_node **)malloc(nb_sons*sizeof(t_node *));
    node->path = NULL;
    for (int i=0; i <nb_sons; i++)
    {
        node->sons[i]=NULL;
    }
    return node;
}

void deleteNode(p_node node) {
    if(node->nbSons == 0) {
        free(node->sons);
        free(node);
    }
    else {
        deleteNode(node->sons[node->nbSons - 1]);
    }
}
