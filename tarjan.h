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
    bool indicateur;
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


/**
 * @brief Initialise un tableau de sommets pour l’algorithme de Tarjan.
 *
 * Chaque sommet est initialisé avec un numéro non défini et un indicateur
 * à false (hors pile).
 *
 * @param graph Graphe sous forme de liste d’adjacence.
 * @return t_tarjan_vertex* Tableau de sommets initialisés pour Tarjan.
 */
t_tarjan_vertex *graph_to_tab(t_list_adj graph);


/**
 * @brief Crée et initialise une pile vide.
 *
 * La pile sera utilisée pour stocker les sommets pendant l’exploration
 * des composantes fortement connexes.
 *
 * @return t_stacklist Pile vide.
 */
t_stacklist create_stack();



/**
 * @brief Empile un sommet au sommet de la pile.
 *
 * @param stack Pointeur vers la pile.
 * @param val Numéro du sommet à empiler.
 */
void push(t_stacklist* stack, int val);


/**
 * @brief Retourne le sommet au sommet de la pile sans le retirer.
 *
 * @param stack Pointeur vers la pile.
 * @return int Numéro du sommet au sommet de la pile.
 */
int top(t_stacklist* stack);


/**
 * @brief Dépile un sommet de la pile et libère sa cellule.
 *
 * @param stack Pointeur vers la pile.
 * @return int Numéro du sommet dépilé.
 */
int pop(t_stacklist* stack);

#endif