#include <stdio.h>
#include <stdlib.h>
#include "tarjan.h"
#include "graphes.h"
#include "list.h"


t_tarjan_vertex *graph_to_tab(t_list_adj graph)
{
    t_tarjan_vertex *tab = (t_tarjan_vertex*) malloc(sizeof(t_tarjan_vertex) * graph.taille);
    for (int i = 0; i < graph.taille; i++) {

        tab[i].num_sommet = i + 1;

        tab[i].numero = -1;
        tab[i].num_accessible = -1;
        tab[i].indicateur = -1;
    }
    return tab;
}


t_stacklist create_stack() // créer pile

{
    t_stacklist stack;
    stack.head = NULL; // initialisation de la pile à NULL
    return stack;
}



int pop(t_stacklist* stack) {
    if (stack == NULL || stack->head == NULL) {
        printf("Pop from empty stack\n");
        exit(EXIT_FAILURE);
    }
    t_stackcell* tmp = stack->head;
    int val = tmp->sommet;
    stack->head = tmp->next;
    free(tmp);
    return val;
}

t_stackcell *create_cell(int val)
{
    t_stackcell *newCell = (t_stackcell*) malloc(sizeof(t_stackcell));
    newCell->sommet = val; // on donne la valeur val au nouveau sommet
    newCell->next = NULL;
    return newCell;
}

void push(t_stacklist *stack, int val) // ajout d'une valeur dans pile (au début de la liste)
{
    t_cell *cell = create_cell(val);
    cell->next = stack->head; // on fait pointer cell->next vers l'ancienne tête
    stack->head = cell; // on met à jour la tête de la pile

}

int top(t_stacklist* stack)
{
    if (stack->head == NULL) { // pile vide
        printf("Pop from empty stack\n");
        exit(EXIT_FAILURE);
    }
    return stack->head->sommet; // 	retourne la valeur du sommet (dernier élément ajouté)
}


void parcours(t_tarjan_vertex* tab, int v_index, t_list_adj graph, t_stacklist* P, int* num, t_partition* partition)
{
    t_tarjan_vertex* v = tab + v_index;


    v->numero = *num;
    v->num_accessible = *num;
    (*num)++;

    push(P, v->num_sommet);
    v->indicateur = 1;


    t_cell* curr = (*(graph.T + v_index)).head;
    while (curr != NULL) {
        int w_index = curr->sommet - 1;

        t_tarjan_vertex* w = tab + w_index;

        if (w->numero == -1) { //si w n'a pas encore été visité on appelle parcours

            parcours(tab, w_index, graph, P, num, partition);


            if (w->num_accessible < v->num_accessible)
                v->num_accessible = w->num_accessible;
        } else if (w->indicateur == 1) {

            if (w->numero < v->num_accessible)
                v->num_accessible = w->numero;
        }
        curr = curr->next;
    }


    if (v->num_accessible == v->numero) {
        int C_size = 0;
        int* C_sommets = NULL;
        int w_num;

        //on dépile tous les sommets de la composante
        do {
            w_num = pop(P);
            t_tarjan_vertex* w = tab + (w_num - 1);
            w->indicateur = -1;
            C_sommets = realloc(C_sommets, sizeof(int) * (C_size + 1));
            C_sommets[C_size] = w_num;
            C_size++;
        } while (w_num != v->num_sommet);

        // Ajoute la composante à la partition
        partition->list_sommet[partition->nb_composant] = C_sommets;
        partition->nb_sommet[partition->nb_composant] = C_size;
        partition->nb_composant++;
    }
}


t_partition tarjan(t_list_adj graph)
{
    int num = 0;
    t_stacklist P = create_stack();
    t_partition partition;

    partition.nb_composant = 0;
    partition.list_sommet = malloc(sizeof(int*) * graph.taille);
    partition.nb_sommet = malloc(sizeof(int) * graph.taille);

    t_tarjan_vertex* tab = graph_to_tab(graph); //on initialise les sommets


    for (int i = 0; i < graph.taille; i++) { //on parcourt  tous les sommets non visités
        if (tab[i].numero == -1) {
            parcours(tab, i, graph, &P, &num, &partition);
        }
    }

    free(tab);
    return partition;
}

void print_tarjan (t_partition part) { //affiche la partition


    for (int i=0;i<part.nb_composant;i++) {
        printf("Composante C%d : {",i+1); //affiche la classe

        //affiche chaque sommet de la classe
        for (int j=0;j<part.nb_sommet[i]-1;j++) {
            printf("%d, ",part.list_sommet[i][j]);
        }

        printf("%d}\n",part.list_sommet[i][part.nb_sommet[i]-1]);

    }
}

t_partition partition_test() { //fonction test si les fonction tarjan et parcours ne marchent pas
    t_partition part;

    part.nb_composant = 6;
    part.list_sommet = malloc(sizeof(int*) * part.nb_composant);
    part.nb_sommet   = malloc(sizeof(int) * part.nb_composant);

    //C1
    part.nb_sommet[0] = 3;
    part.list_sommet[0] = malloc(sizeof(int) * 3);
    part.list_sommet[0][0] = 1;
    part.list_sommet[0][1] = 7;
    part.list_sommet[0][2] = 5;

    //C2
    part.nb_sommet[1] = 1;
    part.list_sommet[1] = malloc(sizeof(int) * 1);
    part.list_sommet[1][0] = 2;

    //C3
    part.nb_sommet[2] = 3;
    part.list_sommet[2] = malloc(sizeof(int) * 3);
    part.list_sommet[2][0] = 3;
    part.list_sommet[2][1] = 8;
    part.list_sommet[2][2] = 6;

    //C4
    part.nb_sommet[3] = 1;
    part.list_sommet[3] = malloc(sizeof(int) * 1);
    part.list_sommet[3][0] = 4;

    //C5
    part.nb_sommet[4] = 1;
    part.list_sommet[4] = malloc(sizeof(int) * 1);
    part.list_sommet[4][0] = 9;

    //C6
    part.nb_sommet[5] = 1;
    part.list_sommet[5] = malloc(sizeof(int) * 1);
    part.list_sommet[5][0] = 10;
    return part;
}


