#ifndef TESTE_DA_EDMONDSKARPGRAPH_H
#define TESTE_DA_EDMONDSKARPGRAPH_H

#include <vector>
#include <string>

using namespace std;


class EdmondsKarpGraph {

    typedef struct Edge{
        int from{}; // Parent node
        int to{}; // Child node
        int cap{}; // Capacity
        int dur{}; // Duration
        int flow = 0; // Flow

        int residualCap() const;

    }Edge;

    typedef struct Node{
        bool visited = false;
        int parent = -1;
        vector<Edge> adj; // Adjacent edges
        vector<Edge> res; // Residual edges
    }Node;

    int s = 1, t, maxFlow = 0;
    vector<Node> nodes;
    vector<vector<int>> paths;
    vector<int> ES;
    vector<int> GrauE;
    vector<int> LF;
    vector<int> GrauS;
    int durMin = -1;
    int FT = INT_MIN;
    vector<int> FT_nodes;
    vector<int> ALL_FT_nodes;

    void augment(int start, int dest, int bottleNeck);
    void visit(int i);
    bool isVisited(int i);
    void unvisitAll();
    int bfs();
    void savePath(const vector<int>&path);

public:

    EdmondsKarpGraph(int n, const string& fileName);
    void addEdge(int source, int to, int cap, int dur);
    void edmondsKarp();
    int getMaxFlow() const;
    void edmondsKarpFixedFlow(int group_size);
    void printPath();
    int criticalPath();
    void latestFinish();
    void clear();
};


#endif //TESTE_DA_EDMONDSKARPGRAPH_H
