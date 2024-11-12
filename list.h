//
// Created by ABuhl on 24/10/2024.
//

#ifndef UNTITLED1_LIST_H
#define UNTITLED1_LIST_H

#include "cell.h"


typedef struct s_std_list
{
    p_cell head;
} h_std_list;

void displayHList(h_std_list);

void addTailList(h_std_list* list, t_move move);

void Deleteelt(h_std_list*, t_move);

h_std_list* createListEmpty();

h_std_list* removeElt(h_std_list list, t_move move);

int countEltHList(h_std_list list);

t_move findElt(h_std_list list, int nb);

#endif //UNTITLED1_LIST_H
