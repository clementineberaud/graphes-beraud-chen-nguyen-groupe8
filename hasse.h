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
 * @brief Vérifie si un lien (a → b) existe déjà dans un tableau de liens.
 *
 * Parcourt le tableau dynamique de liens et compare les champs `from`
 * et `to` pour déterminer si le lien recherché est présent.
 *
 * @param a Sommet de départ.
 * @param b Sommet d'arrivée.
 * @param tab Tableau de liens dans lequel effectuer la recherche.
 * @return 1 si le lien est trouvé, 0 sinon.
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

int* tab_classes (t_partition par, t_list_adj graph);




/**
 * @brief Ajoute un nouveau lien (a → b) dans un tableau de liens.
 *
 * Parcourt la taille logique du tableau pour trouver la prochaine
 * position disponible, puis y copie le lien créé.
 *
 * @param tab Tableau de liens dans lequel insérer le nouveau lien.
 * @param a Sommet source.
 * @param b Sommet destination.
 */
void addLink (t_link_array * list, int a, int b);


/**
 * @brief Construit le diagramme de Hasse des classes du graphe.
 *
 * Pour chaque arc du graphe, si les sommets appartiennent à des classes
 * différentes, un lien entre classes est ajouté dans la structure résultante.
 * Ceci permet de représenter l’ordre entre composantes fortement connexes.
 *
 * @param graph Structure de liste d'adjacence du graphe.
 * @param par Partition des sommets en composantes fortement connexes.
 * @return t_link_array* Tableau de liens représentant le diagramme de Hasse.
 */
t_link_array * diagramme_hasse (t_list_adj graph, t_partition par);



/**
 * @brief Supprime les liens transitifs dans un diagramme de Hasse.
 *
 * Si un lien A → C est implicite via A → B et B → C, la fonction supprime
 * le lien A → C afin de conserver uniquement les liens indispensables pour
 * représenter l'ordre partiel.
 *
 * @param p_link_array Tableau de liens à simplifier.
 */
void removeTransitiveLinks(t_link_array *p_link_array);


#endif