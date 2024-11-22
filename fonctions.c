//
// Created by mendo on 20/11/2024.
//

#include "fonctions.h"

#include "node.h"
#include "tree.h"


//////////////////////////
// Fonctions d'affichage//
//////////////////////////

// Affichage de la progression d'une tâche
void afficherProgression(int pourcentage);

// Affiche les instructions du jeu
void instructions();

// Affiche le message de demmarage du jeu
void afficherDemarrage() {
    printf("*************************************\n");
    printf("*        DEMARRAGE DU JEU...        *\n");
    printf("*************************************\n");
    for (int i = 0; i < 3; i++) {
        printf(".");
        fflush(stdout);
        _sleep(1);
    }
    printf("\n\n");
}

// Affiche la localisation du robot et les coordonées de la phase
void afficherInfosRobot(t_localisation robot_loc, t_position base_station_loc) {
    printf("*************************************\n");
    printf("*       Informations du robot       *\n");
    printf("*************************************\n");
    printf("* Orientation actuelle : %s\t    *\n", getOrientationAsString(robot_loc.ori));
    printf("* Position actuelle :               *\n");
    printf("*\tx : %d    \t\t    *\n", robot_loc.pos.x);
    printf("*\ty : %d    \t\t    *\n", robot_loc.pos.y);
    printf("*                                   *\n");
    printf("* Position de la base :             *\n");
    printf("*\tx : %d    \t\t    *\n", base_station_loc.x);
    printf("*\ty : %d    \t\t    *\n", base_station_loc.y);
    printf("*************************************\n\n");
}

// Affiche la liste des mouvements disponibles dans la phase
void afficherMouvements(h_std_list move_list, int nbMoveSelect) {
    printf("=====================================\n");
    printf("|    Mouvements disponibles (%d)     |\n", nbMoveSelect);
    printf("=====================================\n");
    printf("| %-10s | %-10s\n", "Numero", "Mouvement\t    |");
    printf("-------------------------------------\n");

    p_cell tmp = move_list.head;
        while (tmp != NULL) {
            printf("| %-10.1d | %-10s\t    |\n", tmp->move, getMoveAsString(tmp->move));
            tmp = tmp->next;
        }

    printf("-------------------------------------\n\n");
}

// Affiche le message de début de phase
void afficherDebutPhase(int phase) {
    printf("=========================================\n");
    printf("          Debut de la phase %d\n", phase);
    printf("=========================================\n\n");
}

