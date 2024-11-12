#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "tree.h"
#include "list.h"

#include <time.h>

// Créer un arbre vide
t_tree createEmptyTree() {
    t_tree tree;
    tree.root = NULL;
    return tree;
}

// Supprimer un arbre (pas encore terminée)
void deleteTree(p_tree tree) {
    if(tree->root != NULL) {
        deleteNode(tree->root);
        printf("Arbe supprimé\n");
    }
}

// Ajoute une racine à un arbre vide
void addRoot(p_tree tree, t_move move, int nbSon, h_std_list* avails) {

    // Si l'arbre n'a pas encore de racine
    if (tree->root == NULL) {

        // Créer un nouveau noeud
        tree->root = createNode(move, nbSon, 0);
        tree->root->path = (p_move) malloc(sizeof(t_move));

        // Affecter son chemin (pour la racine ce chemin est toujours 0)
        tree->root->path[0] = tree->root->move;

        // Affecter le tableau des mouvements restants
        tree->root->avails = avails;

        // Affecter la profonceur (profondeur de la racie est de 0)
        tree->depth = 0;
    }

    // Si l'arbre a déjà une racine
    else {
        printf("Arbre contenant un root");
    }
}

// Fonction qui ajoute un noeud fils à un noeud donné
void addNode(p_tree tree, p_node node, t_move move) {

    // Pour le cas où l'arbre est vide
    if (tree->root == NULL) {
        printf("Arbre ne contient pas de root\n");
    }

    // Sinon
    else {

        // Si le noeud admet des noeuds fils
        if (node->nbSons > 0) {

            // Création du nouveau noeud (enfant/fils)
            p_node new_node = createNode(move, node->nbSons - 1, node->depth + 1);

            int j = 0;

            // Parcourir le tableau d'adresse vers les noeud enfant
            while (j < node->nbSons ) {

                // Ajout du nouveau noeud fils dans un "emplacement" libre
                if (node->sons[j] == NULL) {
                    node->sons[j] = new_node;

                    // Mise à jour du chemin pour accéder au noeud à partir de la racine de l'arbre
                    for (int k = 0; k < node->depth + 1; k++) {
                        new_node->path[k] = node->path[k];
                    }

                    // Affectation des movements encore disponible (supprime le mouvement qu'on vient d'ajouter)
                    new_node->avails = removeElt(*node->avails, move);


                    // Affectation du nouveau mouvement dans le chemin (chemin du parent + move du noeud actuel)
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

// Fonction qui retourne l'adresse d'un noeud à partir de son chemin et sa profondeur (pas encore terminée)
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

// Fonction d'affchage pour un noeud et ses enfants
void printNodeSon(t_node node) {

    // Affiche le noeud indenté en fonction de son nombre de fils
    printNode(node, ((node.nbSons * 5 + 7 * (node.nbSons - 1)) / 2) - 1);


    // Afficher le n° de chaque noeud fils avec indentation
    for (int i = 0; i < node.nbSons; i++) {
            printf("[N%d@]", i+1);
            //printPath(node.sons[i]->path, node.sons[i]->depth);
            if (i<node.nbSons-1) {
                printf("-------");
            }

    }


    printf("\n");


    // Affichage prédeterminé de chaque noeud fils avec indentation
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


    // Afficher le mouvement de chaque noeud fils avec indentation
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

// Fonction d'affichae d'un rang de l'abre avec profondeur donnée (pas encore finie)
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

// Fonction pour la création de l'arbre en fonction des mouvements
p_tree createPhaseTree(h_std_list* phase_move) {

    // Création de l'arbre vide
    p_tree tree = (p_tree) malloc(sizeof(t_tree));
    *tree = createEmptyTree();

    // Définition du nombre de noeuds fils de la racine (profondeur de l'arbre)
    int nbMove = countEltHList(*phase_move);

    // Ajout de la racine
    addRoot(tree, U_TURN, nbMove, phase_move);

    // Appel de la fonction récursive pour la création de tous les noeuds
    addPhaseNode(tree, tree->root);

    return tree;

}

// Fonction qui ajoute un noeud fils à un noeud donné pour l'arbre de phase
void addPhaseNode(p_tree tree, p_node node) {

    // Si le noeud n'admet plus de noeud fils
    if (node->nbSons < 1) {
        return;
    }

    // Sinon
    else {

        // Ajout des noeuds fils en fonction des mouvements restants
        for (int i = 0; i < node->nbSons; i++) {
            addNode(tree, node, findElt(*node->avails, i));
        }

        // Appel récursif de la fonction pour constuire l'abre entier
        for (int i = 0; i < node->nbSons; i++) {
            addPhaseNode(tree, node->sons[i]);
        }
    }
}

// Fonction d'affichage des noeuds de l'arbre de Phase
void printPhaseTree(t_tree tree) {

    // Appel de la fonction récursive pour l'affichage de tous les noeuds
    printPhaseNode(*tree.root);

}

// Fonction qui ajoute un noeud fils à un noeud donné pour l'arbre de phase
void printPhaseNode(t_node node) {

    // Si le noeud n'a plus de fils
    if (node.nbSons == 0) {
        return;
    }

    // Sinon
    else {

        // Double sécurité
        if (node.nbSons > 0) {

            // Affichage des noeuds fils de chaque noeud
            for (int i = 0; i < node.nbSons; i++) {
                printNodeSon(*node.sons[i]);
            }

            // Appel récursif de la fonction
            for (int i = 0; i < node.nbSons; i++) {
                printPhaseNode(*node.sons[i]);
            }
        }
    }
}