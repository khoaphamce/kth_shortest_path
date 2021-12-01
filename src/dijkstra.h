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

void Dijkstra(vector<vector<long int> > matrix, long int start) {
    priority_queue<pair<long int, long int>, vector<pair<long int, long int> >, compare> pq;
    dist[start] = 0;
    fill_n(path, MAX, -1);
    pq.push(make_pair(start, 0));
    while(!pq.empty()) {
        pair<long int, long int> top = pq.top();
        long int vertice = top.first;
        long int weight = top.second;
        pq.pop();
        for(int i = 0; i < matrix.size(); i++) {
            if(vertice == matrix[i][0]) {
                if(weight + matrix[i][2] < dist[matrix[i][1]]) {
                    dist[matrix[i][1]] = weight + matrix[i][2];
                    pq.push(pair<int, int>(matrix[i][1], dist[matrix[i][1]]));
                    path[matrix[i][1]] = vertice;
                }
            }
            else if(vertice == matrix[i][1]) {
                if(weight + matrix[i][2] < dist[matrix[i][0]]) {
                    dist[matrix[i][0]] = weight + matrix[i][2];
                    pq.push(pair<int, int>(matrix[i][0], dist[matrix[i][0]]));
                    path[matrix[i][0]] = vertice;
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