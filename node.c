#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "node.h"

// Créer un nouveau noeud
t_node *createNode(t_move move, int nb_sons, int depth) {

    // Allocation de l'espace mémoire nécessaire
    t_node* node = (t_node*) malloc(sizeof (t_node));

    // Initialisation de tous les paramètres
    node->move = move;
    node->nbSons = nb_sons;
    node->depth = depth;

    // Allocation des espaces mémoires nécessaires aux différents tableaux
    node->sons = (t_node **)malloc(nb_sons*sizeof(t_node *));
    node->path = (t_move *)malloc((depth+1)*sizeof(t_move));
    node->char_move = (char*)malloc(8*sizeof(char));
    strcpy(node->char_move, getMoveAsString(move));


    // Mise à NULL de tous les fils du neoud
    for (int i=0; i <nb_sons; i++)
    {
        node->sons[i]=NULL;
    }
    return node;
}

// Supprimer un noeud (pas encore récursif dans le cas où le neoud a des enfants)
void deleteNode(p_node node) {

    // Si le noeud n'a pas de fils
    if(node->nbSons == 0) {
        free(node->sons);
        free(node);
    }

    // Sinon
    else {

        // Suppression de ses noeuds enfant (pas encore d'appel récursif)
        deleteNode(node->sons[node->nbSons - 1]);
    }
}

// Affichage d'un noeud
void printNode(t_node node, int indent) {

    // Si le noeud est la racine
    if(node.depth == 0) {

        // Affichage de la racine
        print_indent(indent);
        printf("[root@]\n");

        // Affichage des éléments visuels
        print_indent(indent);
        printf("|\n");
        print_indent(indent);
        printf("v\n");

        // Affichage de son mouvement
        print_indent(indent);
        printf("[%d]\n", node.move);
        print_indent(indent);
        printf("[%s]\n", node.char_move);

        // Affichage de son nombre de fils total
        print_indent(indent);
        printf("[%d]\n", node.nbSons);

        // Affichage des mouvements restants
        if (node.nbSons > 0) {
            print_indent(indent);
            displayHList(*node.avails);
            printf("\n");
        }
    }

    // Sinon
    else {

        // Affichage de son chemin depuis la racine
        print_indent(indent);
        printPath(node.path, node.depth);
        printf("\n");

        // Affichage des éléments visuels
        print_indent(indent);
        printf("|");
        print_indent(indent);
        printf("\n");
        print_indent(indent);
        printf("v");
        printf("\n");



        // Affichage de son mouvement
        print_indent(indent);
        printf("[%d]\n", node.move);
        print_indent(indent);
        printf("[%s]\n", node.char_move);

        // Affichage de son nombre de fils total
        print_indent(indent);
        printf("[%d]\n", node.nbSons);

        // Affichage des mouvements restants
        if (node.nbSons > 0) {
            print_indent(indent);
            displayHList(*node.avails);
            printf("\n");
        }

    }

}

// Fonction d'affichage du chemin du noeud à partir de la racine
void printPath(p_move path, int depth) {

    printf("[{");
    int i = 0;
    while (i != depth) {

        printf("%d-", path[i]);
        i++;
    }

    printf("%d}@]", path[depth]);
}

// Fonction pour d'indentation
void print_indent(int nb) {
    for(int i = 0; i<nb; i++) {
        printf(" ");
    }
}