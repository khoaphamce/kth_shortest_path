#include <iostream>
#include <iomanip>
#include <cstdio>
#include <math.h>
#include "math_algo.h"
#include "data_structure.h"
#include "algo.h"
#include "io_func.h"
#include <algorithm>


int main(){
    ds::graph inputGraph = io_func_h::input_graph();
    std::cout << "Graph: " << std::endl;

    inputGraph.print();

    std::vector<std::vector<long int>> mandEdges = io_func_h::input_mand_edges();
    std::vector<std::vector<std::vector<long int>>> perm_mandEdges = algo_h::edges_order_perm(mandEdges);
    // std::cout << std::endl << "Permutation of edges:" << std::endl << std::endl;
    // for(int i = 0; i < perm_mandEdges.size(); i++){
    //     io_func_h_h::display_edges(perm_mandEdges[i]);
    //     std::cout << std::endl;
    // }

    std::cout << "Edges require: " << std::endl;
    io_func_h::display_edges(perm_mandEdges[0]);
    std::cout << std::endl;

    ds::graph_linked_list bigGraphList(inputGraph, perm_mandEdges[0]);

    ds::graph outGraph = bigGraphList.main_graph();

    outGraph.print();

    std::cout << std::endl;

    return 0;
}