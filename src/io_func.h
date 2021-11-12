#pragma once

#include <iostream>
#include <iomanip>
#include <vector>

#ifndef io_func_h
#define io_func_h

void display_edges(std::vector<std::vector<long int>> inputEdges){
    long int edgesNo = inputEdges.size();
    for (int i = 0; i < edgesNo; i++)
        printf("%d --> %d | ", inputEdges[i][0], inputEdges[i][1]);
}

#endif