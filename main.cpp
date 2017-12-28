#include <iostream>

using namespace std;

#define IN_FILE "D:\\miscellaneous\\MyProgram\\java\\smartLab\\GCP_instances\\DSJC125.1.col"

int** initMatrix(char * filepath, int &p, int &e) ;
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
    matrix = initMatrix(argv[1], p, e);

    cout << p << "  " << e  << endl ;
//    for (int j = 0; j < p; ++j) {
//        cout << j << ":\t";
//        for (int i = 0; i < p; ++i) {
//            cout<<matrix[j][i]<<" ";
//        }
//        cout<<endl;
//    }

    int n;
    cout << "please input the number of colors : ";
    cin >> n;



    return 0;
}
