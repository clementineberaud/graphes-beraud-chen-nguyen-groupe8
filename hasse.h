#ifndef __HASSE_H__
#define __HASSE_H__
#include "list.h"
#include "tarjan.h"

typedef struct s_link {
  int from;
  int to;
} t_link;

typedef struct {
  t_link *links;
  int log_size;
} t_link_array;



int link_in_list (int a, int b, t_link_array *list);
t_link * createLink (int a, int b);
void addLink (t_link_array * tab, int a, int b);
int* tab_classes (t_partition par, t_list_adj graph);
t_link_array * diagramme_hasse (t_list_adj graph, t_partition par);
void removeTransitiveLinks(t_link_array *p_link_array);

/**
 * @brief Creates a link array from the given partition and graph.
 *
 * @param part The partition of the graph.
 * @param graph The adjacency list representation of the graph.
 * @return The created link array.
 */

#endif