#include <fstream>
#include <iostream>
#include <ctime>
#include <memory.h>
#include "tabuSearch.h"
#include "readData.h"

#define MAX_ITER 100000000
#define OUT_FILE "out.csv"
//#define _FILEPATH "..\\GCP_instances\\DSJC125.1.col"  //5 done
#define _FILEPATH "..\\GCP_instances\\DSJC125.5.col"  //17 done
//#define _FILEPATH "..\\GCP_instances\\DSJC125.9.col"  //44, done
//#define _FILEPATH "..\\GCP_instances\\DSJC250.1.col"  //8 done
//#define _FILEPATH "..\\GCP_instances\\DSJC250.5.col"  //28 done 
//#define _FILEPATH "..\\GCP_instances\\DSJC250.9.col"  //72 done
//#define _FILEPATH "..\\GCP_instances\\DSJC500.1.col"  //12 ,only to 13
//#define _FILEPATH "..\\GCP_instances\\DSJC500.5.col"  //47, only to 50

using namespace std;

//void printTabu(int **tabuList,int tabuLen) {
//    for (int i = 0; i < tabuLen; ++i) {
//        cout<<tabuList[i][0] <<"\t" ;
//        cout<<tabuList[i][1]<<"\t" ;
//        cout<<tabuList[i][2]<<endl;
//    }
//}
//void printAdj(int** adj, int* adjLen, int p) {
//    for (int i = 0; i < p; ++i) {
//        cout << i << " :" << " ";
//        for (int j = 0; j < adjLen[i]; ++j) {
//            cout << adj[i][j] << " ";
//        }
//    }
//    cout << endl;
//}
//
//void printTabu(tabuList* head, int tabuTenure) {
//	tabuList* ptr = head;
//	cout << endl << tabuTenure << "tabuTenure" << endl;
//	for (int i = 0; i < tabuTenure; ++i) {
//		cout << ptr->tabuItem[0] << " " << ptr->tabuItem[1] << "\t";
//		ptr = ptr->next;
//	}
//}

void printAdjLen(int* adjLen, int p) {
	for (int i = 0; i < p; ++i) {
		cout << i << " " << adjLen[i] << "\t";
	}
	cout << endl;
}

int main(int argc, char *argv[]) {

	char *FILEPATH;
	if (argc != 2) {
		FILEPATH = _FILEPATH;
		cout << _FILEPATH << endl;
	} 
	else {
		FILEPATH = argv[1];
	}

	for (int k = 0; k < argc; ++k) {
		cout << "argv  " << argv[k] << endl;
	}

	srand((unsigned)time(NULL));

	int p, e; //p是点数 e是边数
	int target;//
	int* adjLength;
	adjLength = initAdjLength(FILEPATH, p, e);

	//printAdjLen(adjLength,p);

	int** adjacent;


	adjacent = initAdjacent(adjLength, p, FILEPATH);

	//printAdj(adjacent,adjLength,p);

	cout << "points: " << p << "  edges : " << e << endl;


	int colorNum;
	cout << "please input the number of colors : ";
	cin >> colorNum;

	clock_t start, finish;
	double totaltime;
	start = clock();


	int * solution;
	solution = new int[p];
	randomSolution(solution, p, colorNum);
	target = getTargetFunc(adjacent, adjLength, solution, p);
	int targetBest = target;
	cout << "initial target: " << target << endl;

	int **adjColorTable;

	adjColorTable = new int*[p];
	for (int j = 0; j < p; ++j) {
		adjColorTable[j] = new int[colorNum];
	}
	initAdjColorTable(adjColorTable, adjacent, adjLength, p, colorNum, solution);
	cout << "done initializing adjColorTable..." << endl;

	int tabuTenure;//tabuPtr = 0;
	int **tabuTable;
	tabuTable = new int*[p];
	for (int j = 0; j < p; ++j) {
		tabuTable[j] = new int[colorNum];
		for (int i = 0; i < colorNum; ++i) {
			tabuTable[j][i] = 0;
		}
	}

	int **freq;
	freq = new int*[p];
	for (size_t i = 0; i < p; i++)
	{
		freq[i] = new int[colorNum + 1];
		for (size_t j = 0; j < colorNum ; j++)
		{
			freq[i][j] = 1; //初始化为1 防止出现分母为0
		}
		freq[i][colorNum] = colorNum;
	}

	//tabuList **head;
	//head = new tabuList*[1];

	tabuTenure = target + rand() % 10;
	//cout << "init tabu..." << endl;
	//initTabu(head, tabuTenure);
	//cout << "done init tabu" << endl;

	/*** 以上 完成各项初始化 ***/

	int iterTimes = 0;
	while (target > 0) {
		iterTimes++;
		//int testTabuUpdate = 10;
		//cout << "iter: " << iterTimes << " target " << target << endl;
		move(adjColorTable, tabuTable, solution, p, colorNum, target, targetBest,  adjacent, adjLength,iterTimes , tabuTenure,freq);
		/***  dynamically renew TabuList ***/    //if (iterTimes % testTabuUpdate == 0 ) 
		
		//tabuTenure = target + 10 + rand() % 10 + iterTimes ;	//+10 的话125.1要10w次 0.

		if (iterTimes % 30000 == 0) 
		{
			cout << "iteration: " << iterTimes << endl;
			//printTabu(*head, tabuTenure);
			cout << endl << tabuTenure - iterTimes << " (tabuTenure - iterTimes) " << target << " target " << endl;

		}
		if (iterTimes > MAX_ITER) {
			cout << "test" << endl;
			break;
		}
		//if (target != getTargetFunc(matrix, solution, p)) cout <<"a\taaaaa\taaaa "<< target <<" "<<getTargetFunc(matrix, solution, p) << endl;
	}

	cout << "iteration: " << iterTimes << endl;
	for (int i = 0; i < p; ++i) {
		cout << i + 1 << ": " << solution[i] << "\t";
	}


	finish = clock();
	totaltime = (double)(finish - start) / CLOCKS_PER_SEC;
	cout << "\ntotal time : " << totaltime << "seconds" << endl;

	if (target) {
		cout << "failed..." << target << "  " << getTargetFunc(adjacent, adjLength, solution, p) << "best found: " << targetBest ;
	}
	else {
		cout << "success" << target << "  " << getTargetFunc(adjacent, adjLength, solution, p);
	}
	getchar();

	ofstream outfile;
	outfile.open(OUT_FILE, ios::app);
	if (! outfile.is_open())
	{
		cout << "error open " << OUT_FILE << endl;
		getchar();
	}
	//outfile.seekp(ios::end, 0);
	//outfile << "file,vertex,edge,color,iterations,durations" << endl;
	else {
		if (!target) outfile << _FILEPATH << "," << p << "," << e << "," << colorNum << "," << iterTimes << "," << totaltime << ", ," << TABUTENURE_STR << endl;
		else  outfile << _FILEPATH << "," << p << "," << e << "," << colorNum << "," << "FAIL" << "," << "best="<<targetBest << ", ," << TABUTENURE_STR << endl;
		outfile.flush();
	}
	outfile.close();
	getchar();

	return 0;
}
