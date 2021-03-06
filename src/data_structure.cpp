#include "data_structure.h"
#include <algorithm>
#include <cstdio>
#include <string.h>
#include <sstream>

using namespace ds;

//----------------------------- GRAPH -----------------------------
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
    if (matrix.size() > 0)
        matrix.clear();
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

void graph::clear(){
    if (matrix.size() > 0)
        matrix.clear();
}

std::vector<std::vector<long int> > graph::graph_matrix() {
    return this->matrix;
}

void graph::delete_node(long int node){
    for (int i = 0; i < matrix.size(); i++){
        matrix[i][node-1] = -1;
        matrix[node-1][i] = -1;
        matrix[node-1][node-1] = -1;
    }
}


//---------------------- GRAPH_LINKED_LIST ----------------------

graph_linked_list::graph_linked_list(graph inputGraph, std::vector<std::vector<long int>> edgesVec){
    inputGraph.copy(generatedGraph);
    
    // std::cout << "Done copy graph" << std::endl;

    decodeValue = inputGraph.maximum_node();
    long int edgesNo = edgesVec.size();
    
    // std::cout << "Done max node" << std::endl;

    for (int i = 0; i < edgesNo; i++){
        long int node_1 = edgesVec[i][0]-1;
        long int node_2 = edgesVec[i][1]-1;

        if ((inputGraph.dist(node_1+1, node_2+1) == -1) && (inputGraph.dist(node_2+1, node_1+1) == -1)){
            continue;
        }

        if (std::max(node_1, node_2) > inputGraph.maximum_node()-1){
            continue;
        }
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
                if (i2 == j){
                    generatedGraph.matrix[encodeNode(i2,i+2)][encodeNode(j,i+2)] = 0;
                    // generatedGraph.matrix[encodeNode(j,i+2)][encodeNode(i2,i+2)] = 0;
                }
                else{
                    // generatedGraph.matrix[encodeNode(j,i+2)][encodeNode(i2,i+2)] = inputGraph.dist(i2+1, j+1); 
                    generatedGraph.matrix[encodeNode(i2,i+2)][encodeNode(j,i+2)] = inputGraph.dist(j+1, i2+1);
                }   
                // printf("set matrix[%d][%d] = %d \n", encodeNode(i2,i+2), encodeNode(j,i+2), generatedGraph.matrix[encodeNode(i2,i+2)][encodeNode(j,i+2)]);
            }
        }

        // Delete edge in old graph
        // for(int i2 = 0; i2 < generatedGraph.maximum_node(); i2++){
        //     generatedGraph.matrix[i2][encodeNode(node_1+1, i+1)] = -1;
        //     generatedGraph.matrix[encodeNode(node_1+1, i+1)][i2] = -1;
        //     // generatedGraph.delete_edge(i2+1, node_2+1);
        // }

        // Link old graph to new graph
        generatedGraph.matrix[encodeNode(node_1, i+1)][encodeNode(node_2, i+2)] = inputGraph.matrix[node_1][node_2];
        generatedGraph.matrix[encodeNode(node_2, i+2)][encodeNode(node_1, i+1)] = inputGraph.matrix[node_2][node_1];
        // std::cout << "linking graph:" << std::endl;
        // printf("[%d][%d] = [%d][%d] = %d \n", node_1+1, encodeNode(node_2, i+2)+1, node_1+1, node_2+1, generatedGraph.matrix[node_1][encodeNode(node_2, i+2)]);
        // printf("[%d][%d] = [%d][%d] = %d \n", node_2+1, encodeNode(node_1, i+2)+1, node_2+1, node_1+1, generatedGraph.matrix[node_2][encodeNode(node_1, i+2)]);

        // Delete edge in new and old graph
        // printf("prev edge need to be delete: %d -> %d \n", (node_1+1)+decodeValue*(i+1), (node_2+1)+decodeValue*(i+1));
        generatedGraph.delete_edge(encodeNode(node_1+1, i+1), encodeNode(node_2+1, i+1));
        generatedGraph.delete_edge(encodeNode(node_1+1, i+2), encodeNode(node_2+1, i+2));
    }
}

graph graph_linked_list::main_graph(){
    return generatedGraph;
}

graph_linked_list::~graph_linked_list(){
    if (generatedGraph.maximum_node() > 0)
        generatedGraph.clear();
}

long int graph_linked_list::encodeNode(long int inputNode, long int graphIndex){
    long int returnVal = inputNode+(decodeValue*(graphIndex-1));
    // printf("encode %d to %d \n", inputNode, returnVal);
    return returnVal;
}

long int graph_linked_list::decodeNode(long int inputNode){
    // if (inputNode >= decodeValue)
    //     return inputNode-decodeValue;
    // else
    //     return inputNode;
    if ((inputNode % decodeValue == 0) && (inputNode >= decodeValue)) return decodeValue;
    return inputNode - int(inputNode/decodeValue)*decodeValue;
}

