#ifndef GRAPHES_H
#define GRAPHES_H

#include "list.h"

t_list_adj readGraph(const char *filename);
void grapheMarkov (t_list_adj* list);

t_list_adj printGraph(const char *filename);

#endif //GRAPHES_H
