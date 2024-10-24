//
// Created by ABuhl on 24/10/2024.
//

#ifndef UNTITLED1_TREE_H
#define UNTITLED1_TREE_H

#include "node.h"

typedef struct s_tree
{
    p_node root;
} t_tree, *p_tree;

void print_t(p_node);
void displayTree(t_tree);

t_tree createEmptyTree();

#endif //UNTITLED1_TREE_H
