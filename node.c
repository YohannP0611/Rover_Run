#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "node.h"

t_node *createNode(int value, int nb_sons, int depth) {
    t_node* node = (t_node*) malloc(sizeof (t_node));
    node->value = value;
    node->nbSons = nb_sons;
    node->depth = depth;
    node->sons = (t_node **)malloc(nb_sons*sizeof(t_node *));
    for (int i=0; i <nb_sons; i++)
    {
        node->sons[i]=NULL;
    }
    return node;
}
