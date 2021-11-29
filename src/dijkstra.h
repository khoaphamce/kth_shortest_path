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
#define MAX 100
const long int  INF = 1e9;
long int path[MAX];

struct compare {
    bool operator() (const pair<long int, long int> a, const pair<long int, long int> b) const {
        return a.second > b.second;
    }
};

vector<long int> Dijkstra(ds::graph graph, long int start) {
    vector<vector<pair<long int, long int> > > matrix = graph.makeAdMat();
    priority_queue<pair<long int, long int>, vector<pair<long int, long int> >, compare> pq;
    pq.push(make_pair(start, 0));
    vector<long int> dist(matrix.size(), INF);
    dist[start] = 0;
    fill_n(path, matrix.size(), -1);
    while(!pq.empty()) {
        pair<long int, long int> top = pq.top();
        pq.pop();
        long int vertice = top.first;
        long int weight = top.second;
        for(long int i = 0; i < matrix[vertice].size(); i++) {
            pair<long int, long int> neighbor = matrix[vertice][i];
            if(weight + neighbor.second < dist[neighbor.first]) {
                dist[neighbor.first] = weight = neighbor.second;
                pq.push(pair<long int, long int>(neighbor.first, dist[neighbor.first]));
                path[neighbor.first] = vertice;
            }
        }
    }
    return dist;
}

void makePath(long int des, ds::path *dpath) {
    if(path[des] == -1) {
        return;
    }
    makePath(path[des], dpath);
    dpath->add_node(des);
}
}

#endif