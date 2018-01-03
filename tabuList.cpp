#include "tabuList.h"

//typedef struct tabulist{
//    struct tabulist * previous;
//    struct tabulist * next;
//    int tabuItem[2];
//} tabuList;

void initTabu(tabuList** head, int length) {
    tabuList * ptr;
    ptr = new tabuList;
    *head = ptr;
    ptr->next =ptr->previous = ptr;
    for (int i = 1; i < length ; i++) {
        addTabu(head);
    }
}

void addTabu(tabuList** head ) {
    tabuList * ptr;
    ptr = new tabuList();
    ptr->tabuItem[0] = -1;
    ptr->previous = (*head)->previous ;
    (*head)->previous->next = ptr ;
    (*head)->previous = ptr;
    ptr->next = *head ;
}

void deleteTabu(tabuList** head , int** tabuTable ) {
    tabuList * ptr = (*head)->previous;
    if (ptr->tabuItem[0] >= 0 ) {
        tabuTable[ ptr->tabuItem[0] ][ ptr->tabuItem[1] ] = 0 ;
    }
    ptr= ptr->previous;
    delete ptr->next ;
    ptr->next = (*head);
    (*head)->previous = ptr;
}

void updateTabu(tabuList** head, int a, int b, int** tabuTable) {
    (*head) = (*head)->previous ;
    if ((*head)->tabuItem[0] >= 0) {
        tabuTable[(*head)->tabuItem[0] ][ (*head)->tabuItem[1] ] =0 ;
    }
    (*head)->tabuItem[0] = a ;
    (*head)->tabuItem[1] = b ;
    tabuTable[a][b] = 1 ;
}