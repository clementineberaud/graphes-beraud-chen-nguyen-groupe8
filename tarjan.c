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
    return tab;
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



void parcours(int v, t_list_adj* G, t_tab_tarjan tab, t_stacklist* P, int* num, int** partition, int* nbCFC){
    tab[v].numero = *num;
    tab[v].num_accessible = *num;
    (*num)++;

    push(P, v);
    tab[v].indicateur = true;
    
    t_cell* cur = G->T[v].head;

    while (cur != NULL) {
        int w = cur->sommet;

        if (tab[w].numero == -1) {
            parcours(w, G, tab, P, num, partition, nbCFC);
            if (tab[w].num_accessible < tab[v].num_accessible)
                tab[v].num_accessible = tab[w].num_accessible;
        }
        else if (tab[w].indicateur) {
            if (tab[w].numero < tab[v].num_accessible)
                tab[v].num_accessible = tab[w].numero;
        }

        cur = cur->next;
    }
    
    if (tab[v].num_accessible == tab[v].numero) {

        int* cfc = malloc(G->taille * sizeof(int));
        int cpt = 0;
        int w;

        do {
            w = pop(P);
            tab[w].indicateur = false;
            cfc[cpt++] = w;
        } while (w != v);

        partition[*nbCFC] = cfc;
        (*nbCFC)++;
    }
}
