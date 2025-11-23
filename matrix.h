#ifndef MATRIX_H
#define MATRIX_H

#include "list.h"

float **create_matrix_zero(int n);
float **graph_to_matrix(t_list_adj *list);
void copy_matrix(float **M1, float **M2, int n);
float **multiply_matrix(float **M1, float **M2, int n);
float diff_matrices(float **M1, float **M2, int n);

typedef struct {
    int** list_sommet;
    int* nb_sommet;
    int nb_composant;
} t_partition;

typedef struct {
    int rows;
    int cols;
    float** data;
} t_matrix;

t_matrix subMatrix(t_matrix matrix, t_partition part, int compo_index);

#endif //MATRIX_H
