#pragma once

// #include <iostream>
// #include <iomanip>
// #include <vector>

// namespace io_func
// {
#ifndef io_func_h
#define io_func_h

namespace io_func
{
ds::graph input_graph(){
    std::cout << "number of row: ";
    long int n;
    std::cin >> n;
    
    std::cout << "Type in nodes and edges: " << std::endl;
    std::vector<std::vector<long int>> inputMat(n, std::vector<long int>(3, -1));
    for (int i = 0; i < n; i++){
        for (int j = 0; j < 3; j++){
            std::cin >> inputMat[i][j];
        }
    }
    ds::graph myGraph(inputMat, n);
    return myGraph;
}

std::vector<std::vector<long int>> input_mand_edges(){
    std::cout << "number of mandatory edges: ";
    int m;
    std::cin >> m;

    std::cout << "Type in mandatory edges: " << std::endl;
    std::vector<std::vector<long int>> inputEdges(m, std::vector<long int>(2));
    for (int i = 0; i < m; i++){
        std::cin >> inputEdges[i][0];
        std::cin >> inputEdges[i][1];
    }
    return inputEdges;
}

void display_edges(std::vector<std::vector<long int>> inputEdges){
    long int edgesNo = inputEdges.size();
    for (int i = 0; i < edgesNo; i++)
        printf("%d --> %d | ", inputEdges[i][0], inputEdges[i][1]);
}

}

#endif