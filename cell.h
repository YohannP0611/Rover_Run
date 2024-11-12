#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "moves.h"

#ifndef UNTITLED1_CELL_H
#define UNTITLED1_CELL_H

// structure pour les cellules d'une liste
struct s_cell
{
    struct s_cell *prec;
    t_move move;
    struct s_cell *next;
};
typedef struct s_cell t_cell, *p_cell;

/***
 * @brief display a t_cell struct
 * @param t_cell : cell to display
 * @return : void
 */
void displayCell(t_cell);

/***
 * @brief create a cell, and return a pointer to
 * @param int value
 * @return pointer to cell, whit a value, and next is NULL
 */
p_cell createCell(t_move);

// Supprime une cellule
void deleteCell(p_cell);

#endif //UNTITLED1_CELL_H
