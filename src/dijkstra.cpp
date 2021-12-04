#include "dijkstra.h"

using namespace dijkstra;

DijkstraObject::DijkstraObject(){
    dist = std::vector<long int>(my_max, my_inf);
    path = new long int [my_max];
}

void DijkstraObject::Dijkstra(ds::graph graph, long int start) {
    vector<vector<long int> > matrix = graph.graph_matrix();
    long int nodeNo = graph.maximum_node();
    priority_queue<pair<long int, long int>, vector<pair<long int, long int> >, compare> pq;
    dist[start] = 0;
    fill_n(path, my_max, -1);
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

void  DijkstraObject::makePath(long int des) {
    if(path[des] == -1) {
        dPath.add_node(des);
        return;
    }
    makePath(path[des]);
    dPath.add_node(des);
}