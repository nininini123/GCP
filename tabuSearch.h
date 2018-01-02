//
// Created by 30838 on 2017/12/29.
//

#ifndef GRAPHCOLOR_TABUSEARCH_H
#define GRAPHCOLOR_TABUSEARCH_H


#include "tabuList.h"

int getTargetFunc(int** adj, int * adjLen, int * solution, int p) ;
void randomSolution(int* solution, int length, int colorNum) ;
void move( int** adjColorTable,int** tabuTable ,int * solution, int length, int colorNum ,int &target, int &targetBest ,tabuList** head ,int**adj, int* adjLen) ;
//void initAdjacent( int* &adj[],int* adjLength, int p, int ** matrix ) ;
void initAdjColorTable(int** adjColorTable,int ** adj,int * adjLen,int p ,int colorNum, int solution[]) ;

#endif //GRAPHCOLOR_TABUSEARCH_H
