//
// Created by flasque on 19/10/2024.
//

#ifndef UNTITLED1_MAP_H
#define UNTITLED1_MAP_H

#include "loc.h"


/**
 * @brief Array of strings for the possible moves of the robot
 */
static char _soil[8][13] = {"BASE_STATION", "PLAIN", "ERG", "REG", "CREVASSE", "PENTE", "ZONE_MORTE", "ZONE_SOLAIRE"};

/**
 *
 */
#define COST_UNDEF 65535
/**
 * @brief Enum for the possible soils of the map
 */
typedef enum e_soil
{
    BASE_STATION,
    PLAIN,
    ERG,
    REG,
    CREVASSE,
    PENTE,
    ZONE_MORTE,
    ZONE_SOLAIRE
} t_soil;

typedef struct {
 int element;
 double percentage;  // Le pourcentage de probabilité de l'élément
} tabSoils;

/**
 * @brief Array of costs for the soils
 */
static const int _soil_cost[8] = {0, 2, 4, 5, 10000, 10, 6, 1};

/**
 * @brief Structure for the map

 */
typedef struct s_map
{
    t_soil  **soils;
    int     **costs;
    int     x_max;
    int     y_max;
} t_map;

/**
 * @brief Function to initialise the map from a file
 * @param filename : the name of the file
 * @return the map
 */
t_map createMapFromFile(char *);

/**
 * @brief Function to create a standard training map (11x11 with only plains and base station in the middle)
 * @param none
 * @return a standard map
 */
 t_map createTrainingMap();

/**
 * @brief display the map with characters
 * @param map : the map to display
 */
void displayMap(t_map);

/**
 * @brief :  function to get the position of the base station
 * @param map : the map
 * @return : the position of the base station
 */
t_position getBaseStationPosition(t_map);

/**
 * @brief : function to calculate costs of the map  from the base station
 * @param map : the map
 * @return none
 */
void calculateCosts(t_map);

/**
 * @brief : function to remove 'false' crevasses costs from the costs array
 * @param map : the map
 * @return none
 */
void removeFalseCrevasses(t_map);

void createRandomMap(char *filename, int ydim, int xdim);

enum e_soil selectRandomSoils(tabSoils soils[], int size);

int randomNumber(int min, int max);

char *getSoilAsString(t_soil soil);

t_position getNewPositionOnPente( t_localisation loc, t_map map);

#endif //UNTITLED1_MAP_H
