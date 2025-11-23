#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "graphes.h"
#include "tarjan.h"
#include "hasse.h"
#include "utils.h"


int main() {
    //test partie 1
    printGraph("../data/exemple_valid_step3.txt");
    t_list_adj graph=readGraph("../data/exemple_valid_step3.txt");
    grapheMarkov(&graph);

    //test partie 2
    t_partition part = tarjan(graph);
    t_link_array *tab=diagramme_hasse(graph,part);
    removeTransitiveLinks(tab);

    print_tarjan(part);
    printDiagrammeHasse(part,graph);
    carac_graphe_markov(graph);


    return 0;
}
