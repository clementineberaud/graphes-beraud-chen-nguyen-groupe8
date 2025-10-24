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

t_cell * createCell (int s, float p);
t_list createEmptyList ();
void addCell (t_list * list, int s, float p);
#endif