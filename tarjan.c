#include <stdio.h>
#include <stdlib.h>
#include "tarjan.h"
#include "graphes.h"
#include "list.h"

t_tarjan_vertex *graph_to_tab(t_list_adj graph)
{
    t_tarjan_vertex *tab = (t_tarjan_vertex*) malloc(sizeof(t_tarjan_vertex) * graph.taille);
    for (int i = 0; i < graph.taille; i++) {
        tab[i].num_sommet = i+1;
        tab[i].numero = -1;
        tab[i].num_accessible = -1;
        tab[i].indicateur = 0;
    }
    return tab;
}

t_stacklist create_stack() // créer pile
{
    t_stacklist stack;
    stack.head = NULL; // initialisation de la pile à NULL
    return stack;
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

int pop(t_stacklist* stack)
{
    if (stack == NULL || stack->head == NULL) { // pile existe et pas vide
        printf("Pop from empty stack\n");
        exit(1);
    }
    t_stackcell* tmp = stack->head; // stocke le sommet actuel
    int val = tmp->sommet; // valeur du sommet actuel
    stack->head = tmp->next; // met à jour la tête de la pile
    free(tmp);
    return val;
}

void parcours(t_tarjan_vertex* tab, int v_index, t_list_adj graph, t_stacklist* P, int* num, t_partition* partition)
{
    t_tarjan_vertex* v = tab + v_index; // on récupère le sommet actuel v à partir de son indice v_index
    v->numero = *num; // on assigne le numéro d'exploration actuel à v
    v->num_accessible = *num;
    (*num)++; // on incrémente le compteur global de num pour le prochain sommet
    push(P, v->num_sommet); // on empile le sommet v dans la pile P
    v->indicateur = true; // le sommet est dans la pile

    // parcours de tous les successeurs w de v
    t_cell* curr = (*(graph.T + v_index)).head;
    while (curr != NULL) {
        // on récupère l'indice du successeur
        int w_index = curr->sommet - 1;
        t_tarjan_vertex* w = tab + w_index;

        if (w->numero == -1) { // si le successeur n'a pas encore été visité
            parcours(tab, w_index, graph, P, num, partition); // appel récursif pour explorer w
            if (w->num_accessible < v->num_accessible)
                v->num_accessible = w->num_accessible; // mise à jour du numéro accessible le plus bas depuis v
        }
        else if (w->indicateur) { // si le successeur a été visité (il est dans la pile)
            if (w->numero < v->num_accessible)
                v->num_accessible = w->numero; // mise à jour du plus petit numéro accessible de v
        }
        curr = curr->next; // passage au successeur suivant
    }

    if (v->num_accessible == v->numero) { // si v est racine d'une composante fortement connexe
        int C_size = 0; // taille de la composante actuelle
        int* C_sommets = NULL; // tableau pour stocker les sommets de la composante

        int w_num;
        do {
            w_num = pop(P);
            t_tarjan_vertex* w = tab + (w_num - 1);
            w->indicateur = false; // le sommet a été retiré de la pile
            C_sommets = realloc(C_sommets, sizeof(int) * (C_size + 1));
            *(C_sommets + C_size) = w_num;
            C_size++;
        } while (w_num != v->num_sommet); // tant que c'est pas v

        // ajout de la composante dans la partition
        partition->list_sommet = realloc(partition->list_sommet, sizeof(int*) * (partition->nb_composant + 1));
        *(partition->list_sommet + partition->nb_composant) = C_sommets;
        partition->nb_sommet = realloc(partition->nb_sommet, sizeof(int) * (partition->nb_composant + 1));
        *(partition->nb_sommet + partition->nb_composant) = C_size;
        partition->nb_composant++; // on augmente le nombre de composantes trouvées
    }
}

t_partition tarjan(t_list_adj graph) {
    int num = 0; // compteur global pour numéroter les sommets
    t_stacklist P = create_stack(); // pile vide pour les sommets
    t_partition partition;
    partition.nb_composant = 0;
    partition.list_sommet = malloc(sizeof(int*) * graph.taille); // allocation du tableau des composantes
    partition.nb_sommet = malloc(sizeof(int) * graph.taille);   // allocation des tailles des composantes
    t_tarjan_vertex* tab = graph_to_tab(graph); // initialisation des t_tarjan_vertex

    // Parcours de tous les sommets non visités
    for (int i = 0; i < graph.taille; i++) {
        if ((*(tab + i)).numero == -1) { // sommet pas encore visité
            parcours(tab, i, graph, &P, &num, &partition); // lancement du parcours récursif
        }
    }
    free(tab);
    return partition;
}