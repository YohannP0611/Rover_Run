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

h_std_list* removeElt(h_std_list* list, t_move move) {
    h_std_list* list2 = createListEmpty();
    if (list->head == NULL) {
        printf("Liste vide\n");
        return NULL;
    }
    else {
        p_cell tmp = list->head;
        while(tmp != NULL) {
            if (tmp->move != move) {
                addTailList(list2, tmp->move);
            }
            tmp = tmp->next;
        }
    }
    return list2;
}

h_std_list* createListEmpty(){
    h_std_list* list = (h_std_list*)malloc(sizeof (h_std_list));
    list->head = NULL;
    return list;
}