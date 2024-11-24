#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "tree.h"
#include "list.h"
#include "map.h"

#include <time.h>

// Créer un arbre vide
t_tree createEmptyTree() {
    t_tree tree;
    tree.root = NULL;
    return tree;
}

// Supprimer un arbre
void deleteTree(p_tree tree) {
    if (tree->root != NULL) {
        deleteNode(tree->root);
        free(tree);
        printf("Arbre supprimé\n");
    }
}

// Fonction qui retourne l'adresse d'un noeud à partir de son chemin et sa profondeur
p_node findNode(t_tree tree, p_move path, int depth) {
    p_node tmp = tree.root;

    if (tmp == NULL) {
        return NULL;
    }

    for (int j = 1; j < depth; j++) {
        int found = 0;
        for (int i = 0; i < tmp->nbSons; i++) {
            if (tmp->sons[i] != NULL && tmp->sons[i]->move == path[j]) {
                tmp = tmp->sons[i];
                found = 1;
                break;
            }
        }
        if (!found) {
            return NULL;
        }
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

// Fonction pour la création de l'arbre en fonction des mouvements (Méthode 1)
p_tree createTree(h_std_list* phase_move, t_map map, t_localisation loc, int max_depth) {

    // Création de l'arbre vide
    p_tree tree = (p_tree) malloc(sizeof(t_tree));
    *tree = createEmptyTree();

    // Définition du nombre de noeuds fils de la racine (profondeur de l'arbre)
    int nbMove = countEltHList(*phase_move);

    // Ajout de la racine
    addRoot(tree, ROOT, nbMove, phase_move, loc, map);

    // Appel de la fonction récursive pour la création de tous les noeuds
    addNodeRec(tree, tree->root, map, max_depth);

    return tree;

}

// Fonction qui ajoute un noeud fils à un noeud donné pour l'arbre de phase
void addNodeRec(p_tree tree, p_node node, t_map map, int max_depth) {

    // Si le noeud n'admet plus de noeud fils
    if (node->nbSons < 1) {
        return;
    }

        // Sinon
    else {

        if (node->depth < max_depth) {

            // Ajout des noeuds fils en fonction des mouvements restants
            for (int i = 0; i < node->nbSons; i++) {

                addNode(tree, node, findElt(*node->avails, i), map, max_depth);

            }

            // Appel récursif de la fonction pour constuire l'abre entier
            for (int i = 0; i < node->nbSons; i++) {
                addNodeRec(tree, node->sons[i], map, max_depth);


            }
        }
    }
}

// Fonction qui ajoute un noeud fils à un noeud donné (version la plus avancée, prenant en charge le coût des cases) (Méthode 1)
void addNode(p_tree tree, p_node node, t_move number_move, t_map map, int max_depth) {

    // Pour le cas où l'arbre est vide
    if (tree->root == NULL) {
        printf("Arbre ne contient pas de root\n");
    }

    // Sinon
    else {

        // Si le noeud admet des noeuds fils
        if (node->nbSons > 0) {

            // Création du nouveau noeud (enfant/fils)
            p_node new_node = createNode(number_move, node->nbSons - 1, node->depth + 1);

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
                    new_node->avails = removeElt(*node->avails, number_move);


                    // Affectation du nouveau mouvement dans le chemin (chemin du parent + number_move du noeud actuel)
                    new_node->path[node->depth + 1] = new_node->move;

                    // Changement de la profondeur total de l'arbre dans le cas où le nouveau noeud est le plus profond
                    if(tree->depth < new_node->depth) {
                        tree->depth = new_node->depth;
                    }

                    if (node->depth == 0) {

                        switch (map.soils[node->localisation.pos.y][node->localisation.pos.x]) {

                            case ERG : if (number_move == F_20 || number_move == F_30 || number_move == U_TURN) {
                                number_move = number_move - 1;
                            }
                            else {
                                number_move = ROOT;
                            }
                            break;

                            default: break;
                        }

                    }

                    // Si la nouvelle localisation appartient à la map
                    if (isValidLocalisation(move(node->localisation, number_move).pos, map.x_max, map.y_max)) {

                        // Le nouveau noeud prend la localisation après mouvement
                        new_node->localisation = move(node->localisation, number_move);
                        new_node->case_cost = map.costs[new_node->localisation.pos.y][new_node->localisation.pos.x];

                        // Si le noeud correspond à la case de la base alors ce noeud devient une feuille
                        if(new_node->case_cost == 0) {
                            new_node->nbSons = 0;
                        }

                    }

                    // Sinon le noeud devient une feuille avec une case de valeur 13000 (coût d'une case interdite)
                    else {
                        new_node->nbSons = 0;
                        new_node->case_cost = 13000;
                    }

                    return;
                }
                j++;
            }
        }
    }
}

