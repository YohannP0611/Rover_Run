#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "tree.h"

t_tree createEmptyTree() {
    t_tree tree;
    tree.root = NULL;
    return tree;
}