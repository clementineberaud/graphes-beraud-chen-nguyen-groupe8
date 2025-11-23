#ifndef TARJAN_H
#define TARJAN_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "list.h"

typedef struct {
    int num_sommet;
    int numero;
    int num_accessible;
    int indicateur;
} t_tarjan_vertex;

typedef t_tarjan_vertex* t_tab_tarjan;

typedef struct s_stackcell {
    struct s_stackcell* next;
    int sommet;
} t_stackcell;

typedef struct s_stacklist {
    t_stackcell* head;
} t_stacklist;

t_stacklist create_stack();

typedef struct {
    char nom_classe;
    int nb_sommet;
} t_classe;

typedef t_classe* t_graphe;

typedef struct {
    int** list_sommet;
    int* nb_sommet;
    int nb_composant;
} t_partition;

t_tarjan_vertex *graph_to_tab(t_list_adj graph);
t_stacklist create_stack();
void push(t_stacklist* stack, int val);
int top(t_stacklist* stack);
int pop(t_stacklist* stack);

void parcours(t_tarjan_vertex* tab, int v_index, t_list_adj graph, t_stacklist* P, int* num, t_partition* partition);
t_partition tarjan(t_list_adj graph);
void print_tarjan (t_partition part);
t_partition partition_test();
#endif //TARJAN.H