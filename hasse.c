#include <malloc.h>
#include "hasse.h"
#include "list.h"
#include "tarjan.h"


int link_in_tab (int a, int b, t_link_array *tab) {
  for (int i=0;i<tab->log_size;i++) {
    if (tab->links[i].to==b && tab->links[i].from==a) {
      return 1;
    }
  }
  return 0;
}

t_link * createLink (int a, int b){
    t_link * new=(t_link*)malloc(sizeof(t_link));
    new->from=a;
    new->to=b;
    return new;
}

void addLink (t_link_array * tab, int a, int b) {
  int cpt=0;
  for (int i=0;i<tab->log_size;i++) {
    cpt++;
  }
  t_link* link = createLink(a,b);
  tab->links[cpt]=*link;
}

int* tab_classes (t_partitions par, t_list_adj graph) {
  int * classes=(int*)malloc(sizeof(int)*graph.taille);
  for (int i=0;i<par.nb_composant;i++) {
    for (int j=0;j<par.nb_sommet[i];j++) {
      classes[par.list_sommet[i][j]-1]=i+1;
    }
  }
  return classes;
}

t_link_array* diagramme_hasse (t_list_adj graph, t_partitions par) {
  int * classes=tab_classes(par,graph);
  t_link_array tab;
  for (int i=0;i<graph.taille;i++) {
    int Ci=classes[i];
    t_cell * temp=graph.T[i].head;
    while (temp!=NULL) {
      int j=temp->sommet;
      int Cj=classes[j-1];
      if (Ci!=Cj) {
        int test=link_in_tab(i+1,j,&tab);
        if (test==0){
          addLink(&tab,i+1,j);
        }
      }
    }
  }
  return &tab;
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

