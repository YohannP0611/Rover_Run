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
    printf("%d\n", cell.move);
}

/***
 * @brief create a cell, and return a pointer to
 * @param int value
 * @return pointer to cell, whit a value, and next is NULL
 */
p_cell createCell(t_move move) {
    p_cell cell = (t_cell*) malloc(sizeof (p_cell));
    cell->move = move;
    cell->next = NULL;
    cell->prec = NULL;
    return cell;
}

void deleteCell(p_cell cell) {
    free(cell);
}