#ifndef __GRAPH_H_
#define __GRAPH_H_
#include <iostream>
#include <vector>
#include <stack>
#include <sstream>
#include <queue>
#include <climits>
#include <map>

using std::vector;
using std::pair;
using std::stack;
using std::string;
using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::stringstream;
using std::priority_queue;
using std::pair;
using std::greater;
using std::map;

#define INF INT_MAX
#define Edge pair<string, int> // A donde llego, costo
#define Vertex pair<int, string> // Distancia (costo), ID

class Graph {
  private:
    int numNodes;
    int numEdges;
  
    map<string, vector<pair<string,int>>> adjList;
    vector<bool> visited;
    vector<int> color;


    void split(string line, vector<int> & res);
    void printAdjList();

  
  public:
    Graph();
    Graph(int nodes, int edges);
    ~Graph();
    void addNode(string newIp);
    void addEdge(string node, pair<string,int> &newEdge);
    void printGraph();
    map<string, vector<pair<string,int>>> getData();
    vector<pair<string, int>> shortestPath(string src);
    int getGrade(string node);
};




#endif // __GRAPH_H_