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
    node->case_cost = 65000;



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

// Supprimer un noeud (récursivement dans le cas où le noeud a des enfants)
void deleteNode(p_node node) {
    if (node == NULL) {
        return;
    }

    // Suppression récursive de tous les noeuds enfants
    for (int i = 0; i < node->nbSons; i++) {
        deleteNode(node->sons[i]);
    }

    // Libération de la mémoire allouée pour les fils, le chemin et le mouvement
    free(node->sons);
    free(node->path);
    free(node->char_move);

    // Libération de la mémoire du noeud lui-même
    free(node);
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
        printPath(node);
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
void printPath(t_node node) {

    printf("[{");
    int i = 0;
    while (i != node.depth) {

        printf("%d-", node.path[i]);
        i++;
    }

    printf("%d}@]", node.path[node.depth]);
}

// Fonction pour d'indentation
void print_indent(int nb) {
    for(int i = 0; i<nb; i++) {
        printf(" ");
    }
}

// Affichage d'un noeud (Méthode 2)
void printNodeV2(t_node node, int indent) {

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

        // Affichage de son cout de case
        print_indent(indent);
        printf("[*%d]\n", node.case_cost);

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
        printPath(node);
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
        printf("[nbMove : %d]\n", node.move);
        print_indent(indent);
        printf("[%s]\n", node.char_move);

        // Affichage de son nombre de fils total
        print_indent(indent);
        printf("[nbSons : %d]\n", node.nbSons);

        // Affichage de son cout de case
        print_indent(indent);
        printf("{depth : %d}\n", node.depth);

        // Affichage de son cout de case
        print_indent(indent);
        printf("[*%d]\n", node.case_cost);

        // Affichage coordonée x
        print_indent(indent);
        printf("/x : %d\\\n", node.localisation.pos.x);

        // Affichage coordonée y
        print_indent(indent);
        printf("\\y : %d/\n", node.localisation.pos.y);

        // Affichage des mouvements restants
        if (node.nbSons > 0) {
            print_indent(indent);
            displayHList(*node.avails);
            printf("\n");
        }

    }

}