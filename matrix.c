#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"

float **create_matrix_zero(int n)
{
    float **M = malloc(n * sizeof(float*)); // allocation place lignes
    for (int i = 0; i < n; i++) { // parcours lignes
        *(M + i) = malloc(n * sizeof(float)); // allocation place colonnes
        for (int j = 0; j < n; j++) { // parcours colonnes
            *(*(M + i) + j) = 0.00;
        }
    }
    return M;
}

float **graph_to_matrix(t_list_adj *list)
{
    float **M = create_matrix_zero(list->taille);
    for (int i = 0; i < list->taille; i++) {
        t_cell *curr = (*(list->T + i)).head; // tête de la liste du sommet i
        while (curr != NULL) {
            int j = curr->sommet;
            *(*(M + i) + j) = curr->proba; // remplissage avec les probabilités de passage entre états
            curr = curr->next;
        }
    }
    return M;
}

void copy_matrix(float **M1, float **M2, int n)
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            *(*(M2 + i) + j) = *(*(M1 + i) + j); // on recopie les valeurs de M1 dans M2
        }
    }
}

float **multiply_matrix(float **M1, float **M2, int n) // ligne i de M1 x colonne j de M2
{
    float **M3 = create_matrix_zero(n);
    for (int i = 0; i < n; i++) { // parcours lignes de M1
        for (int k = 0; k < n; k++) { // parcours colonnes de M1 = parcours lignes de M2
            for (int j = 0; j < n; j++) { // parcours colonnes de M2
                *(*(M3 + i) + j) += (*(*(M1 + i) + k)) * (*(*(M2 + k) + j)); // on stocke le résultat de la multiplication
            }
        }
    }
    return M3;
}

float diff_matrices(float **M1, float **M2, int n) // cf formule sujet
{
    float somme = 0.00;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            float diff = *(*(M1 + i) + j) - *(*(M2 + i) + j); // différence entre les deux valeurs
            if (diff < 0) {
                diff = -diff; // car valeur absolue
            }
            somme += diff;
        }
    }
    return somme;
}



t_matrix subMatrix(t_matrix matrix, t_partition part, int compo_index){
    int nombre_sommet = part.nb_sommet[compo_index];       // nombre de sommets dans la composante
    int* sommets = part.list_sommet[compo_index]; // tableau des sommets

    // Allocation de la sous-matrice n x n
    t_matrix sub = malloc(nombre_sommet * sizeof(float*));
    for (int i = 0; i < nombre_sommet; i++) {
        sub[i] = malloc(nombre_sommet * sizeof(float));
    }

    // Remplissage de la sous-matrice
    for (int i = 0; i < nombre_sommet; i++) {
        for (int j = 0; j < nombre_sommet; j++) {
            sub[i][j] = matrix[sommets[i]][sommets[j]];
        }
    }

    return sub;
}
