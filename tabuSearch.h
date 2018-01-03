//
// Created by 30838 on 2017/12/29.
//

#ifndef GRAPHCOLOR_TABUSEARCH_H
#define GRAPHCOLOR_TABUSEARCH_H
//
//#define TABUTENURE ( target + rand() % 10  +  iterTimes )
//#define TABUTENURE_STR "target+ rand() % 10 +  iterTimes "

#define TABUTENURE ( target + rand() % 18  +  20 + iterTimes + 2 *colorNum * freq[nonTabuBest[0]][nonTabuBest[1]] / freq[nonTabuBest[0]][colorNum] )
#define TABUTENURE_STR "target+ rand() % 18 +  20 + iterTimes + 2 *colorNum * freq[i][j] / freq_all )"

//#include "tabuList.h"

int getTargetFunc(int** adj, int * adjLen, int * solution, int p) ;
void randomSolution(int* solution, int length, int colorNum) ;
void move( int** adjColorTable,int** tabuTable ,int * solution, int length, int colorNum ,int &target, int &targetBest ,int**adj, int* adjLen, int iterTimes , int& tabuTenure,int** freq ) ;
//void initAdjacent( int* &adj[],int* adjLength, int p, int ** matrix ) ;
void initAdjColorTable(int** adjColorTable,int ** adj,int * adjLen,int p ,int colorNum, int solution[]) ;

#endif //GRAPHCOLOR_TABUSEARCH_H
