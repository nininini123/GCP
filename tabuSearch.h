//
// Created by 30838 on 2017/12/29.
//

#ifndef GRAPHCOLOR_TABUSEARCH_H
#define GRAPHCOLOR_TABUSEARCH_H


void randomSolution(int* solution, int length, int colorNum) ;
int getTargetFunc(int** matrix, int * solution, int length) ;
void move( int** matrix,int * solution, int length, int **tabuList, int tabuLen,int &tabuPtr , int colorNum ,int &target, int &targetBest ) ;


#endif //GRAPHCOLOR_TABUSEARCH_H
