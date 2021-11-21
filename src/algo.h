#pragma once

#include <algorithm>

#ifndef algo_h
#define algo_h

namespace algo
{
// CREATE ALL PERMUTATION OF EDGES' ORDER
std::vector<std::vector<std::vector<long int>>> edges_order_perm(std::vector<std::vector<long int>> edgesVec){
    long int edgesNo = edgesVec.size();
    long int totalComb = math_algo::factorial(edgesNo);
    std::cout << std::endl << "Total permutation: " << totalComb << std::endl;
    std::vector<std::vector<std::vector<long int>>> returnEdges(totalComb, std::vector<std::vector<long int>>(edgesNo, std::vector<long int>(2)));
    
    std::vector<long int> orderVec(edgesVec.size());
    for (int i = 0; i < orderVec.size(); i++) orderVec[i] = i;
    std::sort(orderVec.begin(), orderVec.end());

    for (int i = 0; i < orderVec.size(); i++) returnEdges[0][i] = edgesVec[orderVec[i]];

    int permIndex = 1;
    while (std::next_permutation(orderVec.begin(), orderVec.end())){
        for(int i = 0; i < orderVec.size(); i++){
            returnEdges[permIndex][i] = edgesVec[orderVec[i]];
        }
        permIndex++;
    }
    return returnEdges;
}
}
#endif