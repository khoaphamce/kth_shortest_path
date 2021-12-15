#include <iostream>
#include <vector>
#include <queue>
using namespace std;
int V;
int E;
vector< vector<int> > create_Matrix(){

    vector< vector<int> > Matrix;
    //input vertice
    
    cin >> V;

    //input edge
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
        cin >> u >> v >> cap;
        //capacity transmission
        Matrix[u][v] = cap;
    }
    return Matrix;
}
bool check_path(vector< vector<int> > &resMatrix, int &start, int &end, vector<int> &parent){
    //array for all nodes we visited and initialize to all false
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
        
        //check all of u's friends
        for(int i = 0; i < n; i++){
            int v = i;
            int capacity = resMatrix[u][v];
            
            //find a neighbor that hasn't been visited and the capacity must be bigger than 0
            if(visited[v] == false && capacity > 0){
                //push the neighbor into the queue, mark it's parent, and mark it visited
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }
        
    //if end is visited, we will have a path to it 
    if(visited[end] == true) { 
        return true; 
    }
        
    return false;
}
int FordFulkerson(vector< vector<int> > &Matrix, int &start, int &end){
    int maxflow = 0;
    //create graph
    vector< vector<int> > resMatrix;
    int n = Matrix.size();
    for(int i = 0; i < n; i++){
        vector<int> row;
        resMatrix.push_back(row);
        for(int j = 0; j < Matrix[i].size(); j++){
            resMatrix[i].push_back(Matrix[i][j]);
        }
    }
    
    //create an empty parent array for function check_path to store the augmenting path
    vector<int> parent;
    for(int i = 0; i < n; i++){
        parent.push_back(-1);
    }
    
    //keep calling function check_path to check for an augmenting path (from start to end)
    while(check_path(resMatrix, start, end, parent) == true){
        //find the max flow through the path we just found
        int pathflow = 10000007;
        
        //go through the path we just found
        int v = end;
        while(v != start){
            int u = parent[v];
            
            //update the pathflow to this capacity (if smaller)
            int capacity = resMatrix[u][v];
            pathflow = min(pathflow, capacity);
            
            //setup for the next edge in the path
            v = u;
        }
	 
	cout<<endl;
        //update the residual capacities of the edges and reverse edges
        v = end;
        cout<<end;
        while(v != start){
            int u = parent[v]; 
            cout<<"<-"<<u;
            //update the capacities
            
            resMatrix[u][v] -= pathflow;
            resMatrix[v][u] += pathflow;
            
            //setup for the next edge in the path
            v = u;
        }
        
        //add this path's flow to the total max flow so far
        maxflow += pathflow;
    }
    return maxflow;
}
int main() {
    //create matrix
    vector< vector<int> > Matrix = create_Matrix();
    cout <<"Print Matrix: " << endl;
    for (int i = 0; i < V; i++){
        for (int j = 0; j < V; j++){
            cout << Matrix[i][j] << " ";
        }
        cout << endl;
    }
    //input start point
    int start;
    cout << "Input start: ";
    cin >> start;

    //input end point
    int end;
    cout << "Input end: ";
    cin >> end;
    cout<<"the path is:"<<endl;
    int flowmax=FordFulkerson(Matrix, start, end);
    cout<<endl;
    cout << "The max flow from from the front of the front of the encyclopedia to the Ben Thanh market is " << flowmax << endl;
    return 0;
}