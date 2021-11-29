#include <iostream>
#include <iomanip>
#include <cstdio>
#include <math.h>
#include "math_algo.h"
#include "data_structure.h"
#include "algo.h"
#include "io_func.h"
#include "dijkstra.h"
#include <algorithm>

void test_func(){
    ds::graph inputGraph = io_func::input_graph();

    std::vector<std::vector<long int>> mandEdges = io_func::input_mand_edges();
    std::vector<std::vector<std::vector<long int>>> perm_mandEdges = algo::edges_order_perm(mandEdges);
    
    std::cout << std::endl;

    ds::graph_linked_list bigGraphList(inputGraph, perm_mandEdges[0]);

    ds::graph outGraph = bigGraphList.main_graph();

    std::cout << "Done making graph" << std::endl;

    std::cout << std::endl;
}

void inoutPath(){
    int n;
    std::vector<long int> inputNodes;
    std::cout << "number of nodes: ";
    std::cin >> n;

    for (int i = 0; i < n; i++){
        long int temp;
        std::cin >> temp;
        inputNodes.push_back(temp);
    }
    std::cout << std::endl;
    ds::path inputPath(inputNodes);
    std::cout << "Path that is input:" << std::endl;
    inputPath.print();
    std::cout << std::endl;
}

int main(){
    inoutPath();
    // for (int i = 0; i < 2000000000; i++)
    //     printf("Bruh %d \n", i);
    
    return 0;
}