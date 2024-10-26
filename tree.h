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

void deleteTree(p_tree);

void addNode(p_tree tree, p_node node, t_move move); // Ajouter un noeud à l'arbre en donnant l'adresse du noeud parent

p_node findNode(t_tree tree, p_move path, int depth);

#endif //UNTITLED1_TREE_H