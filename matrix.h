#ifndef MATRIX_H
#define MATRIX_H

#include "list.h"
#include "tarjan.h"

typedef struct {
    int rows; // nombre de lignes
    int cols; // nombre de colonnes
    float **val; // pointeur vers matrice
} t_matrix;

t_matrix create_matrix_zero(int n);
t_matrix graph_to_matrix(t_list_adj *list);
void copy_matrix(t_matrix M1, t_matrix M2);
t_matrix multiply_matrix(t_matrix M1, t_matrix M2);
float diff_matrices(t_matrix M1, t_matrix M2);
t_matrix subMatrix(t_matrix matrix, t_partition part, int compo_index);
void print_matrix(t_matrix M);
void free_matrix(t_matrix M);

#endif //MATRIX_H
