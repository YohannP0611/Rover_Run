//
// Created by ABuhl on 24/10/2024.
//

#ifndef UNTITLED1_NODE_H
#define UNTITLED1_NODE_H

#include "list.h"

typedef struct s_node
{
    t_move move; //valeur stocké dans le noeud
    int depth; // profondeur du noeud (profondeur du noeud précedent+1)
    struct s_node **sons;
    int nbSons; // taille physique du tableau
    h_std_list avails; // Liste des mouvements restants
    p_move path; // chemin d'accès au noeud depuis le root
} t_node, *p_node;

t_node *createNode(t_move move, int nb_sons, int depth);

void deleteNode(p_node);

#endif //UNTITLED1_NODE_H
