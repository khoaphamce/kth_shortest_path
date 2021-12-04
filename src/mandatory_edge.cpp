#include "mandatory_edge.h"

using namespace mand_edge;

mand_edge_path::mand_edge_path(ds::graph inputGraph, std::vector<std::vector<long int>> inputEdges, long int sourceNode, long int finishNode){
    long int minDist = -1;
    // std::vector<ds::path *> path_list;
    // MAKE EDGE PERMUTATION
    std::vector<std::vector<std::vector<long int>>> edgesPermVec = algo::edges_order_perm(inputEdges);
    // START MAKING LIST OF PATH AND ASSIGN THE MINIMUM
    for (int i = 0; i < edgesPermVec.size(); i++){
        ds::graph_linked_list * new_graph_list = new ds::graph_linked_list
                                                (inputGraph, edgesPermVec[i]);
        ds::graph * new_graph = new ds::graph();
        *new_graph = new_graph_list->main_graph();
        long int encode_node = new_graph_list->encodeNode(finishNode);
        
        ds::path new_path;

        dijkstra::DijkstraObject * dijk_object = new dijkstra::DijkstraObject;
        dijk_object->Dijkstra(*new_graph, sourceNode);
        dijk_object->makePath(encode_node);
        new_path = dijk_object->dPath;
        // path_list.push_back(new_path);

        if (minDist < dijk_object->dist[finishNode]){
            // std::cout << "before decode:" << std::endl;
            // new_path.print();
            // std::cout << std::endl;
            path = new_graph_list->decodePath(new_path);
            // std::cout << "after decode: " << std::endl;
            // path.print();
            // std::cout << std::endl;
            minDist = dijk_object->dist[finishNode];
        }
    }
    dist = minDist;
}