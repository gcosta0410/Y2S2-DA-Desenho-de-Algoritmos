#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <vector>
#include <list>
#include <queue>
#include <iostream>

using namespace std;

class Ctcp {

    //Each edge is a vehicle
    typedef struct Edge {
        int dest;   // Destination node
        int capacity; // An integer weigh
        int duration; // Duration of the trip
        int flow;
    }Line;

    //Each node is a place, node number 1 is always the first and node nr n is always the last
    typedef struct Node {
        list<Edge> adj; // The list of outgoing edges (to adjacent nodes)
        list<Edge> res; // The list of residual edges (to adjacent nodes)
        int distance;
        int parent = -1;
        bool use;
        bool visited;   // As the node been visited on a search?
    }Place;
    const unsigned long long INF = UINT32_MAX;
    int start = 1;
    int finish;
    int n;              // Ctcp size (vertices are numbered from 1 to n)
    int t;              // Number of lines
    bool hasDir;        // false: undirect; true: directed
    vector<Node> nodes; // The list of nodes being represented
    int maxFlow;

public:
    // Constructor: nr nodes, nr lines and direction (default: directed)
    Ctcp(int nodes, int lines, bool dir = true);

    // Add edge from source to destination with a certain weight
    void addLine(int src, int dest, int capacity, int duration);
    void load(const string& filename);
    int getMaxCapacityPath(int st , int end, list<int> *path);
    int getMaxCapacityOrLeastChanges(int start , int end, list<int> *path);
    void clear();
    void bfs(int v);
    void bfs2(int start, int end);
    void setPathToUse(const list<int>& path);
    int getMaxCapacityWithUsableNodes(int st, int end, list<int> *path);
    bool nodesUnused();

    void visit(int i);
    void unvisit(int i);
    bool visited(int i);


};

#endif
