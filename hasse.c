#include <stdlib.h>
#include "hasse.h"
#include "list.h"
#include "tarjan.h"

int link_in_tab (int a, int b, t_link_array *tab) { // on vérifie si le lien est déjà dans le tableau
    for (int i=0;i<tab->log_size;i++) {
    if (tab->links[i].to==b && tab->links[i].from==a) {
      return 1;
    }
  }
  return 0;
}


void addLink (t_link_array * tab, int a, int b) { // ajouter un lien au tableau de liens
    tab->links = realloc(tab->links, (tab->log_size + 1) * sizeof(t_link));
    tab->links[tab->log_size].from=a;
    tab->links[tab->log_size].to=b;
    tab->log_size++;
}


int* tab_classes (t_partition par, t_list_adj graph) { //tableau de classe par sommet
    int *classes = (int *) malloc(sizeof(int) * graph.taille);
    for (int i = 0; i < par.nb_composant; i++) {
        // on associe à l'indice i (= sommet i+1) le numéro de sa classe
        for (int j = 0; j < par.nb_sommet[i]; j++) {
            classes[par.list_sommet[i][j] - 1] = i + 1;
        }
    }
    return classes;
}


int cpt_sommet (t_list_adj graph, int sommet){ // on compte le nb de sommets d'arrivées du sommet de départ
    int cpt = 0;
    t_cell *temp = graph.T[sommet].head;
    while (temp != NULL) {
        cpt++;
        temp = temp->next;
    }
    return cpt;
}


t_link_array* diagramme_hasse (t_list_adj graph, t_partition par) { //renvoie un tableau de liens des classes
    int *classes = tab_classes(par, graph);
    t_link_array *tab = (t_link_array *) malloc(sizeof(t_link_array));
    tab->links = NULL;
    tab->log_size = 0;
    for (int i = 0; i < graph.taille; i++) {
        int Ci = classes[i]; //pour chaque sommet on regarde sa classe
        t_cell *temp = graph.T[i].head;

        while (temp != NULL) {

            // on regarde tous ses sommets d'arrivée
            int j = temp->sommet;
            int Cj = classes[j - 1];
            if (Ci != Cj) {

                // on vérifie que le sommet de départ et d'arrivée ne soient pas dans la même classe
                int test = link_in_tab(i + 1, j, tab); // test pour voir si leur lien est déjà dans le tableau

                if (test == 0) {
                    addLink(tab, i + 1, j); // sinon, on ajoute leur lien
                }
            }
            if (i + 1 == j && cpt_sommet(graph, i) == 1) {
                addLink(tab, i + 1, j); // si le sommet n'a que lui-même en sommet d'arrivée, on rajoute son lien
            }
            temp = temp->next;
        }
    }
    return tab;
}


void removeTransitiveLinks(t_link_array *p_link_array)
{
    int i = 0;
    while (i < p_link_array->log_size)
    {
        t_link link1 = p_link_array->links[i];
        int j = 0;
        int to_remove = 0;
        while (j < p_link_array->log_size && !to_remove)
        {
            if (j != i)
            {
                t_link link2 = p_link_array->links[j];
                if (link1.from == link2.from)
                {
                    // look for a link from link2.to to link1.to
                    int k = 0;
                    while (k < p_link_array->log_size && !to_remove)
                    {
                        if (k != j && k != i)
                        {
                            t_link link3 = p_link_array->links[k];
                            if ((link3.from == link2.to) && (link3.to == link1.to))
                            {
                                to_remove = 1;
                            }
                        }
                        k++;
                    }
                }
            }
            j++;
        }
        if (to_remove)
        {
            // remove link1 by replacing it with the last link
            p_link_array->links[i] = p_link_array->links[p_link_array->log_size - 1];
            p_link_array->log_size--;
        }
        else
        {
            i++;
        }
    }
}

