#ifndef GRAPHES_H
#define GRAPHES_H

#include "list.h"
#include "tarjan.h"
#include "utils.h"

t_list_adj readGraph(const char *filename);
void grapheMarkov (t_list_adj* list);

void printGraph(const char *filename);
void printDiagrammeHasse(t_partition part,t_list_adj graph);
void carac_graphe_markov(t_list_adj graph);

#endif //GRAPHES_H
