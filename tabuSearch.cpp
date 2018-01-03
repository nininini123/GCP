//
// Created by 30838 on 2017/12/28.
//

#include <iostream>
#include <random>
#include <Windows.h>
#include "tabuSearch.h"
//#include "tabuList.h"

#define INF 10000

using namespace std;

void randomSolution(int* solution, int length, int colorNum) {
//    random_device rd ;
    for (int i = 0; i < length ; ++i) {
//        solution[i] = rd() % colorNum;
        solution[i] = rand() % colorNum;
//        solution[i] = 0 ; //rand() % colorNum;
    }
    cout << "done random solution" << endl;
}

/***
 *
 * @param solution
 * @param length    结点数
 * @param tabuList
 * @param tabuTenure
 * @param targetBest 历史最优的target
 * @return target 当前solution对应的冲突数之和
 */
void move( int** adjColorTable,int** tabuTable ,int * solution, int length, int colorNum ,int &target, int &targetBest ,int**adj, int* adjLen , int iterTimes , int& tabuTenure, int** freq) {
    int delta =0 ;
    int tabuBest[3] ={0,0,INF};
    int nonTabuBest[3] = {0,0,INF} ; //记录 当前最优的禁忌/非禁忌move的 节点号  & new 颜色  &delta

    //cout << "starting looking for best move ..."<< endl;
    /*** find a best move ***/
    for (int i = 0; i < length ; ++i) {
        //第 i个结点
        //换成颜色j
        //与k是邻居
        if (   adjColorTable[i][ solution[i] ] > 0 )///////////////////////////////记得换啊啊啊回来
        {
            for (int j = 0; j < colorNum; ++j) {
                if (solution[i] != j) {
                    //求delta
                    delta = adjColorTable[i][j] - adjColorTable[i][ solution[i] ];
                    //delta = *( *( adjColorTable + i) +  j )  -  *( *( adjColorTable + i) +  solution[i] ) ;

                    if ( tabuTable[i][j] > iterTimes) {
                        if (delta < tabuBest[2]) {
                            tabuBest[0] = i;
                            tabuBest[1] = j;
                            tabuBest[2] = delta;
                            //cout << "looking for best move ..."<<i << " "<<j<<endl;
                        }
                    } else {
                        if (delta < nonTabuBest[2]) {
                            nonTabuBest[0] = i;
                            nonTabuBest[1] = j;
                            nonTabuBest[2] = delta;
                            //cout << "looking for best move ...nana..."<<i << " "<<j<<endl;

                        }
                    }
                }
            }
        }
    }
    //cout << "done finding best move" << endl;

    /*** make the best move ***/
////////////////////////////////啊喂 adjcolortable 木有更新啊啊啊啊
    if ( (target+ tabuBest[2] < targetBest) && ( tabuBest[2] < nonTabuBest[2] ) ){
        //满足特赦条件
        nonTabuBest[0] = tabuBest[0];
        nonTabuBest[1] = tabuBest[1];
        nonTabuBest[2] = tabuBest[2];
        //  当前最优的禁忌/非禁忌move的 节点号[0]  & new 颜色[1]  &delta
    }
	if (nonTabuBest[2] == INF)
	{
		cout << " all good moves are tabu ! \n!\n!\n!\n!\n!\n!\n!";
		exit(1);
	}
    /***  与修改的结点 相邻的all k个结点 adj[k] 的adjcolortable表项 要更新 √ ***/
    /***  tabutable 也要更新  ***/
    int adjPoint;
    for (int k = 0; k <adjLen[ nonTabuBest[0] ] ; ++k) {
        adjPoint = adj[ nonTabuBest[0] ][k] ;
        adjColorTable[ adjPoint ][ solution[ nonTabuBest[0] ] ] --;
        adjColorTable[ adjPoint ][  nonTabuBest[1] ] ++;
    }

    target +=  nonTabuBest[2];
    if (target < targetBest) targetBest = target ;
    //updateTabu( head,nonTabuBest[0], nonTabuBest[1],tabuTable );
    solution[nonTabuBest[0]] = nonTabuBest[1];
	freq[nonTabuBest[0]][nonTabuBest[1]] ++;
	freq[nonTabuBest[0]][colorNum] ++;
	//tabuTenure = target + rand() % 20 + iterTimes + colorNum * freq[nonTabuBest[0]][nonTabuBest[1]] / freq[nonTabuBest[0]][colorNum];
	tabuTenure = TABUTENURE;
	tabuTable[nonTabuBest[0]][nonTabuBest[1]] = tabuTenure;

}

int getTargetFunc(int** adj, int * adjLen, int * solution, int p ) {
    int target = 0 ;
    for (int i = 0; i < p; ++i) {
        for (int j = 0; j < adjLen[i]; ++j) {
            if ( solution[i] == solution[ *( *( adj+i)+j) ] ){
                //cout << i+1 << "\t" << j+1 << endl;
                 target ++ ;
            }
        }
    }
    //每个冲突算了两次
    return target/2;
}

void initAdjColorTable(int** adjColorTable,int ** adj,int * adjLen,int p ,int colorNum, int solution[]) {
    int point;
    int test=0;
    for (int i = 0; i < p; ++i) {
        for (int j = 0; j < colorNum ; ++j) {
            //*( *( adjColorTable + i) + j ) = 0;
            adjColorTable[i][j] = 0;
        }
        for (int k = 0; k <adjLen[i] ; ++k) {
           // point = *( *( adjColorTable + i) + k ) ;// adj[i][k];
            point = adj[i][k];
//            ( *( *( adjColorTable + i) + solution[ point ] ) )++;
             adjColorTable[i][ solution[ point ] ] ++;
        }
    }
}


//void initAdjacent( int* &adj[], int* adjLength, int p, int ** matrix ) {
//    for (int i = 0; i < p; ++i) {
//        adjLength[i] = 0;
//        for (int j = 0; j < p ; ++j) {
//            if (matrix[i][j]) {
//                adjLength[i] ++ ;
//            }
//        }
//    }
//    for (int i = 0; i < p; ++i) {
//        adj[i] = new int[adjLength[i] ] ;
//        int temp ;
//        temp = 0 ;
//        for (int j = 0; j < p ; ++j) {
//            if (matrix[i][j]) {
//                adj[i][temp] = j;
//                temp++;
//            }
//        }
//    }
//}
