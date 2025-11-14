#include <stdio.h>
#include <stdlib.h>
#include "list.h"
//#include "hasse.h"
#include "graphes.h"
#include "utils.h"


int main() {
    printGraph("../data/exemple1.txt");
    t_list_adj graph=readGraph("../data/exemple1.txt");
    grapheMarkov(&graph);
    return 0;
}
