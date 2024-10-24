#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

void addTailList(h_std_list* list, t_move move) {
    p_cell new_cell = createCell(move);

    if(list->head == NULL) {
        list->head = new_cell;
        return;
    }
    else {
        p_cell tmp = list->head;
        while(tmp->next != NULL) {
            tmp = tmp->next;
        }
        tmp->next = new_cell;
        new_cell->prec = tmp;
        return;
    }
}

void displayHList(h_std_list list) {

    p_cell tmp = list.head;
    while(tmp != NULL) {
        displayCell(*tmp);
        tmp = tmp->next;
    }
    return;

}

void Deleteelt(h_std_list* list, t_move move) {
    if (list->head == NULL) {
        printf("Liste vide\n");
    }
    else {
        p_cell tmp = list->head;
        while(tmp != NULL || tmp->move != move) {
            tmp = tmp->next;
        }
        tmp->prec->next = tmp->next;
        deleteCell(tmp);
        free(tmp);
    }
}