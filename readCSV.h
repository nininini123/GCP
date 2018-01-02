//
// Created by 30838 on 2017/12/29.
//

#ifndef GRAPHCOLOR_READCSV_H
#define GRAPHCOLOR_READCSV_H

int* initAdjLength(char *filepath, int &p, int &e) ;
//void initAdjacent(int* &adj[], int* adjLength, int p, char* filepath) ;
int** initAdjacent( int* adjLength, int p, char* filepath) ;
#endif //GRAPHCOLOR_READCSV_H
