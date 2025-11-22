#ifndef MATRIX_H
#define MATRIX_H

#include "list.h"

float **create_matrix_zero(int n);
float **graph_to_matrix(t_list_adj *list);
void copy_matrix(float **M1, float **M2, int n);
float **multiply_matrix(float **M1, float **M2, int n);
float diff_matrices(float **M1, float **M2, int n);

#endif //MATRIX_H
