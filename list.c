#include "list.h"
#include <stdlio.h>

t_cell * createCell (int s, float p){
    t_cell * newCell=(t_cell*)malloc(sizeof(t_cell));
    newCell->sommet=s;
    newCell->proba=p;
    newCell->next=NULL;
    return newCell;
}

t_list createEmptyList () {
  t_list list=(t_list)malloc(sizeof(t_list));
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