#include "graphes.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include "util.h"

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

void printGraph(const char *filename)
{
  	graph = readGraph(filename);
	FILE *file = fopen("printedGraph.txt", "wt"); // write-only, text

    // directives de configuration
    fprintf(file, "---\nconfig:\n");
    fprintf(file, "\tlayout: elk\n\ttheme: neo\n\tlook: neo\n");
	fprintf(file, "---\n\n");

    // noms de sommets, suivi des numéros à afficher
    fprintf(file, "flowchart LR\n");
    for (int i = 0; i < graph.taille; i++)
    {
    	char *val = getId(graph.T[i]->depart); // nombre converti en lettre
        fprintf(file, "%s((%d))\n", val, graph.T[i]->depart);
    }

    // arêtes, avec leurs probabilités
    for (int i = 0; i < graph.taille; i++) {
      	char *val1 = getId(graph.T[i]->depart); // sommet de départ (converti en lettre)
        char *val2 = getId(graph.T[i]->arrivee); // sommet d'arrivée (converti en lettre)
        double proba = graph.T[i]->proba; // probabilité associée
    	fprintf(file, "%s -->|%lf|%s\n", val1, proba, val2);
    }
  
    fclose(file);
}

void grapheMarkov (t_list_adj* list) {
  int verif=1;
  //verif indique si c'est un graphe de Markov; il passe à 0 quand les probas d'un sommet ne sont pas égales à 1
  float somme=0;
  for (int i=0;i<list->taille;i++){
    t_cell * temp=list->T[i].head;
    while (temp->next!=NULL) { //somme des probabs d'un sommet
      somme+= temp->proba;
      temp=temp->next;
    }
    somme+= temp->proba;
    if ((somme<0.99) || (somme>1)){ //on verifie que la somme est entre 0.99 et 1
        printf("La somme des probabilités du sommet %d est %f",i+1,somme);
        verif=0;
    }
  }
  if (verif==0) {
    printf("Le graphe n'est pas un graphe de Markov");
  } else {
    printf("Le graphe est un graphe de Markov");
  }
}