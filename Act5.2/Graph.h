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


class Graph {
  private:
    int numNodes;
    int numEdges;
  
    map<string, vector<pair<string,int>>> adjList;
    map<string, int> mapGetIn;
    void split(string line, vector<int> & res);
    void printAdjList();
  
  public:
    Graph();
    Graph(int nodes, int edges);
    ~Graph();
    void addNode(string newIp);
    void addEdge(string node, pair<string,int> &newEdge);
    int getIn(string node);
    int getOut(string node);
    void printGraph();
    map<string, vector<pair<string,int>>> getData();
    vector<pair<string, int>> sortIp(vector<pair<string, int>> A);

};




#endif // __GRAPH_H_