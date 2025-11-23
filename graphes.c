#include "graphes.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>

#include "tarjan.h"
#include "utils.h"
#include "hasse.h"

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

  	graph = createEmptyListADJ(nbvert);
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
  	t_list_adj graph = readGraph(filename);
	FILE *file = fopen("../printedGraph.txt", "wt"); // write-only, text

	if (file == NULL) {
		printf("Error, file not found\n");
		return;
	}
    // directives de configuration
    fprintf(file, "---\nconfig:\n");
    fprintf(file, "\tlayout: elk\n\ttheme: neo\n\tlook: neo\n");
	fprintf(file, "---\n\n");

    // noms de sommets, suivi des numéros à afficher
    fprintf(file, "flowchart LR\n");
    for (int i = 0; i < graph.taille; i++)
    {
    	char *val = getID(i+1); // nombre converti en lettre
        fprintf(file, "%s((%d))\n", val, i+1);
    }

    // arêtes, avec leurs probabilités
    for (int i = 0; i < graph.taille; i++) {
    	t_cell * temp=graph.T[i].head;
    	while (temp!=NULL) {
    		char *val1 = getID(i+1);
    		fprintf(file, "%s ",val1);// sommet de départ (converti en lettre)
    		char *val2 = getID(temp->sommet); // sommet d'arrivée (converti en lettre)
    		double proba = temp->proba; // probabilité associée
    		fprintf(file, "-->|%.2lf|%s\n", proba, val2);
    		temp=temp->next;
    	}
    }
  
    fclose(file);
}

void grapheMarkov (t_list_adj* list) {
  int verif=1;
  //verif indique si c'est un graphe de Markov; il passe à 0 quand les probas d'un sommet ne sont pas égales à 1
  float somme=0;
  for (int i=0;i<list->taille;i++){
  	somme=0;
    t_cell * temp=list->T[i].head;
    while (temp->next!=NULL) { //somme des probabs d'un sommet
      somme+= temp->proba;
      temp=temp->next;
    }
    somme+= temp->proba;
    if ((somme<0.99) || (somme>1)){ //on verifie que la somme est entre 0.99 et 1
        printf("La somme des probabilites du sommet %d est %.2f\n",i+1,somme);
        verif=0;
    }
  }
  if (verif==0) {
    printf("Le graphe n'est pas un graphe de Markov.\n");
  } else {
    printf("Le graphe est un graphe de Markov.\n");
  }
}

void printDiagrammeHasse(t_partition part,t_list_adj graph)
{

	FILE *file = fopen("../printedDiagram.txt", "wt"); // write-only, text

	if (file == NULL) {
		printf("Error, file not found\n");
		return;
	}
	// directives de configuration
	fprintf(file, "---\nconfig:\n");
	fprintf(file, "\tlayout: elk\n\ttheme: neo\n\tlook: neo\n");
	fprintf(file, "---\n\n");

	// noms des classes, suivi des sommets à afficher
	fprintf(file, "flowchart LR\n");

	for (int i = 0; i < part.nb_composant; i++)
	{

		char *val = getID(i+1); // nombre converti en lettre

		fprintf(file, "%s[\"{", val);

		for (int j = 0; j < part.nb_sommet[i]-1; j++) {
			fprintf(file, "%d,", part.list_sommet[i][j]);
		}
		fprintf(file, "%d", part.list_sommet[i][part.nb_sommet[i]-1]);
		fprintf(file, "}\"]\n");
	}

	t_link_array *tab= diagramme_hasse(graph,part);
	removeTransitiveLinks(tab);
	int* classes=tab_classes(part,graph);

	// liens entre les classes
	for (int i = 0; i < tab->log_size; i++) {

		int c1=classes[tab->links[i].from-1];
		int c2=classes[tab->links[i].to-1];
		char *val1 = getID(c1);
		fprintf(file, "%s ",val1);// sommet de départ
		char *val2 = getID(c2); // sommet d'arrivée
		fprintf(file, "-->%s\n", val2);


	}

	fclose(file);
}

void carac_graphe_markov(t_list_adj graph) {
	t_partition part=tarjan(graph);
	t_link_array *tab=diagramme_hasse(graph,part);

	removeTransitiveLinks(tab);
	int *classes=tab_classes(part,graph);
	int etats_classes[part.nb_composant]; //tableau de taille du nombre de classes
	for (int i = 0; i < part.nb_composant; i++) etats_classes[i] = 0; //chaque classe est initialisée à 0 (0=persistent)

	if (part.nb_composant==1) { // si 1 classe alors irreductible
		printf("Le graphe est irreductible.\n");
	} else {
		for (int j=0;j<tab->log_size;j++) { //sinon on test si des sommets de la classe on a lien
			int classe=classes[tab->links[j].from-1];
			etats_classes[classe]=1; // on passe 1 si il y a un lien
		}
	}

	for (int k = 0; k < part.nb_composant; k++) {
		if (etats_classes[k]==1) { //si la classe = 1 alors transitoire
			printf("La classe C%d est transitoire.\n",k+1);
		} else { //sinon on affiche persistent
			printf("La classe C%d est persistente.\n",k+1);
			if (part.nb_sommet[k]==1) //on verifie le nombre de sommet dans la classe
				printf("L'etat est absorbant.\n"); //quand il y en a un on dit que c'est absorbant
		}
	}

}