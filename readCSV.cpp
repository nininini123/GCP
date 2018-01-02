//
// Created by 30838 on 2017/12/28.
//
#include <iostream>
#include <fstream>
#include <string>
using namespace std;


int* initAdjLength(char *filepath, int &p, int &e) {
    ifstream infile;
    int *adjLength;

    infile.open(filepath) ;
    if (  !infile.is_open() ) {
        cout << "error open file " << filepath << endl;
        return NULL;
    }
    string value;
    char c = 0;
    infile >> c ;
    while ( c != 'p' )
    {
        getline ( infile, value, '\n' ); // read a string until “\n”:       http://www.cplusplus.com/reference/string/getline/
        infile >> c ;
    }
    char *temp ;
    temp = new char[5];
    infile >> temp >> p >> e ;
    delete [] temp;

    /***
     * 初始化邻接表长度数组
     */
    adjLength = new int[p];
    for (int j = 0; j < p; ++j) {
        adjLength[j] = 0;
    }

    int a,b;
    for (int i = 0; i < e; ++i) {
        infile >> c;
        if (c == 'e' ) {
            infile >> a >> b ;
            adjLength[a-1]++;
            adjLength[b-1]++;
        }
        else {
            cout << "error reading file" << filepath <<endl;
            break;
        }
    }
    infile.close();
    return adjLength;
}


int** initAdjacent( int* adjLength, int p, char* filepath) {
    ifstream infile;
    int **adj;
    adj = new int*[p];

    infile.open(filepath) ;
    if (  !infile.is_open() ) {
        cout << "error open file " << filepath << endl;
        return NULL;
    }
    string value;
    char c = 0;
    infile >> c ;
    while ( c != 'p' )
    {
        getline ( infile, value, '\n' ); // read a string until “\n”:       http://www.cplusplus.com/reference/string/getline/
        infile >> c ;
    }
    char *temp ;
    int _e,_p;
    temp = new char[5];
    infile >> temp >> _p >> _e ;
    if (p != _p ) {
        cout << "error waaaaaaaaaaaaaaaaaa kule T-T" << endl;
    }
    delete[] temp;


    /***
     * 初始化邻接表
     */
    for (int j = 0; j < p; ++j) {
        adj[j] = new int[ adjLength[j] ] ;
    }
    cout << endl;


    int a,b;
    int *counter;
    counter = new int[p];
    for (int k = 0; k < p; ++k) {
        counter[k] = 0;
    }

    for (int i = 0; i < _e; ++i) {
        infile >> c;

        if (c == 'e' ) {
            infile >> a >> b ;
//            if ( counter[a-1] == adjLength[a-1] ) {
//                cout << "aaaaaaaaaaaaa out of bound...";
//                return NULL;
//            }
//            if ( counter[b-1] == adjLength[b-1] ) {
//                cout << "bbbbbbbbbbbbbbbbbb out of bound...";
//                cout << endl << b-1 << " " << adjLength[b-1] << " leaking..." << endl;
//                return NULL;
//            }
//            *( *( adj+ a-1) + counter[a-1] ) = b-1;
//            *( *( adj+ b-1) + counter[b-1] ) = a-1;
            adj[a-1][ counter[a-1] ] = b-1;
            adj[b-1][ counter[b-1] ] = a-1;
            counter[a-1] ++;
            counter[b-1] ++;

        }
        else {
            cout << "error reading file" << filepath <<endl;
            break;
        }
    }

    ////////////////////////////////////奇怪了  不delete就行了
    delete[] counter;

    infile.close();
    return adj;
}