// Affiche la carte avec les coûts de chaque cases
void afficherCarteAvecCouts(t_map map) {

    printf("*************************************\n");
    printf("*          Couts de la carte        *\n");
    printf("*************************************\n\n");

    for (int i = 0; i < map.y_max; i++) {
        for (int j = 0; j < map.x_max; j++) {
            printf("%-5d ", map.costs[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");
    printf("-------------------------------------\n\n\n");
}

// Affiche le résultat de fin de phase
void AfficherResultats(int success) {
        printf("===============================================\n");
    if (success) {
        printf("              MISSION REUSSIE !\n");
    } else {
        printf("MISSION ECHOUEE : le robot est perdu ou detruit\n");
    }
        printf("===============================================\n\n");
    _sleep(6000);
    for (int i = 0; i < 15; i++) {
        printf("\n\n\n");
    }
}

void afficherProgression(int pourcentage) {
    printf("[");
    int completed = pourcentage / 10; // Une case pour chaque 10%
    for (int i = 0; i < 10; i++) {
        if (i < completed) {
            printf("#"); // Rempli
        } else {
            printf(" "); // Vide
        }
    }
    printf("] %d%%\n", pourcentage);
}

// Affiche le menu du jeu
void afficherMenu(t_map* map, int* nbMaxMove, int* nbMoveSelect, int* methode) {
    int choix = 0;
    do {
        printf("\n\n\n");
        printf("\n\n\n");
        printf("*********************************\n");
        printf("*        Rover Run - Menu       *\n");
        printf("*********************************\n");
        printf("* 1. Jouer                      *\n");
        printf("* 2. Instructions               *\n");
        printf("* 3. Options                    *\n");
        printf("* 4. Quitter                    *\n");
        printf("*********************************\n");
        printf("\n\n\n");
        printf("Entrez votre choix : ");
        scanf("%d", &choix);
        for (int i = 0; i < 15; i++) {
            printf("\n\n\n");
        }

        switch (choix) {
            case 1: jouer(*map, *nbMaxMove, *nbMoveSelect, *methode); break;
            case 2: instructions(); break;
            case 3: options(nbMaxMove, nbMoveSelect, map, methode); break;
            case 4: quitter(); break;
            default:
                printf("Choix invalide. Veuillez réessayer.\n");
            getchar(); // Pause pour afficher le message
            break;
        }
    } while (choix != 4);
}

// Affiche les instructions du jeu
void instructions() {
    printf("=======================\n");
    printf("| Instructions du jeu |\n");
    printf("=======================\n\n");
    printf("Contexte de la mission :\n\n2028 : Une tempete solaire tres intense vient de se produire... "
           "Le rover MARC - MArs Rover Cartograph, qui s'acquittait fort bien de sa mission, a ete victime d’un "
           "dysfonctionnement. Ses systemes de programmation, de guidage et de mouvements ont ete fortement alteres... "
           "L'ESTF, Efrei Space Task Force, a fait appel a des experts en programmation pour concevoir un nouveau logiciel "
           "de deplacement pour MARC. Votre mission est de realiser ce logiciel de deplacement pour ramener MARC jusqu'a une "
           "station de base ou il pourra etre remis en etat.\n\nLe rover MARC\n\nMARC est un rover un peu rustique, il embarque un "
           "systeme Linux, et tous ses programmes sont ecrits en langage C. Il se repere par sa position, et la direction a laquelle il "
           "fait face, parmi Nord, Sud, Est et Ouest (meme sur Mars). Fort heureusement, son radar et son gyroscope fonctionnent encore et "
           "lui permettent de se situer.\n\nSysteme de deplacement\n\nMARC peut effectuer les mouvements suivants (ce sont des mouvements "
           "unitaires) :\n\n-	avancer de 10m\n-	avancer de 20m\n-	avancer de 30m\n-	reculer de 10m (en marche arriere)\n"
           "-	tourner d'un quart de tour a gauche\n-	tourner d'un quart de tour a droite\n-	faire demi-tour.\n\nLes avaries "
           "de ses systemes font que son deplacement se deroule maintenant par phases, et il ne peut donc pas directement aller"
           " d'un point A a un point B.\nPour chaque phase, MARC disposera de mouvements possibles, et devra en choisir un nombre precis pour realiser cette phase. Il va donc falloir programmer "
           "le \"meilleur choix possible\" de deplacement.\n\n\n");
    printf("[Appuyez sur ENTREE pour continuer]");
    getchar();
    getchar();
}





/////////////////////
// Autres fonctions//
/////////////////////

// Fonction qui concatène le nom du fichier avec le chemin
char* concatPath(const char* path, const char* filename) {
    static char fullPath[200];
    snprintf(fullPath, sizeof(fullPath), "%s%s", path, filename);
    return fullPath;
}

// Fonction pour modifier la carte
void modifierCarte(t_map* map) {
    int choix = 0;
    char nomCarte[100];

    printf("======================================\n");
    printf("|     Modification de la carte       |\n");
    printf("======================================\n");
    printf("| 1 - Charger une carte existante    |\n");
    printf("| 2 - Creer une nouvelle carte       |\n");
    printf("--------------------------------------\n");

    printf("Entrez votre choix : ");
    scanf("%d", &choix);
    getchar();

    switch (choix) {
        case 1: // Charger une carte existante
            printf("Entrez le nom de la carte a charger (sans chemin, exemple : example2.map) : ");
            fgets(nomCarte, sizeof(nomCarte), stdin);
            nomCarte[strcspn(nomCarte, "\n")] = '\0'; // Enlever le retour à la ligne.
            printf("\n");

            // Chargement de la carte à partir d'un nom de ficher
            *map = createMapFromFile(concatPath("..\\maps\\", nomCarte));
            printf(" Chargement carte : %s\n\n", nomCarte);
            break;

        case 2: // Créer une nouvelle carte
            printf("Entrez le nom de la nouvelle carte (sans chemin, exemple : nouvelle.map) : ");
            fgets(nomCarte, sizeof(nomCarte), stdin);
            nomCarte[strcspn(nomCarte, "\n")] = '\0';
            printf("\n");
            createRandomMap(concatPath("..\\maps\\", nomCarte), randomNumber(7, 16), randomNumber(6, 15));
            *map = createMapFromFile(concatPath("..\\maps\\", nomCarte));
            printf("Nouvelle carte creee et chargee : %s\n\n", nomCarte);
            break;

        default:
            printf("Choix invalide. Veuillez réessayer\n");
            break;
    }
}

// Fonction pour modifier les nombres de mouvement tirés et choisis
void demanderNombreMouvements(int* nbMaxMove, int* nbMoveSelect) {
    printf("\t*******************************************\n");
    printf("\t*         Configuration des phases        *\n");
    printf("\t*******************************************\n\n\n");

    printf("Nombre de mouvements maximum : ");
    scanf(" %d", nbMaxMove);
    printf("\n");
    printf("Nombre de mouvements disponibles : ");
    scanf(" %d", nbMoveSelect);

    printf("\nConfiguration enregistree !\n\n");
}

// Fonction de lancement du jeu
void jouer(t_map map, int nbMaxMove, int nbMoveSelect, int methode) {

    // Numéro de la phase
    int numero_phase = 1;

    int running = 0;

    // Exemple de tableau d'éléments avec leurs pourcentages initiaux
    tabMove items[] = {
            {F_10, 20.0},
            {F_20, 15.0},
            {F_30, 20.0},
            {B_10, 15.0},
            {T_RIGHT, 10.0},
            {T_LEFT, 10.0},
            {U_TURN, 10.0}
    };

    // Nombre de mouvements au total
    int nbMove = 7;


    // Fonction d'affichage au démarrage du jeu
    afficherDemarrage();


    // Affiche la carte avec les coûts de cases
    afficherCarteAvecCouts(map);

    printf("\n\n\n");

    // Définition des données initiales
    int x_init = randomNumber(0, map.x_max-1);
    int y_init = randomNumber(0, map.y_max-1);
    t_orientation  orientation_init = randomNumber(0, 3);

    // Définition des coordonnées de base du robot
    t_localisation robot_loc = loc_init(x_init, y_init, orientation_init);

    // Position de la base
    t_position base_station_loc = getBaseStationPosition(map);

    printf("\n\n\n");

    // Initialiser la location du robot pour le chemin automatique
    t_localisation root_loc_auto = loc_init(x_init, y_init, orientation_init);

    // Initialiser la location du robot pour le chemin manuel
    t_localisation root_loc = loc_init(x_init, y_init, orientation_init);

    while (running == 0) {

        int robot_signal = 1;

        while ((robot_loc.pos.x != base_station_loc.x || robot_loc.pos.y != base_station_loc.y) && robot_signal == 1) {

            // Afficher le message de début de phase
            afficherDebutPhase(numero_phase);

            _sleep(1000);

            // Afficher les informations du robot
            afficherInfosRobot(robot_loc, base_station_loc);

            _sleep(1000);


            h_std_list *move_list = createListEmpty();

            // Sélectionner n éléments
            for (int i = 0; i < nbMaxMove; i++) {

                // Choisir un mouvement aléatoire
                t_move selected = selectRandomMove(items, nbMove);

                // Ajouter l'éléments dans la liste
                addTailList(move_list, selected);
            }

            //for(int i = 0; i< 11; i++) {
            //afficherProgression(i*10);
            //_sleep(500);
            //}

            // Affiche les mouvements disponibles
            afficherMouvements(*move_list, nbMoveSelect);

            char guidage = ' ';

            printf("\n\n\n\nActiver le systeme de guidage automatique ? [Y/n] : ");
            scanf(" %c", &guidage);
            printf("\n");

            // Saisie sécurisée
            while (guidage != 'Y' && guidage != 'n') {
                printf("\nReponse invalide... Activer le systeme de guidage automatique ? [Y/n] : ");
                scanf(" %c", &guidage);
                printf("\n");
            }

            if (guidage == 'Y') {

                p_tree ptr_phase_tree_auto;
                
                p_node node;

                if (methode == 1) {
                    // Création de l'arbre de phase (Méthode 1)
                    ptr_phase_tree_auto = createTree(move_list, map, robot_loc, nbMoveSelect);

                    // Détermination du noeud avec le chemin le moins coûteux
                    node = searchBetterPathNode(*ptr_phase_tree_auto);
                }
                if (methode == 2) {

                    // Création de l'arbre de phase (Méthode 1)
                    ptr_phase_tree_auto = createTreeV2(move_list, map, robot_loc, nbMoveSelect);
                    printf("ojesoifsges");

                    // Détermination du noeud avec le chemin le moins coûteux
                    node = printLastNodeTreeV2(*ptr_phase_tree_auto);
                }


                if (node->case_cost > 12999) {
                    robot_signal = 0;
                } else {
                    printf("Le chemin le moins couteux est : ");

                    // Affichage du chemin
                    printPath(*node);

                    printf("\n\n");

                    // Affichage de la suite de mouvement correspondante
                    printf("Soit la suite de mouvement : [");
                    for (int i = 0; i < node->depth; i++) {
                        printf("%s - ", getMoveAsString(node->path[i]));
                    }
                    printf("%s]\n\n\n", getMoveAsString(node->path[node->depth]));

                    // Affectation des nouvelles coordonnées pour le robot (coordonnées de la case de fin de phase)
                    robot_loc = loc_init(node->localisation.pos.x, node->localisation.pos.y, node->localisation.ori);
                }

                // Augmenter le numéro de phase
                numero_phase++;

                if (robot_loc.pos.x != base_station_loc.x || robot_loc.pos.y != base_station_loc.y) {
                    printf("----------------------------------------------------------------\n\n\n");
                    _sleep(1000);
                }

            } else {

                // Création de l'arbre de phase manuel
                t_tree phase_tree_manuel = createEmptyTree();

                // Ajour de la racine de l'arbre
                addRoot(&phase_tree_manuel, ROOT, 1, move_list, robot_loc, map);

                // Afficher le message de début de phase
                afficherDebutPhase(numero_phase);

                // Temps d'arrêt du programme de 1s
                _sleep(1000);

                // Déclaration du noeud pour parcourir l'arbre
                p_node node = phase_tree_manuel.root;

                int rep = 0;

                // Tant que le nombre de mouvements à sélectionner n'est pas atteint, que le robot n'est pas hors signal (détruit ou sorti de la carte) et que le robot n'est pas arrivé aux coordonnées de la base
                while (rep < nbMoveSelect && robot_signal == 1 && (robot_loc.pos.x != base_station_loc.x || robot_loc.pos.y != base_station_loc.y)) {

                    // Afficher les informations du robot
                    afficherInfosRobot(robot_loc, base_station_loc);

                    _sleep(1000);

                    // Afficher les mouvements disponibles
                    afficherMouvements(*move_list, nbMoveSelect - rep);

                    printf("Choisir un mouvement [numero du mouvement dans la liste] :");

                    int movement;
                    scanf(" %d", &movement);
                    printf("\n");

                    // Vérification de la présence du mouvement dans la liste des mouvements tirés
                    while (!(isEltInList(*move_list, movement))) {
                        printf("Mouvement pas dans la liste... Choisir un autre mouvement :");
                        scanf(" %d", &movement);
                        printf("\n");
                    }

                    // Ajoute le noeud créé à l'arbre
                    addNodeV2(&phase_tree_manuel, node, movement, map, nbMoveSelect);

                    // Supprime le mouvement utilisé de la liste
                    move_list = removeElt(*move_list, movement);

                    // Passe au noeud suivant
                    node = node->sons[node->nbSons - 1];

                    if (node->case_cost > 10000) {

                        // Mettre le signal du robot à 0 pour indiquer une perte de signal de celui-ci
                        robot_signal = 0;

                    }
                    else {
                        printf("Chemin suivi : ");

                        // Affichage du chemin
                        printPath(*node);

                        // Affichage de la suite de mouvement correspondante
                        printf("\n\nSoit la suite de mouvement : [");
                        for (int i = 0; i < node->depth; i++) {
                            printf("%s - ", getMoveAsString(node->path[i]));
                        }
                        printf("%s]\n\n\n", getMoveAsString(node->path[node->depth]));

                        printf("\n\n");

                        // Affectation des nouvelles coordonnées pour le robot (coordonnées de la case de fin de phase)
                        robot_loc = loc_init(node->localisation.pos.x, node->localisation.pos.y, node->localisation.ori);
                    }

                    // Augmenter le nombre de mouvements éxecuté
                    rep++;

                }

                // Augmenter le numéro de phase
                numero_phase++;
            }

            if (robot_loc.pos.x != base_station_loc.x || robot_loc.pos.y != base_station_loc.y) {
                printf("----------------------------------------------------------------\n\n\n");
            }

        }

        AfficherResultats(robot_signal);

        displayMap(map);

        running = -1;

    }
}

// Permet de modifier les options du jeu
void options(int* nbMaxMove, int* nbMoveSelect, t_map* map, int* methode) {
    int choix = 0;

    printf("OPTIONS :\n");
    printf("1 - Modifier la carte.\n");
    printf("2 - Changer la selection des mouvements.\n");
    printf("3 - Changer la methode de construction de l'arbre (Actuellement : Methode %d).\n", *methode);
    printf("4 - Retablir les parametres par defaut.\n\n");
    printf("Entrez votre choix : ");
    scanf("%d", &choix);
    printf("\n");

    switch (choix) {
        case 1: modifierCarte(map);
            break;

        case 2: demanderNombreMouvements(nbMaxMove, nbMoveSelect);
            break;

        case 3: printf("3 - Changer la methode de construction de l'arbre (Actuellement : Methode %d).\n\n", *methode);
            printf("Entrez votre choix : ");
            scanf("%d", methode);
            printf("\n");
            break;

        case 4: *nbMaxMove = 9;
            *nbMoveSelect = 5;
            *map = createMapFromFile("..\\maps\\example1.map");
            *methode = 1;
            break;

        default:
            printf("Choix invalide. Veuillez réessayer.\n");
            break;
    }
    getchar(); // Pause
}

// Fonction pour sortir du programme
void quitter() {
    printf("MERCI D'AVOIR JOUE A ROVER RUN !\n");
    exit(0);
}
