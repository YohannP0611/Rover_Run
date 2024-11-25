//
// Created by flasque on 19/10/2024.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "map.h"
#include "loc.h"
#include "queue.h"
#include <time.h>




/* definition of local functions */

t_position getBaseStationPosition(t_map map)
{
    t_position pos;
    int i = 0;
    int found = 0;
    while (i < map.y_max && !found)
    {
        int j = 0;
        while (j < map.x_max && !found)
        {
            if (map.soils[i][j] == BASE_STATION)
            {
                pos.x = j;
                pos.y = i;
                found = 1;
            }
            j++;
        }
        i++;
    }
    // if the base station is not found, we exit the program
    if (!found)
    {
        fprintf(stderr, "Error: base station not found in the map\n");
        exit(1);
    }
    return pos;
}

void removeFalseCrevasses(t_map map)
{
    // step 1 : find the minimal cost > 10000 in the costs array where the soil is not a crevasse
    int over=0;
    int imin, jmin;
    while (!over)
    {
        int min_cost = COST_UNDEF;
        imin = map.y_max;
        jmin = map.x_max;
        for (int i=0; i<map.y_max; i++)
        {
            for (int j=0; j<map.x_max; j++)
            {
                if (map.soils[i][j] != CREVASSE && map.costs[i][j] > 10000 && map.costs[i][j] < min_cost)
                {
                    min_cost = map.costs[i][j];
                    imin = i;
                    jmin = j;
                }
            }
        }
        if (imin < map.y_max && jmin < map.x_max)
        {
            // step 2 : calculate the costs of the neighbours of the position
            t_position pos;
            pos.x = jmin;
            pos.y = imin;
            t_position lp, rp, up, dp;
            lp = LEFT(pos);
            rp = RIGHT(pos);
            up = UP(pos);
            dp = DOWN(pos);
            int min_neighbour = COST_UNDEF;
            if (isValidLocalisation(lp, map.x_max, map.y_max))
            {
                min_neighbour = (map.costs[lp.y][lp.x] < min_neighbour) ? map.costs[lp.y][lp.x] : min_neighbour;
            }
            if (isValidLocalisation(rp, map.x_max, map.y_max))
            {
                min_neighbour = (map.costs[rp.y][rp.x] < min_neighbour) ? map.costs[rp.y][rp.x] : min_neighbour;
            }
            if (isValidLocalisation(up, map.x_max, map.y_max))
            {
                min_neighbour = (map.costs[up.y][up.x] < min_neighbour) ? map.costs[up.y][up.x] : min_neighbour;
            }
            if (isValidLocalisation(dp, map.x_max, map.y_max))
            {
                min_neighbour = (map.costs[dp.y][dp.x] < min_neighbour) ? map.costs[dp.y][dp.x] : min_neighbour;
            }
            int self_cost = _soil_cost[map.soils[imin][jmin]];
            map.costs[imin][jmin] = (min_neighbour + self_cost < map.costs[imin][jmin]) ? min_neighbour + self_cost : map.costs[imin][jmin];
        }
        else
        {
            over = 1;
        }
    }
}

