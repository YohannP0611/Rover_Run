//
// Created by ABuhl on 24/10/2024.
//

#ifndef UNTITLED1_NODE_H
#define UNTITLED1_NODE_H

#include "list.h"

typedef struct s_node
{
    t_move move; //valeur stocké dans le noeud
    char* char_move; // mouvement chaine de caractère
    int case_cost; // coût de la case sur laquelle on arrive
    t_localisation localisation; // localisation du noeud
    int depth; // profondeur du noeud (profondeur du noeud précedent+1)
    struct s_node **sons;
    int nbSons; // taille physique du tableau
    h_std_list* avails; // Liste des mouvements restants
    p_move path; // chemin d'accès au noeud depuis le root
} t_node, *p_node;

// Créer un nouveau noeud
t_node *createNode(t_move move, int nb_sons, int depth);

// Supprimer un noeud (pas encore récursif dans le cas où le neoud a des enfants)
void deleteNode(p_node node);
// Affichage d'un noeud
void printNode(t_node node, int indent);

// Fonction d'affichage du chemin du noeud à partir de la racine
void printPath(t_node node);

// Fonction pour d'indentation
void print_indent(int nb);

void printFullNode(t_node node, int indent);


#endif //UNTITLED1_NODE_H
