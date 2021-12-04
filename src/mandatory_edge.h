#pragma once

#include "data_structure.h"
#include "dijkstra.h"
#include "algo.h"
#include "math_algo.h"
#include <vector>

#ifndef mandatory_edge_h
#define mandatory_edge_h

namespace mand_edge{

class mand_edge_path{
    public:
        mand_edge_path(){};
        mand_edge_path(ds::graph inputGraph, std::vector<std::vector<long int>> inputEdges, long int sourceNode, long int finishNode);
        ~mand_edge_path(){};
        ds::path path;
        long int dist;

};

}

#endif