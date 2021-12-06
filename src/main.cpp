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
#include "yen.h"
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
    std::cout << std::endl;
    std::cout << "---------- FIND PATH WITH MANDATORY EDGES ----------" << std::endl;

    ds::graph inputGraph = io_func::input_graph();

    std::vector<std::vector<long int>> mandEdges = io_func::input_mand_edges();

    long int source, finish;
    std::cout << "input source and finish node: ";
    std::cin >> source >> finish;
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
    std::cout << std::endl;
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

void test_yen(){
    std::cout << "-------- KTH SHORTEST PATH --------" << std::endl;

    ds::graph inputGraph = io_func::input_graph();
    
    long int source, finish;
    std::cout << "input source and finish node: ";
    std::cin >> source >> finish;

    long int K;
    std::cout << "input K: ";
    std::cin >> K;

    yen::yenObject yen_object(inputGraph);
    yen_object.makePath(source, finish, K);

    std::vector<ds::path> my_path_list = yen_object.getPathList();

    std::cout << "Done finding path" << std::endl;

    for (int i = 0; i < my_path_list.size(); i++){
        my_path_list[i].print();
        std::cout << std::endl;
    }

}

int main(){
    int choice;
    std::cout << "------- PATH FINDING PROGRAM -------" << std::endl << std::endl;
    std::cout << "################################" << std::endl;
    std::cout << "# Type 0 for mandatory edges   #" << std::endl;
    std::cout << "# Type 1 for kth shortest path #" << std::endl;
    std::cout << "################################" << std::endl << std::endl;
    std::cout << "Your choice: ";
    std::cin >> choice;

    while(choice == 1 || choice == 0){
        if (choice == 0)
            test_mand_edge();
        if (choice == 1)
            test_yen();

        std::cout << std::endl;
        std::cout << "Done finding path, type in your choice again:" << std::endl;

        std::cout << "Your choice: ";
        std::cin >> choice;
    }

    std::cout << std::endl;
    std::cout << "EXITING PROGRAM..." << std::endl;

    return 0;
}
