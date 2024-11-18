//
// Created by ABuhl on 24/10/2024.
//

#ifndef UNTITLED1_TREE_H
#define UNTITLED1_TREE_H

#include "node.h"
#include "map.h"

typedef struct s_tree
{
    p_node root;
    int depth;
} t_tree, *p_tree;

void print_t(p_node);
void displayTree(t_tree);

// Créer un arbre vide
t_tree createEmptyTree();

// Supprimer un arbre (pas encore terminée)
void deleteTree(p_tree tree);

// Fonction qui retourne l'adresse d'un noeud à partir de son chemin et sa profondeur (pas encore terminée)
p_node findNode( t_tree tree, p_move path, int depth);

// Fonction d'affchage pour un noeud et ses enfants
void printNodeSon(t_node node);

// Fonction de calcul de puissance
int puissance(int x, int y);

// Fonction qui ajoute un noeud fils à un noeud donné (version la plus avancée, prenant en charge le coût des cases)
void addNode(p_tree tree, p_node node, t_move number_move, t_map map, int max_depth);

// Fonction qui ajoute un noeud fils à un noeud donné pour l'arbre de phase
void addNodeRec(p_tree tree, p_node node, t_map map, int max_depth);

// Fonction pour la création de l'arbre en fonction des mouvements (Méthode 1)
p_tree createTree(h_std_list* phase_move, t_map map, t_localisation loc, int max_depth);

// Fonction d'affchage pour un noeud et ses enfants (incluant plus de détails)
void printNodeSonV2(t_node node);

// Ajoute une racine à un arbre
void addRoot(p_tree tree, t_move move, int nbSon, h_std_list* avails, t_localisation localisation, t_map map);

p_node searchBetterNode(p_node node);

// Recherche le chemin avec le moins de point et renvoie le dernier noeud de celui-ci
p_node searchBetterPathNode(t_tree tree);

// Fonction pour la création de l'arbre en fonction des mouvements (Méthode 2)
p_tree createTreeV2(h_std_list* phase_move, t_map map, t_localisation loc, int max_depth);

void printTree(t_tree tree);

// Fonction qui ajoute un noeud fils à un noeud donné pour l'arbre de phase (Méthode 2)
void addNodeRecV2(p_tree tree, p_node node, t_map map, int max_depth);

// Fonction qui ajoute un noeud fils à un noeud donné (version la plus avancée, prenant en charge le coût des cases) (Méthode 2)
void addNodeV2(p_tree tree, p_node node, t_move number_move, t_map map, int max_depth);

#endif //UNTITLED1_TREE_H