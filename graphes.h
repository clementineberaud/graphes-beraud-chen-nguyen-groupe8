#ifndef GRAPHES_H
#define GRAPHES_H

#include "list.h"
#include "utils.h"

t_list_adj readGraph(const char *filename);
void grapheMarkov (t_list_adj* list);

void printGraph(const char *filename);

#endif //GRAPHES_H
