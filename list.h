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

void addTailList(h_std_list* list, int val);

#endif //UNTITLED1_LIST_H
