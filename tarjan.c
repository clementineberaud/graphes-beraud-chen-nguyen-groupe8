#include "tarjan.h"
#include "graphes.h"

t_tarjan_vertex graph_to_tab(t_list_adj graph)
{
    t_tarjan_vertex * tab = malloc(sizeof(t_tarjan_vertex)*graph.taille);
    for (int i = 0; i < graphe.taille; i++) {
        tab[i].num_sommet = i+1;
        tab[i].numero = -1;
        tab[i].num_accessible = -1;
        tab[i].indicateur = 0;
    }
}

t_stacklist create_stack() {
    t_stacklist stack;
    stack.head = NULL;
    return stack;
}

void push(t_stacklist* stack, int val) {
    t_cell *cell = create_cell(val);
    cell->next = stack->head;
    stack->head = cell;
}


int pop(t_stacklist* stack) {
    int val = top(stack);
    t_cell *cell = stack->head;
    stack->head = cell->next;
    free(cell);
    return val;
}
