#include "Graph.h"
#include <algorithm>

using std::cout;
using std::endl;
using std::find_if;

// Constructor
Graph::Graph(int nodes, int edges){
    numNodes = nodes;
    numEdges = edges;
}

// Deconstructor
Graph::~Graph() {
    adjList.clear();
}

// Add only a node to a graph. It was created due the input format
// Complex: O(1)
void Graph::addNode(string newNode){
    vector<pair<string,int>> tempEdge; 
    adjList[newNode] = tempEdge;
    mapGetIn[newNode] = 0;
}

// Add and edge with a cost (directed graph)
// Complex: O(1)
void Graph::addEdge(string node, pair<string,int> &newEdge){
    adjList[node].push_back(newEdge);
    string tempStr = newEdge.first;
    mapGetIn[tempStr] = mapGetIn[tempStr] +1;
}

// Return the grade of eahc node
// Complex: O(1)
int Graph::getIn(string node){
    return mapGetIn[node];
}

// Return the grade of eahc node
// Complex: O(1)
int Graph::getOut(string node){
    return adjList[node].size();
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
bool cmp(pair<string, int>& a, pair<string, int>& b)
{
    return a.second > b.second;
}
  
// Function to sort a vector
// Complex: O(n*log(n))
vector<pair<string, int>> Graph::sortIp(vector<pair<string, int>> A)
{
    // Sort using comparator function
    sort(A.begin(), A.end(), cmp);   
    return A;
}

