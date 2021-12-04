#include <iostream>
#include <iomanip>
#include <cstdio>
#include <math.h>
#include "math_algo.h"
#include "data_structure.h"
#include "algo.h"
#include "io_func.h"
#include "dijkstra.h"
#include "mandatory_edge.h"
#include <algorithm>


// void test_func(){
//     ds::graph inputGraph = io_func::input_graph();

//     std::vector<std::vector<long int>> mandEdges = io_func::input_mand_edges();
//     std::vector<std::vector<std::vector<long int>>> perm_mandEdges = algo::edges_order_perm(mandEdges);
    
//     std::cout << std::endl;

//     ds::graph_linked_list bigGraphList(inputGraph, perm_mandEdges[0]);

//     ds::graph outGraph = bigGraphList.main_graph();

//     std::cout << "Done making graph" << std::endl;

//     std::cout << std::endl;
// }

void test_mand_edge(){
    ds::graph inputGraph = io_func::input_graph();

    std::vector<std::vector<long int>> mandEdges = io_func::input_mand_edges();

    long int source, finish;
    std::cout << "input source and finish node: ";
    std::cin >> source >> finish;

    // mand_edge::mand_edge_path * mandObject = new mand_edge::mand_edge_path(
    //                                                 inputGraph, 
    //                                                 mandEdges, 
    //                                                 source, 
    //                                                 finish);
    mand_edge::mand_edge_path mandObject(
                            inputGraph, 
                            mandEdges, 
                            source, 
                            finish);

    ds::path myPath = mandObject.path;

    myPath.print();
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
    //inoutPath();
    // for (int i = 0; i < 2000000000; i++)
    //     printf("Bruh %d \n", i);

    // long int n;
    // long int s = 1, e = 2;
    // cin >> n;
    // vector<vector<long int> > matrix = vector<vector<long int> >(n, vector<long int>(3));
    // for(long int i = 0; i < n; i++) {
    //     for(long int j = 0; j < 3; j++) {
    //         cin >> matrix[i][j];
    //     }
    // }
    // ds::graph graph(matrix, n);
    // dijkstra::Dijkstra(graph, s);
    // cout << "The distance between " << s << " and " << e << ": " <<dijkstra::dist[e] << endl;
    // dijkstra::makePath(e);
    // cout << "The path from " << s << " to " << e << ": ";
    // dijkstra::dPath->print();
    test_mand_edge();
    return 0;
}
