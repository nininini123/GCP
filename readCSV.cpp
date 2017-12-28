//
// Created by 30838 on 2017/12/28.
//
#include <iostream>
#include <fstream>
using namespace std;


int** initMatrix(char * filepath, int &p, int &e) {
    ifstream infile;

    infile.open(filepath);
    string value;
    char c = 0;
    infile >> c ;
    while ( c != 'p' )
    {
        getline ( infile, value, '\n' ); // read a string until “p edge”:       http://www.cplusplus.com/reference/string/getline/
        //cout << string( value, 0, value.length() )<<endl ;
        infile >> c ;
    }
    char *temp ;
    temp = new char[5];
    infile >> temp >> p >> e ;
    delete temp;

    /***
     * 初始化邻接矩阵
     */
    int ** matrix ;
    matrix = new int*[p];
    for (int j = 0; j < p; ++j) {
        matrix[j] = new int[p];
        for (int i = 0; i < p; ++i) {
            matrix[j][i] = 0;
        }
    }

    int a,b;
    for (int i = 0; i < e; ++i) {
        infile >> c;
        if (c == 'e' ) {
            infile >> a >> b ;
            matrix[a-1][b-1] = 1;
        }
        else {
            cout << "error reading file" << filepath <<endl;
            break;
        }
    }
    infile.close();
    return matrix;
}