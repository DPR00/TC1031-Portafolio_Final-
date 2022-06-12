#include "Graph.h"
#include <algorithm>

using std::cout;
using std::endl;

// Constructor
Graph::Graph(int nodes, int edges){
    numNodes = nodes;
    numEdges = edges;
}

// Deconstructor
Graph::~Graph() {
    adjList.clear();
    visited.clear();
}

// Add only a node to a graph. It was created due the input format
// Complex: O(1)
void Graph::addNode(string newNode){
    vector<pair<string,int>> tempEdge; 
    adjList[newNode] = tempEdge;
}

// Add and edge with a cost (directed graph)
// Complex: O(1)
void Graph::addEdge(string node, pair<string,int> &newEdge){
    adjList[node].push_back(newEdge);
}

// Return the grade of eahc node
// Complex: O(1)
int Graph::getGrade(string node){
    int grade = adjList[node].size();    
    return grade;
}

// Print graph
// Complex: O(n^2)
void Graph::printGraph(){
    auto iter = adjList.begin();
    while (iter != adjList.end()) {
        cout << "Vertex: [" << iter->first << "]:";
        for(int i = 0; i< adjList[iter->first].size(); i++){
            pair<string, int> pairIp = adjList[iter->first][i];
            cout << "(" << pairIp.first <<", " << pairIp.second << ") ";
        }
        //cout << " ... Size: " << getGrade(iter->first) <<"." << endl;
        cout << endl;
        ++iter;
    }
}

// Return data of the graph
// Complex: O(1)
map<string, vector<pair<string,int>>> Graph::getData(){
    return adjList;
}

// Comparator function to sort pairs according to second value
// Complex: O(1)
// Fuente: https://www.geeksforgeeks.org/sorting-a-map-by-value-in-c-stl/
bool cmp(pair<string, int>& a,
         pair<string, int>& b)
{
    return a.second > b.second;
}
  
// Function to sort the map according to value in a (key-value) pairs
// Complex: O(n*log(n))
// Fuente: https://www.geeksforgeeks.org/sorting-a-map-by-value-in-c-stl/
vector<pair<string, int>> sortMap(map<string, int>& M)
{
  
    // Declare vector of pairs
    vector<pair<string, int>> A;
    // Copy key-value pair from Map to vector of pairs
    for (auto& it : M) {
        A.push_back(it);
    }
  
    // Sort using comparator function
    sort(A.begin(), A.end(), cmp);
    
    return A;
}

// Function to get the shortest path from a source to the other nodes (Dijkstra's algorithm)
// Complex: O(nlog(n))
// Fuente: https://repositorio.tec.mx/handle/11285/648379
vector<pair<string, int>> Graph::shortestPath(string src){

    map<string, int> dist;
    auto iter = adjList.begin();
    dist[src] = 0;
    while (iter != adjList.end()) {
        if(iter->first != src){
            dist[iter->first] = INF;
        }
        ++iter;
    }
    priority_queue< Vertex, vector<Vertex>, greater<Vertex> > pq;
    Vertex vs(0, src);
    pq.push(vs);

    while(!pq.empty()){
        string u = pq.top().second;
        pq.pop();
        for(int j=0; j< (int)adjList[u].size(); j++){
            Edge e = adjList[u][j];
            string v = e.first;
            int weight = e.second;
            if(dist[v] > dist[u] + weight){
                dist[v] = dist[u] + weight;
                Vertex vtx(dist[v], v);
                pq.push(vtx);
            }
        }
    }

    return sortMap(dist);
    
}