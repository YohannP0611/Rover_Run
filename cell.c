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
    printf("%d\n", cell.value);
}

/***
 * @brief create a cell, and return a pointer to
 * @param int value
 * @return pointer to cell, whit a value, and next is NULL
 */
p_cell createCell(int value) {
    p_cell cell = (t_cell*) malloc(sizeof (p_cell));
    cell->value = value;
    return cell;
}
