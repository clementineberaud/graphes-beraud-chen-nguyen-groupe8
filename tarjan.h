#ifndef TARJAN_H
#define TARJAN_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct s_tarjan_vertex {
    int num_sommet;
    int numero;
    int num_accessible;
    bool indicateur;
}t_tarjan_vertex;

typedef t_tarjan_vertex* t_tab_tarjan;

typedef struct s_stackcell {
    t_stackcell* head;
    t_tarjan_vertex sommet;
} t_stackcell;

typedef struct s_stacklist {
    t_stackcell* head;
} t_stacklist;

typedef t_tarjan_vertex* t_graphe;

t_stacklist create_stack();

typedef struct s_classe {
    char nom_classe;
    int nb_sommet;
}t_classe;

typedef t_classe* t_graphe;

void push(t_stacklist* stack, int val);

int pop(t_stacklist* stack);

typedef t_classe* t_partition;

#endif //TARJAN_H