void calculateCosts(t_map map)
{
    t_position baseStation = getBaseStationPosition(map);
    //create a queue to store the positions to visit
    t_queue queue = createQueue(map.x_max * map.y_max);
    //enqueue the base station
    enqueue(&queue, baseStation);
    // while the queue is not empty
    while (queue.first != queue.last)
    {
        // dequeue the position
        t_position pos = dequeue(&queue);
        // get its self cost
        int self_cost = _soil_cost[map.soils[pos.y][pos.x]];
        // get ts neighbours
        t_position lp, rp, up, dp;
        lp = LEFT(pos);
        rp = RIGHT(pos);
        up = UP(pos);
        dp = DOWN(pos);
        // get the mimimum cost of the neighbours
        int min_cost = COST_UNDEF;
        if (isValidLocalisation(lp, map.x_max, map.y_max))
        {
            min_cost = (map.costs[lp.y][lp.x] < min_cost) ? map.costs[lp.y][lp.x] : min_cost;
        }
        if (isValidLocalisation(rp, map.x_max, map.y_max))
        {
            min_cost = (map.costs[rp.y][rp.x] < min_cost) ? map.costs[rp.y][rp.x] : min_cost;
        }
        if (isValidLocalisation(up, map.x_max, map.y_max))
        {
            min_cost = (map.costs[up.y][up.x] < min_cost) ? map.costs[up.y][up.x] : min_cost;
        }
        if (isValidLocalisation(dp, map.x_max, map.y_max))
        {
            min_cost = (map.costs[dp.y][dp.x] < min_cost) ? map.costs[dp.y][dp.x] : min_cost;
        }
        // the cost of the current position is the minimum cost of the neighbours + 1 or 0 if the soil is a base station
        map.costs[pos.y][pos.x] = (map.soils[pos.y][pos.x] == BASE_STATION) ? 0 : min_cost + self_cost;
        // enqueue the neighbours if they are not visited yet
        if (isValidLocalisation(lp, map.x_max, map.y_max) && map.costs[lp.y][lp.x] == COST_UNDEF)
        {
            // mark as visited - change the cost to 65534
            map.costs[lp.y][lp.x] = COST_UNDEF-1;
            enqueue(&queue, lp);
        }
        if (isValidLocalisation(rp, map.x_max, map.y_max) && map.costs[rp.y][rp.x] == COST_UNDEF)
        {
            map.costs[rp.y][rp.x] = COST_UNDEF-1;
            enqueue(&queue, rp);
        }
        if (isValidLocalisation(up, map.x_max, map.y_max) && map.costs[up.y][up.x] == COST_UNDEF)
        {
            map.costs[up.y][up.x] = COST_UNDEF-1;
            enqueue(&queue, up);
        }
        if (isValidLocalisation(dp, map.x_max, map.y_max) && map.costs[dp.y][dp.x] == COST_UNDEF)
        {
            map.costs[dp.y][dp.x] = COST_UNDEF-1;
            enqueue(&queue, dp);
        }
    }


    return;
}
/* definition of exported functions */

t_map createMapFromFile(char *filename)
{
    /* rules for the file :
     * - the first line contains the number of lines : y dimension (int)
     * - the second line contains the number of columns : x dimension (int)
     * - the next lines contain the map values (int) separated by spaces : one line = one row
     * - the values are the following : 0 = BASE_STATION, 1 = PLAIN, 2 = ERG, 3 = REG, 4 = CREVASSE
     */

    t_map map;
    int xdim, ydim;     // dimensions of the map
    char buffer[100];   // buffer for reading the file line by line

    FILE *file = fopen(filename,"rt");
    if (file == NULL)
    {
        fprintf(stderr, "Error: cannot open file %s\n", filename);
        exit(1);
    }
    fscanf(file, "%d", &ydim);
    fscanf(file, "%d", &xdim);
    map.x_max = xdim;
    map.y_max = ydim;
    map.soils = (t_soil **)malloc(ydim * sizeof(t_soil *));
    for (int i = 0; i < ydim; i++)
    {
        map.soils[i] = (t_soil *)malloc(xdim * sizeof(t_soil));
    }
    map.costs = (int **)malloc(ydim * sizeof(int *));
    for (int i = 0; i < ydim; i++)
    {
        map.costs[i] = (int *)malloc(xdim * sizeof(int));
    }
    for (int i = 0; i < ydim; i++)
    {

        // parse the line to get the values : 0 = BASE_STATION, 1 = PLAIN, 2 = ERG, 3 = REG, 4 = CREVASSE
        // values are separated by spaces, so we use sscanf with %d to get the values
        for (int j = 0; j < xdim; j++)
        {
            int value;
            fscanf(file, "%d", &value);
            map.soils[i][j] = value;
            // cost is 0 for BASE_STATION, 65535 for other soils
            map.costs[i][j] = (value == BASE_STATION) ? 0 : COST_UNDEF;
        }

    }
    fclose(file);
    calculateCosts(map);
    removeFalseCrevasses(map);
    return map;
}

t_map createTrainingMap()
{
    return createMapFromFile("..\\maps\\training.map");
}

