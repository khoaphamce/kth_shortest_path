#include <iostream>
#include <iomanip>
#include "data_structure.h"
#include "algo.h"
#include "io_func.h"

int main(){
    // std::cout << "number of row: ";
    // int n;
    // std::cin >> n;
    
    // std::cout << "Type in nodes and edges: " << std::endl;
    // std::vector<std::vector<long int>> inputMat(n, std::vector<long int>(3, -1));
    // for (int i = 0; i < n; i++){
    //     for (int j = 0; j < 3; j++){
    //         std::cin >> inputMat[i][j];
    //     }
    // }

    std::cout << "number mandatory edges: ";
    int m;
    std::cin >> m;

    std::cout << "Type in mandatory edges: " << std::endl;
    std::vector<std::vector<long int>> inputEdges(m, std::vector<long int>(2));
    for (int i = 0; i < m; i++){
        std::cin >> inputEdges[i][0];
        std::cin >> inputEdges[i][1];
    }

    // data_structure_h::graph myGraph(inputMat, n);
    // myGraph.print();
    std::vector<std::vector<std::vector<long int>>> perm_of_edges;
    perm_of_edges = algo_h::edges_order_perm(inputEdges); 
    for (int i = 0; i < perm_of_edges.size(); i++){
        std::cout << std::endl << std::endl;
        io_func_h::display_edges(perm_of_edges[i]);
    }

    std::cout << std::endl;

    return 0;
}