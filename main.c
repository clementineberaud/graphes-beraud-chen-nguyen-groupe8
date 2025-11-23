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
    t_matrix M = graph_to_matrix(&meteo);

    int n = M.rows;

    printf("Matrice M :\n");
    print_matrix(M);

    // ====== Calcul de M^3 ======
    t_matrix M2 = multiply_matrix(M, M);       // M^2
    t_matrix M3 = multiply_matrix(M2, M);      // M^3

    printf("M^3 :\n");
    print_matrix(M3);

    // libérer intermédiaires
    free_matrix(M2);

    // ====== Calcul de M^7 ======
    t_matrix M4 = multiply_matrix(M3, M);      // M^4
    t_matrix M5 = multiply_matrix(M4, M);      // M^5
    t_matrix M6 = multiply_matrix(M5, M);      // M^6
    t_matrix M7 = multiply_matrix(M6, M);      // M^7

    printf("M^7 :\n");
    print_matrix(M7);

    // libérer intermédiaires
    free_matrix(M4);
    free_matrix(M5);
    free_matrix(M6);

    // ====== Calcul de M^k jusqu'à convergence ======
    t_matrix Mk_prev = create_matrix_zero(n);
    copy_matrix(M, Mk_prev);          // copie M dans Mk_prev

    t_matrix Mk = multiply_matrix(M, M); // M^2
    int k = 2;

    while (diff_matrices(Mk_prev, Mk) >= 0.01) {
        free_matrix(Mk_prev);                  // libérer l’ancienne matrice
        Mk_prev = create_matrix_zero(n);
        copy_matrix(Mk, Mk_prev);             // copier Mk dans Mk_prev

        t_matrix temp = multiply_matrix(Mk, M); // calculer M^(k+1)
        free_matrix(Mk);                        // libérer l’ancienne Mk
        Mk = temp;

        k++;
        if (k > 1000) break; // sécurité anti-boucle infinie
    }

    printf("M^%d atteint une variation < 0.01 :\n", k);
    print_matrix(Mk);

    // libérer toutes les matrices
    free_matrix(M);
    free_matrix(Mk_prev);
    free_matrix(Mk);
    free_matrix(M3);
    free_matrix(M7);

    return 0;
}