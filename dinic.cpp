#include <iostream>
#include <vector>
#include <limits.h>
#include <queue>
using namespace std;
#define min(a, b) ((a < b) ? a : b)
struct Edge
{
    int v; //"To" vertex of a directed edge u - v
    int flow;//The amount of flow in edge
    int cap;// Capacity of edge
    int rev;//The index of reversed edge of this edge
};
// A function to intialize the matrix with -1 for all of value index
void InitializeMatrix(int** matrix, int n) 
{
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            matrix[i][j] = -1;
        }
    }
}
class Graph
{
    int vertices, edges;// Number of vertices and edges in graph
    int* level;// The matrix contains the level of each node
    vector<Edge>* resGraph;// The residual graph contains edge data
    int** matrix;// The matrix contains capacity of each edges
public:
    Graph(int vertices) // Constructor of graph, initializing all initial value
    {
        resGraph = new vector<Edge>[vertices];
        this->vertices = vertices;
        level = new int[vertices];
        matrix = new int*[vertices];
        for(int i = 0; i < vertices; i++)
        {
            matrix[i] = new int[vertices];
        }
        InitializeMatrix(matrix, vertices);
    }
    //A function to add edge to the graph
    void addEdge(int u, int v, int cap)
    {
        Edge a = {v, 0, cap, resGraph[v].size()}; //Forward edge from u to v
        Edge b = {u, 0, 0, resGraph[u].size()}; // Reverse edge from v to u with 0 capacity
                                                //and negative flow
        resGraph[u].push_back(a); //add forward to the u vertex
        resGraph[v].push_back(b); //add reverse to the v vertex

        //Transform graph to matrix
        matrix[u][v] = a.cap; 
        matrix[v][u] = b.cap;
    }
    //Assign Level by using breadth first search algorithm
    bool labelLevelBFS(int s, int t)
    {
        for(int i = 0; i < vertices; i++)
        {
            level[i] = -1; //Assign level of all vertices is -1
        }

        level[s] = 0; //Level of source is 0

        queue<int> q;// Create a queue to conduct breadth first search algorithm
        q.push(s);
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            int j = 0;
            while(j < (int)resGraph[u].size())
            {
                Edge &e = resGraph[u][j];
                if(level[e.v] < 0 && e.flow < e.cap)
                {
                    level[e.v] = level[u] + 1; //level of "to" vertex is equal to level of "from" vertex + 1
                    q.push(e.v);
                }
                j++;
            }
        }
        //If we cannot reach to the sink, return false. Otherwise true
        return level[t] < 0 ? false : true;
    }

    int augmentFlow(int u, int flow, int t, int start[]);
    int DinicAlgorithm(int s, int t);
    //Fuction to print a matrix
    void PrintGraph()
    {
        for(int i = 0; i < vertices; i++)
        {
            for(int j = 0; j < vertices; j++)
            {
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
    }
};
//This method will augment the flow by using Depth-first search algorithm
//We also use the recursion for this method to go from 1 vertex to sink vertex
//u: current vertex
//flow: the flow data of edge
//t: sink vertex
//In this method, we use start[i] to count how many edges explored from i
int Graph::augmentFlow(int u, int flow, int t, int start[])
{
    if(u == t)
        {
            return flow;
        }

        int& i = start[u];
        while(i < (int)resGraph[u].size())//Traverse all edges one by one
        {
            Edge &e = resGraph[u][i];//Pick edge from resdiual graph
            if(level[e.v] == level[u] + 1 && e.flow < e.cap)
            {
                int currentFlow = min(flow, e.cap - e.flow);//Find minimum flow from u to t
                 int tempFlow = augmentFlow(e.v, currentFlow, t, start);//Use recursion to go to next edge from u

                if(tempFlow > 0)
                {
                    e.flow += tempFlow;//Add flow to current edge
                    resGraph[e.v][e.rev].flow -= tempFlow;//Subtract flow to reverse edge of current edge
                    return tempFlow;
                }
            }
            i++;
        }
        return 0;
}
//Find maximum flow
int Graph::DinicAlgorithm(int s, int t)
{
    if(s == t) // If graph only has one vertex case
        {
            return -1;
        }
        int maxFlow = 0;
        //We will augment the flow while existing the path from s to t
        while(labelLevelBFS(s, t))
        {
            int* start = new int[vertices + 1];
            //Initialize the visited matrix
            for(int i = 0; i < vertices; i++)
            {
                start[i] = 0;
            }
            //If flow is not 0 from s to t
            while(int flow = augmentFlow(s, INT_MAX, t, start))
            {
                maxFlow += flow;//Add that minimum flow to maxflow
            }
        }
        return maxFlow;
}
int main()
{
    int vertices, edges; 
    do
    {
        cout << "Input number of vertices: ";
        cin >> vertices;
    } while (vertices < 1);
    do
    {
        cout << "Input number of edges: ";
        cin >> edges;
    } while (edges < 1);
    Graph g(vertices); // Initialize the graph
    for(int i = 0; i < edges; i++)
    {
        int u, v, cap;
        cout << "Input u, v, capacity respectively: " << endl;
        cin >> u >> v >> cap;
        g.addEdge(u,v,cap);
    }
    cout << "Matrix: " << endl;
    g.PrintGraph();
    int source, sink;
    cout << "Input source vertex: "; cin >> source;
    cout << "Input sink vertex: "; cin >> sink;
    cout << "Maximum flow from " << source << " to " << sink << " is " <<g.DinicAlgorithm(source, sink);
}
