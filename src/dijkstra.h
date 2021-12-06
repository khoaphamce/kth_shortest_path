#pragma once

#include "data_structure.h"
#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>

using namespace std;

//--------DIJKSTRA'S ALGORITHM--------
#ifndef dijkstra_h
#define dijkstra_h

namespace dijkstra {

struct compare {
    bool operator()(const pair<long int, long int> &a, const pair<long int, long int> &b) const {
        return a.second > b.second;
    }
};

const int my_max = 100;
const long int my_inf = 1e9;

class DijkstraObject{
    public:
        DijkstraObject();
        ~DijkstraObject(){};

        void Dijkstra(ds::graph graph, long int start);
        void makePath(long int des);

        ds::path dPath;
        vector<long int> dist;

    protected:
        long int * path;
};

}

#endif