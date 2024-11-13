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

// Ajoute une racine à un arbre vide
void addRoot(p_tree tree, t_move move, int nbSon, h_std_list* avails);

// Fonction qui ajoute un noeud fils à un noeud donné
void addNode(p_tree tree, p_node node, t_move number_move);

// Fonction qui retourne l'adresse d'un noeud à partir de son chemin et sa profondeur (pas encore terminée)
p_node findNode( t_tree tree, p_move path, int depth);

// Fonction d'affchage pour un noeud et ses enfants
void printNodeSon(t_node node);

// Fonction d'affichae d'un rang de l'abre avec profondeur donnée (pas encore finie)
void printTreeDepthNode(t_tree tree, int depth);

// Fonction de calcul de puissance
int puissance(int x, int y);

// Fonction pour la création de l'arbre en fonction des mouvements
p_tree createPhaseTree(h_std_list* phase_move);

// Fonction qui ajoute un noeud fils à un noeud donné pour l'arbre de phase
void addPhaseNode(p_tree tree, p_node node);

// Fonction d'affichage des noeuds de l'arbre de Phase
void printPhaseTree(t_tree tree);

// Fonction qui ajoute un noeud fils à un noeud donné pour l'arbre de phase
void printPhaseNode(t_node node);

void addCostCaseNode(p_tree tree, p_node node, t_move number_move, t_map map);

void addCostCasePhaseNode(p_tree tree, p_node node, t_map map);

p_tree createCostCasePhaseTree(h_std_list* phase_move, t_map map, t_localisation loc);

void printCostCaseNodeSon(t_node node);

void addCostRoot(p_tree tree, t_move move, int nbSon, h_std_list* avails, t_localisation localisation, t_map map);

#endif //UNTITLED1_TREE_H