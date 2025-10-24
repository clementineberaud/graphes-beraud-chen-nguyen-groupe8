#ifndef __LIST_H__
#define __LIST_H__

typedef struct s_cell {
  int sommet;
  float proba;
  struct s_cell* next;
} t_cell;

typedef struct s_list {
  t_cell* head;
} t_list;

typedef struct s_list_adj {
  t_list *T;
  int taille;
} t_list_adj;


void printList(t_list* list);
t_list* create_empty_list();
t_list_adj createEmptyListADJ(int taille);
void printListADJ(t_list_adj adj);
#endif