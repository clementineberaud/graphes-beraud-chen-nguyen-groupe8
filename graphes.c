#include "graphes.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>

t_list_adj readGraph(const char *filename)
{
  FILE *file = fopen(filename, "rt"); // read-only, text
  int nbvert, depart, arrivee;
  float proba;
  t_list_adj graph;
  if (file == NULL)
  {
    perror("Could not open file for reading");
    exit(EXIT_FAILURE);
  }

  // première ligne contient le nombre de sommets (=vertices)
  if (fscanf(file, "%d", &nbvert) != 1)
  {
    perror("Could not read number of vertices");
    exit(EXIT_FAILURE);
  }

  graph = createEmptyListAdj(nbvert);
  while (fscanf(file, "%d %d %f", &depart, &arrivee, &proba) == 3)
  {
    // on obtient, pour chaque ligne du fichier les valeurs depart, arrivee, proba
    addCell(&graph.T[depart-1], arrivee, proba);
  }
  fclose(file);
  return graph;
}