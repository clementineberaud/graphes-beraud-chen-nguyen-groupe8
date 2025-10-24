#include "list.h"


void printList(t_list list){
    if (is_empty(list)) {
        printf("[]");
    } else {
        t_cell *cell = list;
        while (cell != NULL) {
            print_cell(*cell);
            cell = cell->next;
        }
    }

}
