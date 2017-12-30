//
// Created by 30838 on 2017/12/28.
//

#include <iostream>
#include <random>
#include <Windows.h>
#define INF 10000

using namespace std;

void randomSolution(int* solution, int length, int colorNum) {
    random_device rd ;
    for (int i = 0; i < length ; ++i) {
        solution[i] = 1;///////////////////////////////////////////rd() % colorNum;
    }
}

/***
 *
 * @param solution
 * @param length    结点数
 * @param tabuList
 * @param tabuLen
 * @param targetBest 历史最优的target
 * @return target 当前solution对应的冲突数之和
 */
//void move( int** matrix,int * solution, int length, int tabuList[][3], int tabuLen,int &tabuPtr , int colorNum ,int &target, int &targetBest ) {
void move( int** matrix,int * solution, int length, int **tabuList, int tabuLen,int &tabuPtr , int colorNum ,int &target, int &targetBest ) {
    int delta =0,newColor;
    int tabuBest[4] ={0,0,0,INF};
    int nonTabuBest[4] = {0,0,0,INF} ; //记录 当前最优的禁忌/非禁忌move的 节点号 & old颜色 & new 颜色 &delta
    for (int i = 0; i < length ; ++i) {
        //第 i个结点
        //换成颜色j
        //与k是邻居
        for (int j = 0; j < colorNum ; ++j) {
            if ( solution[i] != j ) {
                //求delta
                delta = 0 ;
                for (int k = 0; k < length; ++k) {
                    if (matrix[i][k] == 1) {
                        if (solution[k] == j) {
                            delta++;
                        }
                        if (solution[k] == solution[i]) {
                            delta--;
                        }
                    }
                }

                short tabu = 0 ;
                for (int l = 0; l <tabuLen ; ++l) {
                    if ( (tabuList[l][0]== i && tabuList[l][2]== solution[i] && tabuList[l][1 ]== j )
                            || (tabuList[l][0]== i && tabuList[l][1]== solution[i] && tabuList[l][2 ]== j )  ) {
                        tabu = 1 ;
                        break;
                    }
                }
                if (tabu) {
                    if ( delta < tabuBest[3]) {
                        tabuBest[0] = i;
                        tabuBest[1] = solution[i];
                        tabuBest[2] = j;
                        tabuBest[3] = delta ;
                        //cout << "tttttTT.."<<i << " "<<j<<endl;
                    }
                } else {
                    if ( delta < nonTabuBest[3]) {
                        nonTabuBest[0] = i;
                        nonTabuBest[1] = solution[i];
                        nonTabuBest[2] = j;
                        nonTabuBest[3] = delta ;
                    }
                }
            }
        }
    }
    if ( (target+ tabuBest[3] < targetBest) ) {///////// && ( tabuBest[3] < nonTabuBest[3] ) ){
//    if ( (target+ tabuBest[3] < targetBest) && ( tabuBest[3] < nonTabuBest[3] ) ){
        //满足特赦条件
        target = targetBest = target +  tabuBest[3];
        tabuList[tabuPtr][0] = tabuBest[0];
        tabuList[tabuPtr][1] = tabuBest[1];
        tabuList[tabuPtr][2] = tabuBest[2];
        cout << "emmm \t\t\t" << tabuBest[0]<<" "<< tabuBest[1]<< " "<< tabuBest[2]<< " "<< tabuBest[3]<< endl;
    }else {
        target = target + nonTabuBest[3];
        if (target < targetBest) targetBest = target ;
        tabuList[tabuPtr][0] = nonTabuBest[0];
        tabuList[tabuPtr][1] = nonTabuBest[1];
        tabuList[tabuPtr][2] = nonTabuBest[2];
        //cout << "ehhhh" <<" "<< nonTabuBest[0]<< " "<< nonTabuBest[1]<< " "<< nonTabuBest[2]<<" "<<  nonTabuBest[3]<< endl;

    }
    if (solution[ tabuList[tabuPtr][0] ] != tabuList[tabuPtr][1] ) cout << "ERROR!!!!!!!!!!!!!!!!!!" << endl;
    solution[ tabuList[tabuPtr][0] ] = tabuList[tabuPtr][2];
    tabuPtr ++;
    if (tabuPtr == tabuLen) tabuPtr =0;
}

int getTargetFunc(int** matrix, int * solution, int length) {
    int ret = 0 ;
    for (int i = 0; i < length; ++i) {
        for (int j = 0; j < i; ++j) {
            if (matrix[i][j] == 1 ) {
                if ( solution[i] == solution[j] ){
                    //cout << i+1 << "\t" << j+1 << endl;
                    ret ++;
                }
            }
        }
    }
    Sleep(3000);
    return ret;
}