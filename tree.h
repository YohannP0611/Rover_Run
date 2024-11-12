//
// Created by ABuhl on 24/10/2024.
//

#ifndef UNTITLED1_TREE_H
#define UNTITLED1_TREE_H

#include "node.h"

typedef struct s_tree
{
    p_node root;
    int depth;
} t_tree, *p_tree;

void print_t(p_node);
void displayTree(t_tree);

t_tree createEmptyTree();

void deleteTree(p_tree);

void addRoot(p_tree tree, t_move move, int nbSon, h_std_list* avails);

void addNode(p_tree tree, p_node node, t_move move); // Ajouter un noeud à l'arbre en donnant l'adresse du noeud parent

p_node findNode(t_tree tree, p_move path, int depth);

void afficher_arbre(t_tree tree);

void afficher_arbre_recursive(p_node noeud, int niveau, p_move chemin, int tree_depth);

void printNodeSon(t_node node);

void printTreeDepthNode(t_tree tree, int depth);

int puissance(int x, int y);

p_tree createPhaseTree(h_std_list* phase_move);

// Fonction qui ajoute un noeud fils à un noeud donné pour l'arbre de phase
void addPhaseNode(p_tree tree, p_node node);

void printPhaseTree(t_tree tree);

void printPhaseNode(t_node node);

#endif //UNTITLED1_TREE_H