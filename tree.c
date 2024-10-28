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

void addNode(p_tree tree, p_node node, t_move move) {

    if (tree->root == NULL) {
        tree->root = node;
        node->path = (p_move) malloc(sizeof(t_move));
        node->path[0] = node->move;
        tree->depth = 0;
    }
    else {

        p_node new_node = createNode(move, node->nbSons-1, node->depth + 1);

        int j = 0;
        while (j < node->nbSons ) {
            if (node->sons[j] == NULL) {
                node->sons[j] = new_node;

                for (int k = 0; k < node->depth + 1; k++) {
                    new_node->path[k] = node->path[k];
                }
                new_node->path[node->depth + 1] = new_node->move;
                if(tree->depth < new_node->depth) {
                    tree->depth = new_node->depth;
                }
                return;
            }
            j++;
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
    if (noeud == NULL) {
        printf("|\nv\n");
        printf("NULL\n");
        printf("\n");
        return;
    }

    // Indentation pour représenter la profondeur du nœud
    for (int i = 0; i < niveau * 5; i++) {

    }

    // Affiche le chemin et la valeur du noeud
    printNode(*noeud, 20);

    // Parcours récursif , des fils
    for (int i = 0; i < noeud->nbSons; i++) {

        // Affichage des branches [L@] pour le premier fils et [RQ] pour les suivants
        printNodeSon(*noeud);


        printf("\n\n\n");

        // Appel récursif pour afficher chaque sous-arbre
        afficher_arbre_recursive(noeud->sons[i], niveau + 1, noeud->sons[i]->path, tree_depth);
    }
}

// Fonction principale pour afficher l'arbre depuis la racine
void afficher_arbre(t_tree tree) {
    if (tree.root == NULL) {
        printf("L'arbre est vide.\n");
        return;
    }
    printf("tree depth : %d\n", tree.depth);
    afficher_arbre_recursive(tree.root, 0, tree.root->path, tree.depth);
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

int puissance(int x, int y)
{
    // Déclaration des variables
    int compteur, resultat;

    compteur = 0;
    resultat = 1;

    while (compteur <= y){
        resultat = resultat * x;
        compteur ++;
    }

    return resultat;
}

void buildTreeMove(p_move movelist, int nbMove) {
    t_tree tree = createEmptyTree();

    addNode(&tree, createNode(U_TURN, nbMove, 0), U_TURN);

    for (int i = 0; i < nbMove; i++) {
        for (int j = 0; j < nbMove; j++) {

        }
    }

}

void buildTreeMoveRec(p_tree tree, p_node node) {

        for (int j = 0; j < node->nbSons; j++) {
            addNode(tree, createNode(U_TURN, node->nbSons-1, 0), U_TURN);
        }


}