#ifndef GRAPHES_H
#define GRAPHES_H

#include "list.h"
#include "tarjan.h"
#include "utils.h"

/**
 * @brief Lit un graphe depuis un fichier et le retourne sous forme de liste d'adjacence.
 *
 * @param filename Nom du fichier contenant le graphe
 * @return t_list_adj Graphe représenté par des listes d'adjacence
 */

t_list_adj readGraph(const char *filename);


/**
 * @brief Vérifie si le graphe est un graphe de Markov (somme des probabilités de chaque sommet = 1).
 *
 * @param list Pointeur vers le graphe sous forme de liste d'adjacence
 */
void grapheMarkov (t_list_adj* list);


/**
 * @brief Lit un graphe depuis un fichier et génère un fichier texte représentant le graphe.
 *
 * @param filename Nom du fichier contenant le graphe
 */
void printGraph(const char *filename);



/**
 * @brief Génère un fichier texte représentant le diagramme de Hasse à partir d'une partition et du graphe.
 *
 * @param part Partition des composantes fortement connexes
 * @param graph Graphe sous forme de liste d'adjacence
 */
void printDiagrammeHasse(t_partition part,t_list_adj graph);



/**
 * @brief Caractérise les classes d'un graphe de Markov en identifiant les classes persistantes, transitoires et les états absorbants.
 *
 * @param graph Graphe sous forme de liste d'adjacence
 */
void carac_graphe_markov(t_list_adj graph);

#endif //GRAPHES_H
