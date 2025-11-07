#ifndef GRAPHES_H
#define GRAPHES_H

#include "list.h"

t_list_adj readGraph(const char *filename);
void grapheMarkov (t_list_adj* list);

#endif //GRAPHES_H
