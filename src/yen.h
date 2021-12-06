#pragma once

#include "data_structure.h"
#include "algorithm"
#include "dijkstra.h"
#include <vector>

#ifndef yen_h
#define yen_h

// namespace yen{
//     class yenObject;
// }

// #endif

namespace yen
{

class yenObject{
    public:
        yenObject();
        yenObject(ds::graph inGraph);
        void makePath(long int sourceNode, long int finishNode, long int K);
        ds::path path(long int kth);
        std::vector<ds::path> getPathList();

    protected:
        ds::graph mainGraph;
        std::vector<ds::path> path_list;
        static bool comparePath(ds::path path_1, ds::path path_2);

};

}
#endif