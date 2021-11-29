#include "data_structure.h"
#include <vector>
#include <queue>
#include <iostream>
using namespace std;

//--------DIJKSTRA'S ALGORITHM--------
#ifndef dijkstra_h
#define dijkstra_h

#define MAX 100
const long int  INF = 1e9;
vector<long int> dist(MAX, INF);

struct compare {
    bool operator() (const pair<long int, long int> a, const pair<long int, long int> b) const {
        return a.second > b.second;
    }
};

void Dijkstra(data_structure_h::ds::graph *graph, long int start) {
    vector<vector<long int> > matrix = graph->getMat();
    priority_queue<pair<long int, long int>, vector<pair<long int, long int> >, compare> pq;
    pq.push(make_pair(start, 0));
    dist[start] = 0;
    while(!pq.empty()) {
        pair<long int, long int> top = pq.top();
        pq.pop();
        long int vertice = top.first;
        long int weight = top.second;
        for(long int i = 0; i < matrix[vertice].size(); i++) {
            long int neighbor = matrix[vertice][i];

        }
    }
}

#endif