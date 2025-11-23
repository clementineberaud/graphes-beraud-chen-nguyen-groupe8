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




/**
 * @brief Parcours récursif pour identifier les composantes fortement connexes (Tarjan).
 *
 * @param tab Tableau de t_tarjan_vertex
 * @param v_index Index du sommet courant
 * @param graph Graphe sous forme de liste d'adjacence
 * @param P Pile des sommets visités
 * @param num Compteur global pour numéroter les sommets
 * @param partition Partition dans laquelle stocker les composantes trouvées
 */
void parcours(t_tarjan_vertex* tab, int v_index, t_list_adj graph, t_stacklist* P, int* num, t_partition* partition);



/**
 * @brief Algorithme de Tarjan pour trouver les composantes fortement connexes d'un graphe.
 *
 * @param graph Graphe sous forme de liste d'adjacence
 * @return t_partition Partition des composantes fortement connexes
 */
t_partition tarjan(t_list_adj graph);



/**
 * @brief Affiche la partition des composantes fortement connexes.
 *
 * @param part Partition contenant les composantes
 */
void print_tarjan (t_partition part);



/**
 * @brief Génère une partition de test pour vérifier le fonctionnement des fonctions Tarjan.
 *
 * @return t_partition Partition prédéfinie
 */
t_partition partition_test();




/**
 * @brief Crée une cellule de pile contenant un sommet.
 *
 * @param val Numéro du sommet
 * @return t_stackcell* Nouvelle cellule
 */
t_stackcell *create_cell(int val);


/**
 * @brief Initialise un tableau de t_tarjan_vertex pour tous les sommets du graphe.
 *
 * @param graph Le graphe sous forme de liste d'adjacence
 * @return t_tarjan_vertex* Tableau de structures pour chaque sommet
 */
t_tarjan_vertex *graph_to_tab(t_list_adj graph);


/**
 * @brief Crée une pile vide.
 *
 * @return t_stacklist Pile initialisée
 */
t_stacklist create_stack();



/**
 * @brief Empile un sommet dans la pile.
 *
 * @param stack Pointeur vers la pile
 * @param val Numéro du sommet à empiler
 */
void push(t_stacklist* stack, int val);


/**
 * @brief Retourne le sommet au sommet de la pile sans le dépiler.
 *
 * @param stack Pointeur vers la pile
 * @return int Sommet au sommet de la pile
 */
int top(t_stacklist* stack);


/**
 * @brief Dépile et retourne le sommet au sommet de la pile.
 *
 * @param stack Pointeur vers la pile
 * @return int Sommet dépilé
 */
int pop(t_stacklist* stack);

#endif
