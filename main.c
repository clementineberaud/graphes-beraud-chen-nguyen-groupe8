#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "graphes.h"
#include "hasse.h"
#include "utils.h"
#include "matrix.h"

int main()
{
    // ====== Lire le fichier météo ======
    t_list_adj meteo = readGraph("../data/exemple_meteo.txt");

    // ====== Convertir en matrice ======
    float **M = graph_to_matrix(&meteo);

    int n = meteo.taille;

    printf("Matrice M :\n");
    print_matrix(M, n);

    // ====== Calcul de M^3 ======
    float **M2 = multiply_matrix(M, M, n);
    float **M3 = multiply_matrix(M2, M, n);

    printf("M^3 :\n");
    print_matrix(M3, n);

    // ====== Calcul de M^7 ======
    float **M4 = multiply_matrix(M3, M, n);
    float **M5 = multiply_matrix(M4, M, n);
    float **M6 = multiply_matrix(M5, M, n);
    float **M7 = multiply_matrix(M6, M, n);

    printf("M^7 :\n");
    print_matrix(M7, n);

    // ====== Calcul de M^k jusqu'à convergence ======
    float **Mk_prev = M;
    float **Mk = multiply_matrix(M, M, n);
    int k = 2;

    while (diff_matrices(Mk_prev, Mk, n) >= 0.01) {

        // libérer l’ancienne matrice
        Mk_prev = Mk;

        // calculer M^(k+1)
        float **temp = multiply_matrix(Mk, M, n);
        Mk = temp;

        k++;
        if (k > 1000) break; // sécurité anti-boucle infinie
    }

    printf("M^%d atteint une variation < 0.01 :\n", k);
    print_matrix(Mk, n);

    return 0;
}