// Fonction d'affchage pour un noeud et ses enfants (incluant plus de détails)
void printNodeSonV2(t_node node) {

    // Affiche le noeud indenté en fonction de son nombre de fils
    printNodeV2(node, ((node.nbSons * 5 + 7 * (node.nbSons - 1)) / 2) - 1);


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

    // Afficher le mouvement de chaque noeud fils avec indentation
    for (int i = 0; i < node.nbSons; i++) {
        if (node.sons[i] != NULL) {
            printf("  [*%d]", node.sons[i]->case_cost);
        } else {
            printf(" NULL");
        }
        printf("       ");
    }
    printf("\n");

}

// Ajoute une racine à un arbre
void addRoot(p_tree tree, t_move move, int nbSon, h_std_list* avails, t_localisation localisation, t_map map) {

    // Si l'arbre n'a pas encore de racine
    if (tree->root == NULL) {

        // Créer un nouveau noeud
        tree->root = createNode(move, nbSon, 0);
        tree->root->path = (p_move) malloc(sizeof(t_move));

        // Affecter son chemin (pour la racine ce chemin est toujours 0)
        tree->root->path[0] = tree->root->move;

        // Affecter le tableau des mouvements restants
        tree->root->avails = avails;

        // Affecter la localisation
        tree->root->localisation = localisation;

        // Affecter le coût de la case qu'il représente
        tree->root->case_cost = map.costs[tree->root->localisation.pos.y][tree->root->localisation.pos.x];

        // Affecter la profonceur (profondeur de la racie est de 0)
        tree->depth = 0;
    }

    // Si l'arbre a déjà une racine
    else {
        printf("Arbre contenant un root");
    }
}

// Recherche le chemin avec le moins de point et renvoie le dernier noeud de celui-ci
p_node searchBetterPathNode(t_tree tree) {

    // Récupérer l'adresse de la racine
    p_node node = tree.root;

    // Parcourir jusqu'à atteindre une feuille
    while (node != searchBetterNode(node)) {

        // Aller au nœud avec le coût minimal
        node = searchBetterNode(node);
    }

    return node;
}

p_node searchBetterNode(p_node node) {

    // Si c'est une feuille, la retourner
    if (node->nbSons == 0) {

        return node;

    }

    // Initialiser le coût minimal à une valeur très élevée
    int cost_min = INT_MAX;

    // Initialiser le noeud minimal à NULL
    p_node node_min = NULL;

    for (int i = 0; i < node->nbSons; i++) {

        // Récupérer l'adresse d'un noeud fils
        p_node child = node->sons[i];

        if (child != NULL) {

            if (child->case_cost < cost_min) {

                // Mettre à jour le coût minimal
                cost_min = child->case_cost;

                // Mettre à jour le noeud avec le coût minimal
                node_min = child;
            }
        }
    }

    // Si aucun noeud enfant n'est trouvé renvoyer le noeud actuel
    return (node_min != NULL) ? node_min : node;

}

p_tree createTreeV2(h_std_list* phase_move, t_map map, t_localisation loc, int max_depth) {

    // Création de l'arbre vide
    p_tree tree = (p_tree) malloc(sizeof(t_tree));
    if (tree == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire pour l'arbre\n");
        exit(EXIT_FAILURE);
    }
    *tree = createEmptyTree();

    // Définition du nombre de noeuds fils de la racine (profondeur de l'arbre)
    int nbMove = 1;

    // Ajout de la racine
    addRoot(tree, ROOT, nbMove, phase_move, loc, map);

    // Appel de la fonction récursive pour la création de tous les noeuds
    addNodeRecV2(tree, tree->root, map, max_depth);

    return tree;
}



