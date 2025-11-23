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
 * @brief Crée et initialise une cellule de liste d’adjacence.
 *
 * Alloue dynamiquement une structure t_cell contenant le sommet de destination
 * et la probabilité associée, puis initialise le pointeur vers la cellule suivante à NULL.
 *
 * @param s Sommet de destination.
 * @param p Probabilité associée à l’arête.
 * @return t_cell* Pointeur vers la cellule nouvellement créée.
 */
t_cell * createCell (int s, float p);


/**
 * @brief Crée et initialise une liste vide pour représenter les successeurs d’un sommet.
 *
 * Alloue dynamiquement une structure t_list et initialise sa tête à NULL.
 *
 * @return t_list* Pointeur vers la liste vide.
 */
t_list * createEmptyList ();


/**
 * @brief Ajoute une cellule au début d’une liste d’adjacence.
 *
 * Crée une nouvelle cellule contenant le sommet et la probabilité,
 * puis l’insère en tête de la liste.
 *
 * @param list Liste dans laquelle ajouter la cellule.
 * @param s Sommet de destination.
 * @param p Probabilité associée à l’arête.
 */
void addCell (t_list * list, int s, float p);


/**
 * @brief Affiche le contenu d’une liste d’adjacence pour un sommet.
 *
 * Parcourt la liste et affiche chaque cellule sous la forme (sommet, probabilité),
 * en indiquant la structure de la liste.
 *
 * @param list Pointeur vers la liste à afficher.
 */
void printList(t_list* list);


/**
 * @brief Crée une structure de liste d’adjacence vide pour tout le graphe.
 *
 * Alloue un tableau de t_list de taille `taille` et initialise chaque liste à vide.
 *
 * @param taille Nombre de sommets du graphe.
 * @return t_list_adj Structure contenant toutes les listes d’adjacence initialisées.
 */
t_list_adj createEmptyListADJ(int taille);


/**
 * @brief Affiche toutes les listes d’adjacence d’un graphe.
 *
 * Parcourt le tableau de listes et appelle printList sur chacune.
 *
 * @param adj Liste d’adjacence du graphe à afficher.
 */
void printListADJ(t_list_adj adj);


#endif
