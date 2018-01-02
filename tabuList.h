//
// Created by 30838 on 2017/12/31.
//

#ifndef GRAPHCOLOR_TABULIST_H
#define GRAPHCOLOR_TABULIST_H

typedef struct tabulist{
    struct tabulist * previous;
    struct tabulist * next;
    int tabuItem[2];
} tabuList;

void initTabu(tabuList** head, int length) ;
void addTabu(tabuList** head ) ;
//void deleteTabu(tabuList** head ) ;
void deleteTabu(tabuList** head , int** tabuTable );
void updateTabu(tabuList** head, int a, int b, int** tabuTable) ;

#endif //GRAPHCOLOR_TABULIST_H
