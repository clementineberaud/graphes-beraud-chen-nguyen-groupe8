#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"

t_matrix create_matrix_zero(int n)
{
    t_matrix M;
    M.rows = n;
    M.cols = n;
    M.val = malloc(n * sizeof(float*)); // allocation place lignes
    for (int i = 0; i < n; i++) { // parcours lignes
        *(M.val + i) = malloc(n * sizeof(float)); // allocation place colonnes
        for (int j = 0; j < n; j++) { // parcours colonnes
            *(*(M.val + i) + j) = 0.00;
        }
    }
    return M;
}

t_matrix graph_to_matrix(t_list_adj *list)
{
    t_matrix M = create_matrix_zero(list->taille);
    for (int i = 0; i < list->taille; i++) {
        t_cell *curr = (*(list->T + i)).head; // tête de la liste du sommet i
        while (curr != NULL) {
            int j = curr->sommet - 1;
            *(*(M.val + i) + j) = curr->proba; // remplissage avec les probabilités de passage entre états
            curr = curr->next;
        }
    }
    return M;
}

void copy_matrix(t_matrix M1, t_matrix M2)
{
    for (int i = 0; i < M1.rows; i++) {
        for (int j = 0; j < M1.cols; j++) {
            *(*(M2.val + i) + j) = *(*(M1.val + i) + j); // on recopie les valeurs de M1 dans M2
        }
    }
}

t_matrix multiply_matrix(t_matrix M1, t_matrix M2) // ligne i de M1 x colonne j de M2
{
    int n = M1.rows;
    t_matrix M3 = create_matrix_zero(n);
    for (int i = 0; i < n; i++) { // parcours lignes de M1
        for (int k = 0; k < n; k++) { // parcours colonnes de M1 = parcours lignes de M2
            for (int j = 0; j < n; j++) { // parcours colonnes de M2
                *(*(M3.val + i) + j) += (*(*(M1.val + i) + k)) * (*(*(M2.val + k) + j)); // on stocke le résultat de la multiplication
            }
        }
    }
    return M3;
}

float diff_matrices(t_matrix M1, t_matrix M2) // cf formule sujet
{
    float somme = 0.00;
    int n = M1.rows;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            float diff = *(*(M1.val + i) + j) - *(*(M2.val + i) + j); // différence entre les deux valeurs
            if (diff < 0) {
                diff = -diff; // car valeur absolue
            }
            somme += diff;
        }
    }
    return somme;
}

t_matrix subMatrix(t_matrix matrix, t_partition part, int compo_index)
{
    int nombre_sommet = *(part.nb_sommet + compo_index); // nombre de sommets dans la composante
    int *sommets = *(part.list_sommet + compo_index); // tableau des indices de sommets

    // Création de la sous-matrice
    t_matrix sub = create_matrix_zero(nombre_sommet);

    // Remplissage de la sous-matrice avec les valeurs correspondantes
    for (int i = 0; i < nombre_sommet; i++) {
        for (int j = 0; j < nombre_sommet; j++) {
            *(*(sub.val + i) + j) = *(*(matrix.val + (*(sommets + i) - 1)) + (*(sommets + j) - 1));
        }
    }
    return sub;
}

void print_matrix(t_matrix M)
{
    int n = M.rows;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%.2f ", *(*(M.val + i) + j));
        }
        printf("\n");
    }
    printf("\n");
}

void free_matrix(t_matrix M) {
    for (int i = 0; i < M.rows; i++)
        free(*(M.val + i));
    free(M.val);
}