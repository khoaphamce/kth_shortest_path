#include <iostream>
#include <iomanip>
#include "data_structure.h"

int main(){
    int n;
    std::cin >> n;
    
    long int **inputMat = new long int * [n];
    for (int i = 0; i < n; i++){
        inputMat[i] = new long int [3];
    }

    for (int i = 0; i < n; i++){
        for (int j = 0; j < 3; j++){
            std::cin >> inputMat[i][j];
        }
    }

    data_structure_h::graph myGraph(inputMat, n);

    myGraph.print();
}