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
 * @brief Crée une matrice carrée n x n initialisée à zéro.
 *
 * @param n Dimension de la matrice
 * @return t_matrix Matrice carrée remplie de zéros
 */
t_matrix create_matrix_zero(int n);


/**
 * @brief Convertit un graphe représenté par une liste d'adjacence en matrice de probabilités.
 *
 * @param list Pointeur vers la liste d'adjacence du graphe
 * @return t_matrix Matrice représentant les probabilités de transition
 */
t_matrix graph_to_matrix(t_list_adj *list);


/**
 * @brief Copie les valeurs d'une matrice M1 dans une matrice M2.
 *
 * @param M1 Matrice source
 * @param M2 Matrice destination (doit être déjà allouée)
 */
void copy_matrix(t_matrix M1, t_matrix M2);


/**
 * @brief Multiplie deux matrices carrées de même dimension.
 *
 * @param M1 Première matrice
 * @param M2 Deuxième matrice
 * @return t_matrix Résultat de la multiplication M1 x M2
 */
t_matrix multiply_matrix(t_matrix M1, t_matrix M2);


/**
 * @brief Calcule la somme des différences absolues entre deux matrices de même taille.
 *
 * @param M1 Première matrice
 * @param M2 Deuxième matrice
 * @return float Somme des différences absolues des éléments correspondants
 */
float diff_matrices(t_matrix M1, t_matrix M2);


/**
 * @brief Extrait une sous-matrice correspondant à une composante d'une partition.
 *
 * @param matrix Matrice originale
 * @param part Partition des sommets
 * @param compo_index Index de la composante dans la partition
 * @return t_matrix Sous-matrice correspondant à la composante
 */
t_matrix subMatrix(t_matrix matrix, t_partition part, int compo_index);


/**
 * @brief Affiche une matrice à l'écran avec deux décimales.
 *
 * @param M Matrice à afficher
 */
void print_matrix(t_matrix M);


/**
 * @brief Libère la mémoire allouée pour une matrice.
 *
 * @param M Matrice à libérer
 */
void free_matrix(t_matrix M);

#endif //MATRIX_H
