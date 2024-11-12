#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "cell.h"

/***
 * @brief display a t_cell struct
 * @param t_cell : cell to display
 * @return : void
 */
void displayCell(t_cell cell) {
    printf("%d", cell.move);
}

/***
 * @brief create a cell, and return a pointer to
 * @param int value
 * @return pointer to cell, whit a value, and next is NULL
 */
p_cell createCell(t_move move) {
    p_cell cell = (p_cell) malloc(sizeof (t_cell));
    cell->move = move;
    cell->next = NULL;
    cell->prec = NULL;
    return cell;
}

// Supprime une cellule
void deleteCell(p_cell cell) {
    free(cell);
}