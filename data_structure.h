#pragma once

#include <vector>
#include <iostream>
#include <iomanip>
#include <limits.h>


#ifndef data_structure_h
#define data_structure_h

// const long int MAX_LONG_INT = std::LONG_MAX;

// Declaring classes
class graph{
    public:
        graph(long int** inputMat, long int inputRow);
        ~graph();
    
        long int dist(long int a, long int b);
        void print();

    private:
        bool validGraph;
        long int nodeNo;
        long int **matrix; 
};

// Declaring classes' method

// Making graph
graph::graph(long int** inputMat, long int inputRow){
    int maxNode = 0;
    for (int i = 0; i < inputRow; i++){
        for (int j = 0; j < 3; j++){
            if (inputMat[i][j] <= 0){
                validGraph = false;
                return;
            }
            if ((inputMat[i][j] > maxNode) && j < 2) maxNode = inputMat[i][j];
        }
    }
    nodeNo = maxNode;
    long int **graphMat = new long int * [maxNode];
    for (int i = 0; i < maxNode; i++){
        graphMat[i] = new long int [maxNode];
        for (int j = 0; j < maxNode; j++){
            graphMat[i][j] = 0;
        }
    }
    for (int i = 0; i < inputRow; i++){
        if (inputMat[i][0] == inputMat[i][1]) graphMat[inputMat[i][0]-1][inputMat[i][1]-1] = 0;
        else graphMat[inputMat[i][0]-1][inputMat[i][1]-1] = inputMat[i][2];
    }
    matrix = graphMat;
    validGraph = true;
}

// destructor
graph::~graph(){
}

// return distance from node to node base on the graph
long int graph::dist(long int a, long int b){
    return matrix[a-1][b-1];
}

// print graph
void graph::print(){
    int width = 5;
    std::cout << std::setw(width+1);

    for (int i = 1; i <= nodeNo; i++){
        std::cout << i;
        if (i < nodeNo) std::cout << std::setw(width);
    }
    for(int i = 1; i <= width/2; i++)
        std::cout << std::endl;

    for (int i = 0; i < nodeNo; i++){
        std::cout << i+1 << std::setw(width);
        for(int j = 0; j < nodeNo; j++){
            std::cout << matrix[i][j];
            if (j < nodeNo-1){
                if (matrix[i][j] < 0) std::cout << std::setw(width-1);
                else std::cout << std::setw(width);
            }
        }    
        std::cout << std::endl;    
    }
}

#endif