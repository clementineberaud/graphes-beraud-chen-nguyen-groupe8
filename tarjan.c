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



void parcours(int sommet_curr, t_list_adj* graph_adj, t_tab_tarjan tab, t_stacklist* pile_sommet, int* cpt, int** partition, int* nbCFC){
    tab[sommet_curr].numero = *cpt;
    tab[sommet_curr].num_accessible = *cpt;
    (*cpt)++;

    push(pile_sommet, sommet_curr);
    tab[sommet_curr].indicateur = true;
    
    t_cell* cur = graph_adj->T[sommet_curr].head;

    while (cur != NULL) {
        int sommet_succ = cur->sommet;

        if (tab[sommet_succ].numero == -1) {
            parcours(sommet_succ, graph_adj, tab, pile_sommet, cpt, partition, nbCFC);
            if (tab[sommet_succ].num_accessible < tab[sommet_curr].num_accessible)
                tab[sommet_curr].num_accessible = tab[sommet_succ].num_accessible;
        }
        else if (tab[sommet_succ].indicateur) {
            if (tab[sommet_succ].numero < tab[sommet_curr].num_accessible)
                tab[sommet_curr].num_accessible = tab[sommet_succ].numero;
        }

        cur = cur->next;
    }
    
    if (tab[sommet_curr].num_accessible == tab[sommet_curr].numero) {

        int* tab_temp = malloc(graph_adj->taille * sizeof(int));
        int local_cpt = 0;
        int sommet_depile;

        do {
            sommet_depile = pop(pile_sommet);
            tab[sommet_depile].indicateur = false;
            tab_temp[local_cpt++] = sommet_depile;
        } while (sommet_depile != sommet_curr);

        partition[*nbCFC] = tab_temp;
        (*nbCFC)++;
    }
}