void addNodeRecV2(p_tree tree, p_node node, t_map map, int max_depth) {
    // Si le noeud n'admet plus de noeud fils
    if (node->nbSons < 1) {
        return;
    }

    // Sinon
    if (node->depth < max_depth) {

        // Stocker le mouvement correspondant au minimum de point
        t_move min_move = ROOT;

        // Stocker le coût de la case la plus petite
        int min_case_cost = 65000;

        // Ajout des noeuds fils en fonction du mouvement le plus intéressant
        for (int i = 0; i < countEltHList(*node->avails); i++) {

            t_move current_move = findElt(*node->avails, i);

            t_localisation new_loc;

            if (node->depth == 0) {

                switch (map.soils[node->localisation.pos.y][node->localisation.pos.x]) {

                    case ERG : if (current_move == F_20 || current_move == F_30 || current_move == U_TURN) {
                        new_loc = move(node->localisation, current_move - 1);;
                    }
                    else {
                        new_loc = node->localisation;
                    }
                        break;

                    default: new_loc = move(node->localisation, current_move);
                        break;
                }

            }

            if (isValidLocalisation(new_loc.pos, map.x_max, map.y_max) && map.costs[new_loc.pos.y][new_loc.pos.x] < min_case_cost) {
                min_case_cost = map.costs[new_loc.pos.y][new_loc.pos.x];
                min_move = current_move;
            }
        }

        if (min_move == ROOT || min_case_cost < 12999) {

            // Ajout du noeud le plus intéressant
            addNodeV2(tree, node, min_move, map, max_depth);

            // Appel récursif de la fonction pour construire l'arbre entier
            for (int i = 0; i < node->nbSons; i++) {
                if (node->sons[i] != NULL) {
                    addNodeRecV2(tree, node->sons[i], map, max_depth);
                }
            }
        } else {
            node->nbSons = 0;

            // Ajout du noeud le plus intéressant
            addNodeV2(tree, node, min_move, map, max_depth);
        }
    }
}


void addNodeV2(p_tree tree, p_node node, t_move number_move, t_map map, int max_depth) {
    // Pour le cas où l'arbre est vide
    if (tree->root == NULL) {
        printf("Arbre ne contient pas de root\n");
        return;
    }

    // Création du nouveau noeud (enfant/fils)
    p_node new_node = createNode(number_move, node->nbSons, node->depth + 1);
    if (new_node == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire pour le noeud\n");
        exit(EXIT_FAILURE);
    }

    // Ajout du nouveau noeud fils dans un "emplacement" libre
    for (int i = 0; i < node->nbSons; i++) {
        if (node->sons[i] == NULL) {
            node->sons[i] = new_node;

            // Mise à jour du chemin pour accéder au noeud à partir de la racine de l'arbre
            for (int k = 0; k < node->depth + 1; k++) {
                new_node->path[k] = node->path[k];
            }

            // Affectation des movements encore disponible (supprime le mouvement qu'on vient d'ajouter)
            new_node->avails = removeElt(*node->avails, number_move);

            // Affectation du nouveau mouvement dans le chemin (chemin du parent + number_move du noeud actuel)
            new_node->path[node->depth + 1] = new_node->move;

            // Changement de la profondeur total de l'arbre dans le cas où le nouveau noeud est le plus profond
            if (tree->depth < new_node->depth) {
                tree->depth = new_node->depth;
            }

            if (node->depth == 0) {

                switch (map.soils[node->localisation.pos.y][node->localisation.pos.x]) {

                    case ERG : if (number_move == F_20 || number_move == F_30 || number_move == U_TURN) {
                        number_move = number_move - 1;
                    }
                    else {
                        number_move = ROOT;
                    }
                    break;

                    default: break;
                }

            }
            // Si la nouvelle localisation appartient à la map
            t_localisation new_loc = move(node->localisation, number_move);
            if (isValidLocalisation(new_loc.pos, map.x_max, map.y_max)) {
                // Le nouveau noeud prend la localisation après mouvement
                new_node->localisation = new_loc;
                new_node->case_cost = map.costs[new_node->localisation.pos.y][new_node->localisation.pos.x];

                // Si le noeud correspond à la case de la base alors ce noeud devient une feuille
                if (new_node->case_cost == 0) {
                    new_node->nbSons = 0;
                }
            } else {
                // Sinon le noeud devient une feuille avec une case de valeur 13000 (coût d'une case interdite)
                new_node->nbSons = 0;
                new_node->case_cost = 13000;
            }

            return;
        }
    }
}

// Retourne et affiche le dernier noeud de l'arbre Methode 2
p_node printLastNodeTreeV2(t_tree tree) {

    p_node node = tree.root;
    while (node->nbSons == 1 && node->sons[0] != NULL) {
        node = node->sons[0];
    }

    return node;
}
