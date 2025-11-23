#ifndef GRAPHES_H
#define GRAPHES_H

#include "list.h"
#include "utils.h"

/**
 * @brief Lit un graphe depuis un fichier texte et construit une liste d'adjacence.
 *
 * Le fichier doit contenir :
 *  - sur la première ligne : le nombre de sommets,
 *  - sur les lignes suivantes : des triplets (depart, arrivee, proba).
 *
 * La fonction crée une structure t_list_adj et y insère les arcs lus.
 *
 * @param filename Nom du fichier contenant la description du graphe.
 * @return t_list_adj La liste d'adjacence représentant le graphe.
 */

t_list_adj readGraph(const char *filename);


/**
 * @brief Vérifie si une liste d'adjacence représente un graphe de Markov.
 *
 * Pour chaque sommet, la fonction calcule la somme des probabilités
 * d'arcs sortants et vérifie qu'elle est comprise entre 0.99 et 1.
 *
 * Si tous les sommets respectent cette propriété, le graphe est déclaré
 * conforme à un graphe de Markov (matrice stochastique).
 *
 * @param list Pointeur vers la liste d'adjacence du graphe.
 */
void grapheMarkov (t_list_adj* list);


/**
 * @brief Lit un graphe depuis un fichier et génère une visualisation dans printedGraph.txt.
 *
 * La fonction lit d'abord le graphe avec readGraph(), puis écrit un fichier
 * contenant une description au format Mermaid/flowchart pour visualiser :
 *  - les sommets numérotés,
 *  - les arcs avec leurs probabilités.
 *
 * @param filename Nom du fichier contenant le graphe à afficher.
 */
void printGraph(const char *filename);

#endif //GRAPHES_H
