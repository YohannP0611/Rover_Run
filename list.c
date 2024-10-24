#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

void addTailList(h_std_list* list, int value) {
    p_cell new_cell = createCell(value);

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