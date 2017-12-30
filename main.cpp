#include <cmath>
#include <iostream>
#include <limits>
#include "tabuSearch.h"
#include "readCSV.h"

using namespace std;

#define OUT_FILE "out.csv"

void printTabu(int **tabuList,int tabuLen) {
    for (int i = 0; i < tabuLen; ++i) {
        cout<<tabuList[i][0] <<"\t" ;
        cout<<tabuList[i][1]<<"\t" ;
        cout<<tabuList[i][2]<<endl;
    }
}

int main(int argc, char *argv[] ) {

    if (argc != 2) {
        cout << "please input the filename as the parameter";
        return 0;
    }

    for (int k = 0; k < argc; ++k) {
        cout<< "argv  " << argv[k] <<endl;
    }

    int** matrix;
    int p,e; //p是点数 e是边数
    int target ;//= (numeric_limits<int>::max)();
    //cout << target << endl;
    matrix = initMatrix(argv[1], p, e);
    //////////////////////////////////////test
//    if (matrix == NULL)
//        return 1;
//    for (int l = 0; l < p ; ++l) {
//        cout << p%10 ;
//    }
//    cout<<endl;
//
//    for (int l = 0; l < p ; ++l) {
//        for (int i = 0; i < p; ++i) {
//            cout << matrix[l][i];
//        }
//        cout<<endl;
//    }
    ///////////////////////////////////endoftest
    cout << "points: "<< p << "  edges : " << e  << endl ;


    int colorNum;
    cout << "please input the number of colors : ";
    cin >> colorNum;

    int * solution ,*currentBestSolution;
    solution = new int[p];
    currentBestSolution = new int[p];
    randomSolution(solution,p,colorNum);
    target = getTargetFunc(matrix, solution, p);
    int targetBest = target;
    cout << "initial target: " << target << endl;

    int ** tabuList ;
    int tabuLen ,tabuPtr = 0;
    tabuLen = (int) sqrt( (colorNum - 1) * p);
    tabuList = new int*[tabuLen];
    for (int j = 0; j < tabuLen; ++j) {
        tabuList[j] = new int[3];
        tabuList[j][0] = 0;
        tabuList[j][1] = 0;
        tabuList[j][2] = 0;
    }
    cout << "length of tabu length is " << tabuLen << endl ;

    int iterTimes = 0;
    while (target > 0) {
        iterTimes ++ ;
//        target =
        move( matrix, solution, p,tabuList, tabuLen, tabuPtr , colorNum ,target, targetBest ) ;
        if (iterTimes % 10000 == 0) {
            cout << "iteration: " << iterTimes << endl;
            printTabu(tabuList, tabuLen);
        }
        //if (target != getTargetFunc(matrix, solution, p)) cout <<"a\taaaaa\taaaa "<< target <<" "<<getTargetFunc(matrix, solution, p) << endl;
    }

    cout << "iteration: " <<iterTimes <<endl;
    for (int i = 0; i < p; ++i) {
       cout <<i+1 <<": " <<solution[i] <<"\t";
    }

    return 0;
}
