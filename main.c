#include <stdio.h>
#include <time.h>
#include "fonctions.h"


int main() {

    // Initialisation de la méthode utilisée pour l'arbre (par défaut : Méthode 1)
    int methode = 1;

    // Initialisation de la fonction aléatoire
    srand(time(NULL));

    // Déclaration d'une variable t_map
    t_map map;

    // Fonction pour créer une carte aléatoirement (peut faire crash le programme de temps en temps)
    createRandomMap("..\\maps\\example2.map", randomNumber(7, 16), randomNumber(6, 15));

    // The following preprocessor directive checks if the code is being compiled on a Windows system.
    // If either _WIN32 or _WIN64 is defined, it means we are on a Windows platform.
    // On Windows, file paths use backslashes (\), hence we use the appropriate file path for Windows.


#if defined(_WIN32) || defined(_WIN64)
    map = createMapFromFile("..\\maps\\example1.map");
#else
    printf("ouhzer");
    map = createMapFromFile("../maps/example1.map");
    printf("zfgqsegspjges");
#endif

    printf("Map created with dimensions %d x %d\n", map.y_max, map.x_max);
    for (int i = 0; i < map.y_max; i++)
    {
        for (int j = 0; j < map.x_max; j++)
        {
            printf("%d ", map.soils[i][j]);
        }
        printf("\n");
    }
    // printf the costs, aligned left 5 digits
    for (int i = 0; i < map.y_max; i++)
    {
        for (int j = 0; j < map.x_max; j++)
        {
            printf("%-5d ", map.costs[i][j]);
        }
        printf("\n");
    }

    // Affiche la carte
    displayMap(map);

    printf("\n\n\n");

    // Nombre de mouvements tiré
    int nbMaxMove = 9;

    // Nombre de mouvements sélectionné
    int nbMoveSelect = 5;

    printf("\n\n\n");

    // Affiche le menu du jeu
    afficherMenu(&map, &nbMaxMove, &nbMoveSelect, &methode);

    return 0;
}
