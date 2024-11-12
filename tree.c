#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "tree.h"
#include "list.h"

#include <time.h>

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

// Ajoute une racine à un arbre vide
void addRoot(p_tree tree, t_move move, int nbSon, h_std_list* avails) {
    if (tree->root == NULL) {
        tree->root = createNode(move, nbSon, 0);
        tree->root->path = (p_move) malloc(sizeof(t_move));
        tree->root->path[0] = tree->root->move;
        tree->root->avails = avails;
        tree->depth = 0;
    }
    else {
        printf("Arbre contenant un root");
    }
}

// Fonction qui ajoute un noeud fils à un noeud donné
void addNode(p_tree tree, p_node node, t_move move) {

    // Si l'arbre est vide
    if (tree->root == NULL) {
        printf("Arbre ne contient pas de root\n");
    }
    else {
        if (node->nbSons > 0) {
            // Création du nouveau noeud (enfant)
            p_node new_node = createNode(move, node->nbSons - 1, node->depth + 1);

            int j = 0;
            while (j < node->nbSons ) {

                // Ajout du nouveau noeud fils
                if (node->sons[j] == NULL) {
                    node->sons[j] = new_node;

                    // Définition du chemin pour accéder au noeud à partir de la racine de l'arbre
                    for (int k = 0; k < node->depth + 1; k++) {
                        new_node->path[k] = node->path[k];
                    }

                    // Affectation des movements encore disponible
                    new_node->avails = removeElt(*node->avails, move);


                    // Affectation du nouveau mouvement dans le chemin
                    new_node->path[node->depth + 1] = new_node->move;

                    // Changement de la profondeur total de l'arbre dans le cas où le nouveau noeud est le plus profond
                    if(tree->depth < new_node->depth) {
                        tree->depth = new_node->depth;
                    }
                    return;
                }
                j++;
            }
        }
    }
}


p_node findNode( t_tree tree, p_move path, int depth) {

    p_node tmp = tree.root;

    if (tmp->sons == NULL) {
        return tmp;
    }

    int j = 0;
    while(j < depth) {

            int i = 0;

            while (i < tmp->nbSons) {

                if (tmp->sons[i] != NULL) {

                    if (tmp->path[j] == tmp->sons[i]->move) {
                        tmp = tmp->sons[i];

                    }
                }

                i++;
            }
            j++;
    }
    return tmp;
}


// Fonction récursive pour afficher l'arbre
void afficher_arbre_recursive(p_node noeud, int niveau, p_move chemin, int tree_depth) {

}

void printNodeSon(t_node node) {

    printNode(node, ((node.nbSons * 5 + 7 * (node.nbSons - 1)) / 2) - 1);
    for (int i = 0; i < node.nbSons; i++) {
            printf("[N%d@]", i+1);
            //printPath(node.sons[i]->path, node.sons[i]->depth);
            if (i<node.nbSons-1) {
                printf("-------");
            }

    }
    printf("\n");
    for (int i = 0; i < node.nbSons; i++) {
        printf("   |");
        printf("        ");
    }
    printf("\n");
    for (int i = 0; i < node.nbSons; i++) {
        printf("   v");
        printf("        ");
    }
    printf("\n");
    for (int i = 0; i < node.nbSons; i++) {
        if (node.sons[i] != NULL) {
            printf("  [%d]", node.sons[i]->move);
        } else {
            printf(" NULL");
        }
        printf("       ");
    }
    printf("\n");

}

void printTreeDepthNode(t_tree tree, int depth) {
    t_node node = *tree.root;
    print_indent((5 * puissance(node.nbSons, tree.depth - depth) + 7 * (puissance(node.nbSons, tree.depth - depth) - 1)) / 2);

    for (int i = 0; i < node.nbSons; i++) {
        printf("[N%d@]", i+1);
        //printPath(node.sons[i]->path, node.sons[i]->depth);
        if (i<node.nbSons-1) {
            for (int j = 0; j < (5 * puissance(node.nbSons, tree.depth - depth) + 7 * (puissance(node.nbSons, tree.depth - depth) - 1)) / 2; j++) {
                printf("-");
            }
            printf("-------");
        }

    }
    printf("\n");
    print_indent((5 * puissance(node.nbSons, tree.depth - depth) + 7 * (puissance(node.nbSons, tree.depth - depth) - 1)) / 2);

    for (int i = 0; i < node.nbSons; i++) {
        printf("   |");
        for (int j = 0; j < (5 * puissance(node.nbSons, tree.depth - depth) + 7 * (puissance(node.nbSons, tree.depth - depth) - 1)) / 2; j++) {
            printf(" ");
        }
        printf("        ");
    }
    printf("\n");
    print_indent((5 * puissance(node.nbSons, tree.depth - depth) + 7 * (puissance(node.nbSons, tree.depth - depth) - 1)) / 2);

    for (int i = 0; i < node.nbSons; i++) {
        printf("   v");
        for (int j = 0; j < (5 * puissance(node.nbSons, tree.depth - depth) + 7 * (puissance(node.nbSons, tree.depth - depth) - 1)) / 2; j++) {
            printf(" ");
        }
        printf("        ");
    }
    printf("\n");
    print_indent((5 * puissance(node.nbSons, tree.depth - depth) + 7 * (puissance(node.nbSons, tree.depth - depth) - 1)) / 2);

    for (int i = 0; i < node.nbSons; i++) {
        if (node.sons[i] != NULL) {
            printf("  [%d]", node.sons[i]->move);
        } else {
            printf(" NULL");
        }
        for (int j = 0; j < (5 * puissance(node.nbSons, tree.depth - depth) + 7 * (puissance(node.nbSons, tree.depth - depth) - 1)) / 2; j++) {
            printf(" ");
        }
        printf("       ");
    }
    printf("\n");
    if (depth < tree.depth) {
        printTreeDepthNode(tree, depth+1);
    }
}

// Fonction de calcul de puissance
int puissance(int x, int y) {
    int compteur, resultat;

    compteur = 0;
    resultat = 1;

    while (compteur <= y){
        resultat = resultat * x;
        compteur ++;
    }

    return resultat;
}

p_tree createPhaseTree(h_std_list* phase_move) {

    p_tree tree = (p_tree) malloc(sizeof(t_tree));

    *tree = createEmptyTree();

    int nbMove = countEltHList(*phase_move);

    addRoot(tree, U_TURN, nbMove, phase_move);

    addPhaseNode(tree, tree->root);

    return tree;

}

// Fonction qui ajoute un noeud fils à un noeud donné pour l'arbre de phase
void addPhaseNode(p_tree tree, p_node node) {

    if (node->nbSons < 1) {
        return;
    }
    else {

        for (int i = 0; i < node->nbSons; i++) {
            addNode(tree, node, findElt(*node->avails, i));
        }
        for (int i = 0; i < node->nbSons; i++) {
            addPhaseNode(tree, node->sons[i]);
        }
    }
}

void printPhaseTree(t_tree tree) {

    printPhaseNode(*tree.root);
}

// Fonction qui ajoute un noeud fils à un noeud donné pour l'arbre de phase
void printPhaseNode(t_node node) {

    if (node.nbSons == 0) {
        return;
    }
    else {
        if (node.nbSons > 0) {
            for (int i = 0; i < node.nbSons; i++) {

                printNodeSon(*node.sons[i]);
            }
            for (int i = 0; i < node.nbSons; i++) {

                printPhaseNode(*node.sons[i]);


            }
        }
    }
}