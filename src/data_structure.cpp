#include "data_structure.h"
#include <algorithm>
#include <cstdio>
#include <string.h>
#include <sstream>

using namespace ds;

// Making graph

graph::graph(std::vector<std::vector<long int>> inputMat, long int inputRow){
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

    // INITIATE VECTOR
    std::vector<std::vector<long int>> graphMat(nodeNo, std::vector<long int>(nodeNo, -1));
    for (int i = 0, j = 0; (i < nodeNo) && (j < nodeNo); i++, j++){
        graphMat[i][j] = 0;
    }
    // ASSIGNING WEIGHT VALUE TO VECTOR
    for (int i = 0; i < inputRow; i++){
        if (inputMat[i][0] == inputMat[i][1]){
            graphMat[inputMat[i][0]-1][inputMat[i][1]-1] = 0;
            graphMat[inputMat[i][1]-1][inputMat[i][0]-1] = 0;
        }
        else{
            graphMat[inputMat[i][0]-1][inputMat[i][1]-1] = inputMat[i][2];
            graphMat[inputMat[i][1]-1][inputMat[i][0]-1] = inputMat[i][2];
        }
    }
    matrix = graphMat;
    graphMat.clear();
    validGraph = true;
}

// destructor
graph::~graph(){
}

long int graph::maximum_node(){
    return graph::matrix.size();
}

// return distance from node to node base on the graph
long int graph::dist(long int a, long int b){
    return matrix[a-1][b-1];
}

// print graph
void graph::print(){
    nodeNo = matrix.size();

    int width = 5;
    std::cout << std::setw(width+3);

    for (int i = 1; i <= nodeNo; i++){
        std::cout << i;
        if (i < nodeNo){
            int thisLen = std::to_string(i+1).length();
            for (int k = 0; k < width - thisLen; k++)
                std::cout <<' ';
        }
    }
    for(int i = 1; i <= width/2; i++)
        std::cout << std::endl;

    for (int i = 0; i < nodeNo; i++){
        int thisLen = std::to_string(i+1).length();
        std::cout << i+1 << std::setw(width+2-thisLen+1);
        for(int j = 0; j < nodeNo; j++){
            std::cout << matrix[i][j];
            if (j < nodeNo-1){
                int nextLen = std::to_string(matrix[i][j+1]).length();
                for (int k = 0; k < width - nextLen; k++){
                    std::cout << ' ';
                }
            }
        }    
        std::cout << std::endl;    
    }
}

void graph::copy (graph &inputGraph){
    if (inputGraph.matrix.size() > 0){
        for (int i = 0; i < inputGraph.matrix.size(); i++){
            inputGraph.matrix[i].clear();
        }
    }
        inputGraph.matrix = matrix;
        inputGraph.validGraph = validGraph;
        inputGraph.nodeNo = nodeNo;
}

bool graph::delete_edge(long int node_1, long int node_2){
    bool validation = false;
    long int graphSize = matrix.size();
    if (std::max(node_1 - 1, node_2 - 1)){
        validation = true;
        matrix[node_1 - 1][node_2 - 1] = -1;
        matrix[node_2 - 1][node_1 - 1] = -1;
    }
    return validation;
}

//----------- GRAPH_LINKED_LIST -----------
graph_linked_list::graph_linked_list(graph inputGraph, std::vector<std::vector<long int>> edgesVec){
    inputGraph.copy(generatedGraph);
    
    // std::cout << "Done copy graph" << std::endl;

    decodeValue = inputGraph.maximum_node();
    long int edgesNo = edgesVec.size();
    
    // std::cout << "Done max node" << std::endl;

    for (int i = 0; i < edgesNo; i++){
        long int node_1 = edgesVec[i][0]-1;
        long int node_2 = edgesVec[i][1]-1;

        // std::cout << "Done node assign" << std::endl;

        // Add row vector
        for (int i2 = 0; i2 < decodeValue; i2++){
            std::vector<long int> tempVec(decodeValue*(i+2), -1);
            generatedGraph.matrix.push_back(tempVec);
            tempVec.clear();
        }

        // Add new vector

        for (int i2 = 0; i2 < generatedGraph.maximum_node(); i2++){
            long int current_size = generatedGraph.matrix[i2].size();
            if (current_size < decodeValue*(i+2)){
                while (current_size < decodeValue * (i+2)){
                    generatedGraph.matrix[i2].push_back(-1);
                    current_size = generatedGraph.matrix[i2].size();
                }
            }
            // printf("now done [%d] \n", i2);
            // printf("Size of graph[%d]: %d \n", i2, generatedGraph.matrix[i2].size());
        }

        // std::cout << "Done first add vector" << std::endl;

        // ------ Configure the big graph ------
        
        // Make new graph has default value
        for (int i2 = 0; i2 < decodeValue; i2++){
            for (int j = 0; j < decodeValue; j++){
                if (i2 == j)
                    generatedGraph.matrix[i2 + decodeValue*(i+1)][j + decodeValue*(i+1)] = 0;
                else
                    generatedGraph.matrix[i2 + decodeValue*(i+1)][j + decodeValue*(i+1)] = inputGraph.dist(i2+1, j+1);    
            }
        }

        // Link old graph to new graph
        generatedGraph.matrix[node_1][node_2 + decodeValue*(i+1)] = inputGraph.matrix[node_1][node_2];
        generatedGraph.matrix[node_2][node_1 + decodeValue*(i+1)] = inputGraph.matrix[node_2][node_1];

        // Delete edge in new graph
        
        printf("prev edge need to be delete: %d -> %d \n", (node_1+1)+decodeValue*(i+1), (node_2+1)+decodeValue*(i+1));
        generatedGraph.delete_edge((node_1+1)+decodeValue*(i+1), (node_2+1)+decodeValue*(i+1));
    }
}

graph graph_linked_list::main_graph(){
    return generatedGraph;
}