void displayMap(t_map map)
{
    /** the rules for display are :
     * display all soils with 3x3 characters
     * characters are : B for base station, '-' for plain, '~' for erg, '^' for reg, ' ' for crevasse
     */
    for (int i = 0; i < map.y_max; i++)
    {
        for (int rep = 0; rep < 2; rep++)
        {
            for (int j = 0; j < map.x_max; j++)
            {
                char c[4];
                switch (map.soils[i][j])
                {
                    case BASE_STATION:
                        if (rep==1)
                        {
                            strcpy(c, " B ");
                        }
                        else
                        {
                            strcpy(c, "   ");
                        }
                        break;
                    case PLAIN:
                        strcpy(c, "---");
                        break;
                    case ERG:
                        strcpy(c, "~~~");
                        break;
                    case REG:
                        strcpy(c, "^^^");
                        break;
                    case CREVASSE:
                        sprintf(c, "%c%c%c",219,219,219);
                        break;
                    case PENTE:
                        strcpy(c, "///");
                        break;
                    case ZONE_MORTE:
                        strcpy(c, "|||");
                        break;
                    case ZONE_SOLAIRE:
                        sprintf(c, "***",219,219,219);
                        break;
                    default:
                        strcpy(c, "???");
                        break;
                }
                printf("%s", c);
            }
            printf("\n");
        }

    }
    return;
}

void createRandomMap(char *filename, int ydim, int xdim) {

    // Exemple de tableau d'éléments avec leurs pourcentages initiaux
    tabSoils item_soils[] = {
        {PLAIN, 25.0},
        {ERG, 20.0},
        {REG, 20.0},
        {CREVASSE, 5.0},
        {BASE_STATION, 5.0},
        {PENTE, 10.0},
        {ZONE_MORTE, 10.0},
        {ZONE_SOLAIRE, 5.0}
    };

    srand(time(NULL));

    // Ouverture du fichier en écriture
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        fprintf(stderr, "Error: cannot create file %s\n", filename);
        exit(1);
    }

    // Écriture des dimensions de la carte
    fprintf(file, "%d\n", ydim);
    fprintf(file, "%d\n", xdim);

    // Génération aléatoire des cases de la carte
    for (int i = 0; i < ydim; i++) {
        for (int j = 0; j < xdim; j++) {
            int value;

            // Si la base n'est pas encore sorti à la fin de la génération de la carte
            if (item_soils[4].percentage != 0 && i == ydim - 1 && j == xdim - 1) {
                value = 0;
            }
            else {
                value = selectRandomSoils(item_soils, 8);
                if (value == 0) {
                    item_soils[4].percentage = 0.0;
                }
            }

            fprintf(file, "%d", value);
            if (j < xdim - 1) {
                fprintf(file, " "); // Ajouter un espace sauf à la fin de la ligne
            }
        }
        if (i < ydim - 1) {
            fprintf(file, "\n");
        }

    }

    // Fermeture du fichier
    fclose(file);
    printf("Map successfully created in file: %s\n", filename);

}

// Fonction pour sélectionner un élément en fonction des pourcentages
t_soil selectRandomSoils(tabSoils soils[], int size) {

    double sum = 0.0;

    // Calcul le pourcentage total des éléments
    for (int i = 0; i < size; i++) {
        sum += soils[i].percentage;
    }

    // Générer un nombre aléatoire entre 0 et la somme des pourcentages
    double random = (double)rand() / RAND_MAX * sum;

    // Sélection de l'élément
    double cumulative = 0.0;
    for (int i = 0; i < size; i++) {
        cumulative += soils[i].percentage;
        if (random <= cumulative) {
            return soils[i].element;
        }
    }

    return -1; // Retourne -1 si aucun élément n'est sélectionné (ne devrait pas arriver)
}

int randomNumber(int min, int max) {

    return min + rand() % (max - min + 1);

}

char *getSoilAsString(t_soil soil)
{
    return _soil[soil];
}

t_position getNewPositionOnPente(t_localisation loc, t_map map)
{
    t_position res;
    res.x = loc.pos.x;
    res.y = loc.pos.y;
    int dir = randomNumber(1,4);
    switch (dir) {

        case 1:
            res = RIGHT(res);
        break;
        case 2:
            res = UP(res);
        break;
        case 3:
            res = DOWN(res);
        break;
        case 4:
            res = LEFT(res);
        break;
        default:
            break;
    }
    return res;
}

