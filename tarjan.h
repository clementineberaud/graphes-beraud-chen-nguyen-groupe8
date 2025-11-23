#ifndef TARJAN_H
#define TARJAN_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "list.h"

typedef struct s_tarjan_vertex {
    int num_sommet;
    int numero;
    int num_accessible;
    bool indicateur;
}t_tarjan_vertex;

typedef t_tarjan_vertex* t_tab_tarjan;

typedef struct s_stackcell {
    struct s_stackcell* head;
    t_tarjan_vertex sommet;
} t_stackcell;

typedef struct s_stacklist {
    t_stackcell* head;
} t_stacklist;

t_stacklist create_stack();

typedef struct s_classe {
    char nom_classe;
    int nb_sommet;
}t_classe;

typedef t_classe* t_graphe;

typedef struct {
    int** list_sommet;
    int* nb_sommet;
    int nb_composant;
} t_partition;

void push(t_stacklist* stack, int val);

int pop(t_stacklist* stack);

void parcours(int v, t_list_adj* G, t_tab_tarjan tab, t_stacklist* P, int* num, int** partition, int* nbCFC);
t_partition tarjan(t_list_adj* graph);


#endif //TARJAN_H
