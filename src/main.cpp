#include <iostream>
#include <iomanip>
#include <cstdio>
#include <math.h>
#include "math_algo.h"
#include "data_structure.h"
#include "algo.h"
#include "io_func.h"
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

int main(){
    test_func();
    for (int i = 0; i < 2000000000; i++)
        printf("Bruh %d \n", i);
    
    return 0;
}