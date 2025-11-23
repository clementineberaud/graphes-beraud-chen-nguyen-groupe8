#ifndef MATRIX_H
#define MATRIX_H

#include "list.h"
#include "tarjan.h"

typedef struct {
    int rows; // nombre de lignes
    int cols; // nombre de colonnes
    float **val; // pointeur vers matrice
} t_matrix;


/**
 * @brief Crée une matrice carrée initialisée à zéro.
 *
 * Alloue dynamiquement une matrice de taille n×n et initialise toutes les
 * valeurs à 0.0.
 *
 * @param n Dimension de la matrice.
 * @return t_matrix La matrice créée avec toutes les valeurs à zéro.
 */
t_matrix create_matrix_zero(int n);


/**
 * @brief Convertit une liste d’adjacence en matrice d’adjacence.
 *
 * Remplit une matrice n×n avec les probabilités de transition
 * contenues dans la liste d’adjacence.
 *
 * @param list Pointeur vers la liste d’adjacence du graphe.
 * @return t_matrix Matrice d’adjacence correspondant au graphe.
 */
t_matrix graph_to_matrix(t_list_adj *list);


/**
 * @brief Copie le contenu d’une matrice dans une autre.
 *
 * Recopie toutes les valeurs de la matrice source M1 dans la matrice cible M2.
 *
 * @param M1 Matrice source.
 * @param M2 Matrice cible.
 */
void copy_matrix(t_matrix M1, t_matrix M2);


/**
 * @brief Multiplie deux matrices carrées.
 *
 * Effectue la multiplication matricielle M1 × M2 et retourne le résultat.
 *
 * @param M1 Première matrice.
 * @param M2 Deuxième matrice.
 * @return t_matrix Résultat de la multiplication.
 */
t_matrix multiply_matrix(t_matrix M1, t_matrix M2);


/**
 * @brief Calcule la somme des différences absolues entre deux matrices.
 *
 * Utile pour mesurer la convergence des distributions de Markov.
 *
 * @param M1 Première matrice.
 * @param M2 Deuxième matrice.
 * @return float Somme des différences absolues élément par élément.
 */
float diff_matrices(t_matrix M1, t_matrix M2);


/**
 * @brief Extrait une sous-matrice correspondant à une composante d’un graphe.
 *
 * Garde uniquement les lignes et colonnes correspondant aux sommets
 * d’une composante fortement connexe.
 *
 * @param matrix Matrice originale.
 * @param part Partition du graphe en composantes fortement connexes.
 * @param compo_index Index de la composante à extraire.
 * @return t_matrix Sous-matrice correspondant à la composante.
 */
t_matrix subMatrix(t_matrix matrix, t_partition part, int compo_index);


/**
 * @brief Affiche une matrice à l’écran.
 *
 * Parcourt la matrice et affiche chaque élément avec deux décimales.
 *
 * @param M Matrice à afficher.
 */
void print_matrix(t_matrix M);


/**
 * @brief Libère la mémoire allouée pour une matrice.
 *
 * Parcourt toutes les lignes pour libérer chaque sous-tableau,
 * puis libère le tableau principal.
 *
 * @param M Matrice à libérer.
 */
void free_matrix(t_matrix M);

#endif //MATRIX_H
