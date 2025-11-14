#include "list.h"
#include <stdlib.h>
#include <stdio.h>

t_cell * createCell (int s, float p){
    t_cell * newCell=(t_cell*)malloc(sizeof(t_cell));
    newCell->sommet=s;
    newCell->proba=p;
    newCell->next=NULL;
    return newCell;
}

t_list * createEmptyList () {

  t_list * list=(t_list*)malloc(sizeof(t_list));

  list->head=NULL;
  return list;
}

void addCell (t_list * list, int s, float p) {
  t_cell * cell=createCell(s,p);
  if (list->head==NULL) {
      list->head=cell;
      return;
  }
  t_cell *temp=list->head;
  list->head=cell;
  cell->next=temp;
  return;
}




void printList(t_list* list){
    if (list->head == NULL) {
        printf("Liste vide\n");
        return;
    }
    t_cell *cell = list->head;
    printf("Liste pour le sommet %d:",list->head->sommet);
    printf("[head @] -> ");
    while (cell != NULL) {
        printf("(");
        printf("%d, %f ", cell->sommet, cell->proba);
        printf(")");
        if (cell->next !=NULL) {
            printf(" @-> ");
        }
        cell = cell->next;
    }
}


t_list_adj createEmptyListADJ(int taille) {
    t_list_adj list_adj;
    list_adj.taille = taille;
    list_adj.T = (t_list*) malloc(taille * sizeof(t_list));

    for (int i = 0; i < taille; i++) {
        t_list *list = createEmptyList();
        list_adj.T[i] = *list;
        free(list);
    }

    return list_adj;
}


void printListADJ(t_list_adj adj) {
    for (int i = 0; i < adj.taille; i++) {
        printList(&adj.T[i]);
    }
}