path graph_linked_list::decodePath(path inputPath){
    // printf("decode value: %d \n", decodeValue);
    // std::cout << "Input path: " << std::endl;
    // inputPath.print();
    path returnPath;
    for(int i = 0; i < inputPath.size(); i++){
        // printf("input node: %d \n", inputPath.node(i));
        returnPath.add_node(decodeNode(inputPath.node(i)));
    }
    return returnPath;
}
/* ---------------------- PATH ------------------------ */

// Constructor 
path::path(){
}

path::path(std::vector<long int> nodeVec){
    for (int i = 0; i < nodeVec.size(); i++){
        nodeVector.push_back(nodeVec[i]);
    }
}

// Destructor
path::~path(){
    if (nodeVector.size() > 0)
        nodeVector.clear();
}

// node
long int path::node(long int nodeIndex){
    return nodeVector[nodeIndex];
}

// erase node
void path::erase_node(long int node_1){
    long int node_pos = find_node_pos(node_1);
    if (node_pos >= 0)
        erase_node_pos(node_pos);
}

// erase node position
void path::erase_node_pos(long int nodeIndex){
    nodeVector.erase(nodeVector.begin()+nodeIndex);
}

// Size of path
long int path::size(){
    return nodeVector.size();
}

// pop out node
long int path::pop_node(){
    long int node_poped_out;
    if (nodeVector.size() > 0){
        node_poped_out = nodeVector[nodeVector.size()];
        nodeVector.pop_back();
    }

    return node_poped_out;
}

// add node 
void path::add_node(long int node_1){
    nodeVector.push_back(node_1);
}

// add node with position
void path::add_node(long int node_1, long int pos){
    if (nodeVector.size() > 0)
        nodeVector.insert(nodeVector.begin() + pos, node_1);
    else
        nodeVector.push_back(node_1);
}

// print out path
void path::print(){
    for (int i = 0; i < nodeVector.size(); i++){
        std::cout << nodeVector[i];
        if (i < nodeVector.size() - 1){
            std::cout << " -> ";
        }
    }
}

void path::clear(){
    nodeVector.clear();
}

// find node pos
long int path::find_node_pos(long int node_1){
    for (int i = 0; i < nodeVector.size(); i++){
        if (nodeVector[i] == node_1) return i;
    }
    return -1;
}

void path::copy(path &inPath){
    inPath.nodeVector = nodeVector;
}

void path::copy(path &inPath, long int start, long int end){
    if (inPath.nodeVector.size() > 0){
        inPath.nodeVector.clear();
    }
    std::vector<long int> tempVec(nodeVector.begin()+start, nodeVector.begin()+end);
    inPath.nodeVector = tempVec; 
}

bool path::compare(path &inPath){
    if (inPath.nodeVector.size() != nodeVector.size())
        return false;

    bool flag = true;
    
    for (int i = 0; i < inPath.nodeVector.size() && flag == true; i++){
        if (inPath.nodeVector[i] != nodeVector[i])
            flag = false;
    }

    return flag;
}

path path::merge(path &inPath, bool flag, long int add_dist){
    path * new_path;

    if (flag == true)
        new_path = this;
    else{ 
        new_path = new path;
        new_path->nodeVector.assign(this->nodeVector.begin(), this->nodeVector.end());
    }

    // std::cout << "Done assign original vector" << std::endl;

    if ((new_path->size() > 0) && (inPath.size() > 0)){
        if (new_path->nodeVector[new_path->nodeVector.size()-1] == inPath.nodeVector[0]){
            new_path->nodeVector.pop_back();    
        }
    }

    // std::cout << "Done poping vector" << std::endl;

    new_path->nodeVector.insert(new_path->nodeVector.end(), inPath.nodeVector.begin(), inPath.nodeVector.end());
    // std::cout << "Done adding into vector" << std::endl;

    new_path->setDist(new_path->getDist() + inPath.getDist());
    // std::cout << "Done making new dist" << std::endl;

    return * new_path;
}

long int path::getDist(){
    return dist;
}

void path::setDist(long int new_dist){
   dist = new_dist; 
}

long int path::loopEnd(){
    long int endAt = -1;
    for (int i = 0; i < nodeVector.size()-1; i++){
        bool flag = false;
        for (int j = i+1; j < nodeVector.size(); j++){
            long int addIndex = 0;
            while ((nodeVector[i+addIndex] == nodeVector[j+addIndex]) && (j+addIndex < nodeVector.size())){
                flag = true;
                endAt = i+addIndex;
                addIndex++;
            }
            if (flag) break;
        }
        if (flag) break;
    }
    return endAt;
}