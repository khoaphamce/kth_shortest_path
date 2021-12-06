#include "mandatory_edge.h"

using namespace mand_edge;

mand_edge_path::mand_edge_path(ds::graph inputGraph, std::vector<std::vector<long int>> inputEdges, long int sourceNode, long int finishNode){
    long int minDist = -1;
    // std::vector<ds::path *> path_list;
    // MAKE EDGE PERMUTATION
    std::vector<std::vector<std::vector<long int>>> edgesPermVec = algo::edges_order_perm(inputEdges);
    // START MAKING LIST OF PATH AND ASSIGN THE MINIMUM
    bool satisfied = false;
    // ds::path toRemovePath;
    // toRemovePath.add_node(1);
    // toRemovePath.add_node(2);
    long int prevSwap = -1;
    path.add_node(-1);
    for (int i = 0; i < edgesPermVec.size(); i++){ 
        satisfied = false;
        while(satisfied == false){
            //std::cout << "edges vector now: " << std::endl;
            // for (int i2 = 0; i2 < edgesPermVec[i].size(); i2++){
            //     printf("%d, %d \n", edgesPermVec[i][i2][0], edgesPermVec[i][i2][1]);
            // }
            ds::graph_linked_list * new_graph_list = new ds::graph_linked_list
                                                    (inputGraph, edgesPermVec[i]);
            ds::graph * new_graph = new ds::graph();
            *new_graph = new_graph_list->main_graph();
            
            // if (toRemovePath.size() > 0){
            //     new_graph->graph_matrix()[toRemovePath.node(0)][toRemovePath.node(1)] = -1;
            // }

            //std::cout << "new graph: " << std::endl;
            // new_graph->print();
            //std::cout << std::endl;

            long int encode_node = new_graph_list->encodeNode(finishNode, edgesPermVec[i].size()+1);
            
            ds::path new_path;

            dijkstra::DijkstraObject * dijk_object = new dijkstra::DijkstraObject;
            dijk_object->Dijkstra(*new_graph, sourceNode);
            dijk_object->makePath(encode_node);
            new_path = dijk_object->dPath;
            
            
            //std::cout << "before decode:" << std::endl;
            // new_path.print();
            //std::cout << std::endl;
            new_path = new_graph_list->decodePath(new_path);
            //std::cout << "after decode: " << std::endl;
            // new_path.print();
            //std::cout << std::endl;

            long int loopEndIndex;
            loopEndIndex = new_path.loopEnd();

            if (minDist < dijk_object->dist[finishNode]){
                if(new_path.size() == 1 || loopEndIndex == -1){
                    satisfied = true;
                    path = new_path;
                    minDist = dijk_object->dist[finishNode];
                    break;
                }    
            }
            
            if(new_path.size() <= 1 || loopEndIndex == -1){
                satisfied = true;
                break;
            }
            
            if (loopEndIndex != -1){
                //std::cout << "Loop found" << std::endl;
                // printf("swap node: %d -> %d \n", new_path.node(loopEndIndex+1), new_path.node(loopEndIndex+2));
                // printf("itterating through vector of edges: \n");
                bool swapFlag = false;
                for (int i2 = 0; i2 < edgesPermVec[i].size() && swapFlag==false; i2++){
                    // printf("edegs now: %d, %d \n", edgesPermVec[i][i2][0], edgesPermVec[i][i2][1]);
                    if ((new_path.node(loopEndIndex+1) == edgesPermVec[i][i2][0]) && 
                        (new_path.node(loopEndIndex+2) == edgesPermVec[i][i2][1]) &&
                         (i2 != prevSwap))
                    {
                        prevSwap = i2;
                        long int temp = edgesPermVec[i][i2][0];
                        edgesPermVec[i][i2][0] = edgesPermVec[i][i2][1];
                        edgesPermVec[i][i2][1] = temp;
                        // printf("swapped \n");
                        swapFlag = true;
                        // printf("edegs now: %d, %d \n", edgesPermVec[i][i2][0], edgesPermVec[i][i2][1]);
                    }
                        
                    else if ((new_path.node(loopEndIndex+2) == edgesPermVec[i][i2][0]) &&
                             (new_path.node(loopEndIndex+1) == edgesPermVec[i][i2][1]) &&
                             (i2 != prevSwap))
                    {
                        prevSwap = i2;
                        long int temp = edgesPermVec[i][i2][0];
                        edgesPermVec[i][i2][0] = edgesPermVec[i][i2][1];
                        edgesPermVec[i][i2][1] = temp;
                        // printf("swapped \n");
                        swapFlag = true;
                        // printf("edegs now: %d, %d \n", edgesPermVec[i][i2][0], edgesPermVec[i][i2][1]);
                    }
                    else if (i2 == edgesPermVec[i].size()-1){
                        //std::cout << "Satisfied, no loop cause by mand edges \n";
                        satisfied = true;
                        break;
                    }
                }
            }
        }
    }
    dist = minDist;
}