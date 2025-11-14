//
// Created by lana chen on 24/10/2025.
//

#ifndef TARJAN_H
#define TARJAN_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct s_tarjan_vertex {
    int identifiant;
    int numero;
    int num_accessible;
    bool indicateur;
}t_tarjan_vertex;

typedef t_tarjan_vertex* t_tarjan;

typedef struct s_classe {
    char nom;
    int nb_sommet;
}t_classe;

typedef t_classe* t_partition;

#endif //TARJAN_H
