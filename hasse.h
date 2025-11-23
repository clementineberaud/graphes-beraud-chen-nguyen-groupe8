#ifndef __HASSE_H__
#define __HASSE_H__
#include "list.h"
#include "tarjan.h"

typedef struct s_link {
  int from;
  int to;
} t_link;

typedef struct {
  t_link *links;
  int log_size;
} t_link_array;


/**
 * @brief Vérifie si un lien entre deux sommets existe déjà dans le tableau de liens.
 *
 * @param a Sommet de départ
 * @param b Sommet d'arrivée
 * @param tab Pointeur vers le tableau de liens
 * @return int 1 si le lien existe, 0 sinon
 */
int link_in_list (int a, int b, t_link_array *list);


/**
 * @brief Crée dynamiquement une structure représentant un lien (a → b).
 *
 * Alloue un t_link, initialise les champs `from` et `to`,
 * puis retourne le pointeur vers cette structure.
 *
 * @param a Sommet source.
 * @param b Sommet destination.
 * @return t_link* Pointeur vers la structure nouvellement créée.
 */
t_link * createLink (int a, int b);




/**
 * @brief Crée un tableau associant à chaque sommet le numéro de sa classe.
 *
 * @param par Partition des composantes fortement connexes
 * @param graph Graphe sous forme de liste d'adjacence
 * @return int* Tableau où chaque case i contient la classe du sommet i+1
 */
int* tab_classes (t_partition par, t_list_adj graph);



/**
 * @brief Ajoute un lien entre deux sommets dans le tableau de liens.
 *
 * @param tab Pointeur vers le tableau de liens
 * @param a Sommet de départ
 * @param b Sommet d'arrivée
 */
void addLink (t_link_array * list, int a, int b);



/**
 * @brief Construit le diagramme de Hasse sous forme de tableau de liens pour les classes.
 *
 * @param graph Graphe sous forme de liste d'adjacence
 * @param par Partition des composantes fortement connexes
 * @return t_link_array* Tableau de liens représentant le diagramme de Hasse
 */
t_link_array * diagramme_hasse (t_list_adj graph, t_partition par);



/**
 * @brief Supprime les liens transitifs d'un tableau de liens pour ne garder que les liens directs.
 *
 * @param p_link_array Pointeur vers le tableau de liens
 */
void removeTransitiveLinks(t_link_array *p_link_array);




/**
 * @brief Compte le nombre de successeurs d'un sommet donné dans le graphe.
 *
 * @param graph Graphe sous forme de liste d'adjacence
 * @param sommet Indice du sommet
 * @return int Nombre de sommets accessibles depuis le sommet
 */
int cpt_sommet(t_list_adj graph, int sommet);


#endif
