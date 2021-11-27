#include <iostream>
#include <vector>
#include <queue>
int V;
int E;
//vector< vector<int> > capacity(100, vector<int>(100,1000007));
using namespace std;

vector< vector<int> > create_Matrix(){

    vector< vector<int> > Matrix;
    //input vertice
    
    cout << "input number of vertices: ";
    cin >> V;

    //input edge
    
    cout << "input number of edges: ";
    cin >> E;
    
    //set all the matrix to 0
    for(int i = 0; i < V; i++){
        vector<int> row;
        Matrix.push_back(row);
        for(int j = 0; j < V; j++){
            Matrix[i].push_back(0);
        }
    }
    for (int i = 0; i < E; i++){
        int u, v, cap;
        cout << "input edge list" << endl;
        cin >> u >> v >> cap;
        //capacity transmission
        Matrix[u][v] = cap;
    }
    return Matrix;
}

// A special BFS version that returns true if there's a path from start to end.
bool check_path(vector< vector<int> > &resMatrix, int &start, int &end, vector<int> &parent){
    //array for all nodes we visited and initialize to all false.
    int n = resMatrix.size();
    bool visited[1000];
    for (int i = 0; i <= n; i++){
        visited[i] = false;
    }
        
    queue<int> q;
    
    //push start into the queue and mark it visited
    q.push(start);
    visited[start] = true;
    parent[start] = -1;
        
    //keep visiting vertice
    while(q.empty() == false){
        int u = q.front();
        q.pop();
        
        //check all of u's friends.
        for(int i = 0; i < n; i++){
            int v = i;
            int capacity = resMatrix[u][v];
            
            //find a neighbor that hasn't been visited and the capacity must be bigger than 0.
            if(visited[v] == false && capacity > 0){
                //push the neighbor into the queue, mark it's parent, and mark it visited.
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }
        
    //if end is visited, we will have a path to it. 
    if(visited[end] == true) { 
        return true; 
    }
        
    return false;
}
//ford-fulkerson algorithm to get the max flow.
int FordFulkerson(vector< vector<int> > &Matrix, int &start, int &end){
    int maxflow = 0;
    
    //the residual graph. (Same as the original graph.)
    vector< vector<int> > resMatrix;
    int n = Matrix.size();
    for(int i = 0; i < n; i++){
        vector<int> row;
        resMatrix.push_back(row);
        for(int j = 0; j < Matrix[i].size(); j++){
            resMatrix[i].push_back(Matrix[i][j]);
        }
    }
    
    //create an empty parent array for function check_path to store the augmenting path. 
    vector<int> parent;
    for(int i = 0; i < n; i++){
        parent.push_back(-1);
    }
    
    //keep calling function check_path to check for an augmenting path (from start to end)
    while(check_path(resMatrix, start, end, parent) == true){
        //find the max flow through the path we just found.
        int pathflow = 10000007;
        
        //go through the path we just found
        int v = end;
        while(v != start){
            int u = parent[v];
            
            //update the pathflow to this capacity (if smaller)
            int capacity = resMatrix[u][v];
            pathflow = min(pathflow, capacity);
            
            //setup for the next edge in the path.
            v = u;
        }
        
        //update the residual capacities of the edges and reverse edges. 
        v = end;
        while(v != start){
            int u = parent[v]; //the parent.
            
            //update the capacities.
            
            resMatrix[u][v] -= pathflow;
            resMatrix[v][u] += pathflow;
            
            //setup for the next edge in the path.
            v = u;
        }
        
        //add this path's flow to the total max flow so far.
        maxflow += pathflow;
    }
    return maxflow;
}
//////////////////////////////////////////////////////////////////////////////////////////////
void printMatrix(int V){
    
}
int main() {
    cout << "begin\n";
    
    //create matrix
    vector< vector<int> > Matrix = create_Matrix();

    cout <<"print Matrix: " << endl;
    for (int i = 0; i < V; i++){
        for (int j = 0; j < V; j++){
            cout << Matrix[i][j] << " ";
        }
        cout << endl;
    }
    //input start point
    int start;
    cout << "input start: ";
    cin >> start;

    //input end point
    int end;
    cout << "input end: ";
    cin >> end;

    cout << "The max flow from " << start << " to " << end << " is " << FordFulkerson(Matrix, start, end) << endl;
    // for(int i = 0; i < 6; i++){
    //     for(int j = 0; j < 6; j++){
    //         int start = i;
    //         int end = j;
    //         if(i == j) { continue; }
    //         cout << "The max flow from " << start << " to " << end << " is: ";
    //         cout << FordFulkerson(Matrix, start, end) << endl;
    //      }
    //     cout << endl;
    // }
    
    cout << "done\n";
    
    return 0;
}

// 0 1 15
// 0 2 12
// 1 2 9
// 1 3 11
// 2 1 5
// 2 4 13
// 3 2 9
// 3 5 25
// 4 3 8
// 4 5 6