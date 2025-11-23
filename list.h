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


/**
 * @brief Crée une cellule de liste avec un sommet et sa probabilité.
 *
 * @param s Sommet à stocker dans la cellule
 * @param p Probabilité associée au sommet
 * @return t_cell* Pointeur vers la nouvelle cellule
 */
t_cell * createCell (int s, float p);


/**
 * @brief Crée une liste vide.
 *
 * @return t_list* Pointeur vers la nouvelle liste vide
 */
t_list * createEmptyList ();


/**
 * @brief Ajoute une cellule au début de la liste.
 *
 * @param list Pointeur vers la liste
 * @param s Sommet à ajouter
 * @param p Probabilité associée au sommet
 */
void addCell (t_list * list, int s, float p);


/**
 * @brief Affiche le contenu d'une liste de cellules.
 *
 * @param list Pointeur vers la liste à afficher
 */
void printList(t_list* list);


/**
 * @brief Crée une liste d'adjacence vide pour un graphe de taille donnée.
 *
 * @param taille Nombre de sommets dans le graphe
 * @return t_list_adj Liste d'adjacence initialisée
 */
t_list_adj createEmptyListADJ(int taille);


/**
 * @brief Affiche le contenu de toutes les listes d'adjacence d'un graphe.
 *
 * @param adj Liste d'adjacence du graphe
 */
void printListADJ(t_list_adj adj);


#endif
