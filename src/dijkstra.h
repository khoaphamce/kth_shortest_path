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
vector<long int> dist(MAX, INF);
long int path[MAX];
ds::path *dPath = new ds::path();

struct compare {
    bool operator()(const pair<long int, long int> &a, const pair<long int, long int> &b) const {
        return a.second > b.second;
    }
};

void Dijkstra(ds::graph graph, long int start) {
    vector<vector<long int> > matrix = graph.graph_matrix();
    long int nodeNo = graph.maximum_node();
    priority_queue<pair<long int, long int>, vector<pair<long int, long int> >, compare> pq;
    dist[start] = 0;
    fill_n(path, MAX, -1);
    pq.push(make_pair(start, 0));
    while(!pq.empty()) {
        pair<long int, long int> top = pq.top();
        long int vertice = top.first;
        long int weight = top.second;
        pq.pop();
        for(long int i = 0; i < nodeNo; i++) {
            if(matrix[vertice - 1][i] != -1) {
                if(weight + matrix[vertice - 1][i] < dist[i + 1]) {
                    dist[i + 1] = weight + matrix[vertice - 1][i];
                    pq.push(pair<long int, long int>(i + 1, dist[i + 1]));
                    path[i + 1] = vertice;
                }
            }
        }
    }
}

void makePath(long int des) {
    if(path[des] == -1) {
        dPath->add_node(des);
        return;
    }
    makePath(path[des]);
    dPath->add_node(des);
}
}

#endif