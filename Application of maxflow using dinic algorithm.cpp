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
// int* start = new int[vertices];// The matrix to check how many edges are visited
class Graph
{
    int vertices, edges;// Number of vertices and edges in graph
    int* level;// The matrix contains the level of each node
    vector<Edge>* resGraph;// The residual graph contains edge data
public:
    Graph(int vertices)
    {
        resGraph = new vector<Edge>[vertices];
        this->vertices = vertices;
        level = new int[vertices];
    }
    void addEdge(int u, int v, int cap)
    {
        Edge a = {v, 0, cap, resGraph[v].size()}; //Forward edge from u to v
        Edge b = {u, 0, 0, resGraph[u].size()}; // Reverse edge from v to u with 0 capacity
                                                //and negative flow
        resGraph[u].push_back(a); //add forward to the u vertex
        resGraph[v].push_back(b); //add reverse to the v vertex
    }
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
    void PrintGraph()
    {
        for(int i = 0; i < vertices; i++)
        {
            for(int j = 0; j < vertices; j++)
            {
                cout << resGraph[i][j].cap << " ";
            }
            cout << endl;
        }
    }
};
int Graph::augmentFlow(int u, int flow, int t, int start[])
{   
    if(u == t)
        {
        	cout<<endl<<"12";
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
                
                //cout<<e.v<<"<-";
                if(tempFlow > 0)
                {
                	cout<<"<-"<<u;
                    e.flow += tempFlow;//Add flow to current edge
                    resGraph[e.v][e.rev].flow -= tempFlow;//Subtract flow to reverse edge of current edge
                    return tempFlow;
                }
            }
            i++;
        }
        return 0;
}
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

//Initialize the graph
// void createGraph(vector<Edge>* resGraph)
// {
//     resGraph = new vector<Edge>[vertices];
// }

//A method to add edge to the graph
// void addEdge(int u, int v, int cap)
// {
//     Edge a = {v, 0, cap, resGraph[v].size()}; //Forward edge from u to v
//     Edge b = {u, 0, 0, resGraph[u].size()}; // Reverse edge from v to u with 0 capacity
//                                             //and negative flow
//     resGraph[u].push_back(a); //add forward to the u vertex
//     resGraph[v].push_back(b); //add reverse to the v vertex
// }
//Assign Level by using breadth first search algorithm
// bool labelLevelBFS(int s, int t)
// {
//     for(int i = 0; i < vertices; i++)
//     {
//         level[i] = -1; //Assign level of all vertices is -1
//     }

//     level[s] = 0; //Level of source is 0

//     queue<int> q;// Create a queue to conduct breadth first search algorithm
//     q.push(s);
//     while (!q.empty())
//     {
//         int u = q.front();
//         q.pop();
//         int j = 0;
//         while(j < (int)resGraph[u].size())
//         {
//             Edge &e = resGraph[u][j];
//             if(level[e.v] < 0 && e.flow < e.cap)
//             {
//                 level[e.v] = level[u] + 1; //level of "to" vertex is equal to level of "from" vertex + 1
//                 q.push(e.v);
//             }
//             j++;
//         }
//     }
//     //If we cannot reach to the sink, return false. Otherwise true
//     return level[t] < 0 ? false : true;
// }
//This method will augment the flow by using Depth-first search algorithm
//We also use the recursion for this method to go from 1 vertex to sink vertex
//u: current vertex
//flow: the flow data of edge
//t: sink vertex
//In this method, we use start[i] to count how many edges explored from i
// int augmentFlow(int u, int flow, int t)
// {
//     if(u == t)
//     {
//         return flow;
//     }

//     int& i = start[u];
//     while(i < (int)resGraph[u].size())//Traverse all edges one by one
//     {
//         Edge &e = resGraph[u][i];//Pick edge from resdiual graph
//         if(level[e.v] == level[u] + 1 && e.flow < e.cap)
//         {
//             int currentFlow = min(flow, e.cap - e.flow);//Find minimum flow from u to t
//             int tempFlow = augmentFlow(e.v, currentFlow, t);//Use recursion to go to next edge from u

//             if(tempFlow > 0)
//             {
//                 e.flow += tempFlow;//Add flow to current edge
//                 resGraph[e.v][e.rev].flow -= tempFlow;//Subtract flow to reverse edge of current edge
//                 return tempFlow;
//             }
//         }
//         i++;
//     }
//     return 0;
// }
//Find maximum flow
// int DinicAlgorithm(int s, int t)
// {
//     if(s == t) // If graph only has one vertex case
//     {
//         return -1;
//     }
//     int maxFlow = 0;
//     //We will augment the flow while existing the path from s to t
//     while(labelLevelBFS(s, t))
//     {
//         //Initialize the visited matrix
//         for(int i = 0; i < vertices; i++)
//         {
//             start[i] = 0;
//         }
//         //If flow is not 0 from s to t
//         while(int flow = augmentFlow(s, INT_MAX, t))
//         {
//             maxFlow += flow;//Add that minimum flow to maxflow
//         }
//     }
//     return maxFlow;
// }
int main()
{   int u, v, cap;
    int vertices, edges; 
    int flow = 700000000;
    int t;
    int* start = new int[vertices + 1];
            for(int i = 0; i < vertices; i++)
            {
                start[i] = 0;
            }
    do
    {
        cin >> vertices;
    } while (vertices < 1);
    do
    {
        cin >> edges;
    } while (edges < 1);
    Graph g(vertices);
    for(int i = 0; i < edges; i++)
    {
        cin >> u >> v >> cap;
        g.addEdge(u,v,cap);
    }
    //   cout << "The matrix is generated from the graph: " << endl;
    //Print matrix
    // for(int i = 0; i < vertices; i++)
    // {
    //     for(int j = 0; j < vertices; j++)
    //     {
    //         cout << g.resGraph[i][j].cap << " ";
    //     }
    //     cout << endl;
    // }
    int source, sink;
    cout << "Input source vertex: "; cin >> source;
    cout << "Input sink vertex: "; cin >> sink;
    cout<<"the path is:"<<endl;
    cout<<endl;
    int trafficFlow = g.augmentFlow( u,  flow,  t,  start);
    cout <<endl<< "Maximum flow from " << source << " to " << sink << " is " <<g.DinicAlgorithm(source, sink);
}
