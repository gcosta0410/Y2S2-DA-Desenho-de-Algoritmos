#include "EdmondsKarpGraph.h"

#include <chrono>
#include <vector>
#include <iostream>
#include <queue>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <stack>

/**
 * @brief Returns the remaining capacity of an edge
 * @return edge remaining capacity
 */
int EdmondsKarpGraph::Edge::residualCap() const {
    return this->cap - this->flow;
}

/**
 * @brief Augments the flow of the edge from start to dest by bottleNeck, as well as the flow of the opposite residual edge
 * @param start
 * @param dest
 * @param bottleNeck
 */
void EdmondsKarpGraph::augment(int start, int dest, int bottleNeck) {
    for(Edge &edge : nodes[start].adj){
        if(edge.to == dest){
            edge.flow += bottleNeck;
        }
    }
    for(Edge &edge : nodes[dest].res){
        if(edge.to == start){
            edge.flow -= bottleNeck;
        }
    }
}

/**
 * @brief Marks node i as visited
 * @param i
 */
void EdmondsKarpGraph::visit(int i) {
    nodes[i].visited = true;
}

/**
 * @brief Returns visited status of node i
 * @param i
 * @return true if visited, false otherwise
 */
bool EdmondsKarpGraph::isVisited(int i) {
    return nodes[i].visited;
}

/**
 * Marks all nodes as unvisited
 */
void EdmondsKarpGraph::unvisitAll() {
    for(Node &node : nodes){
        node.visited = false;
    }
}

/**
 * @brief Breadth first search used in Edmond's-karp algorithm that finds the smallest paths between faucet and sink
 * and gets the bottleneck of that path
 * @return path flow bottleneck
 */
int EdmondsKarpGraph::bfs() {
    unvisitAll();

    // queue of unvisited nodes
    queue<int> q;
    q.push(this->s); visit(s);

    vector<Edge*> aux(t+1);

    // while there are still unvisited nodes
    while(!q.empty()){
        int currentNode = q.front(); q.pop();

        // if current node is target node
        if(currentNode == t) break;

        // for each adjacent edge
        for(Edge &edge : nodes[currentNode].adj){
            int cap = edge.residualCap();

            // if there is still capacity left and next node wasn't visited
            if(cap > 0 && !isVisited(edge.to)){
                aux[edge.to] = &edge;
                q.push(edge.to); // add to queue
                visit(edge.to); // mark as visited
            }
        }
    }

    if (aux[t] == nullptr) return 0;

    int bottleNeck = 99999;

    Edge* edge = aux[t];
    vector<int>path;
    path.push_back(t);
    while(edge != nullptr){
        bottleNeck = min(bottleNeck, edge->residualCap());
        int prev = edge->from;
        path.push_back(prev);
        edge = aux[prev];
    }
    savePath(path);
    edge = aux[t];
    while(edge != nullptr){
        augment(edge->from, edge->to, bottleNeck);
        edge = aux[edge->from];
    }

    aux.clear();
    return bottleNeck;

}

/**
 * @brief Saves a path given by nodes
 * @param path
 */
void EdmondsKarpGraph::savePath(const vector<int>&path) {
    paths.push_back(path);
}

/**
 * @brief Graph ready for edmond's-karp algorithm constructor
 * @param n - number of nodes
 * @param fileName
 */
EdmondsKarpGraph::EdmondsKarpGraph(int n, const string &fileName) : t(n), nodes(n + 1), ES(n + 1), GrauE(n + 1),
                                    GrauS(n + 1), LF(n + 1) {
    std::string line, word;
    std::vector<std::string> row;

    std::fstream file (fileName, std::ios::in);
    if(file.is_open()){
        getline(file, line);
        while(getline(file, line)) {
            std::stringstream str(line);
            row.clear();
            while (getline(str, word, ' ')) {
                row.push_back(word);
            }
            this->addEdge(stoi(row[0]), stoi(row[1]), stoi(row[2]), stoi(row[3]));
        }
        file.close();

    }
    else
        std::cerr<<"Could not open the file\n";
}

/**
 * @brief Add's an edge to the graph from source to to with capacity cap and duration dur
 * @param source
 * @param to
 * @param cap
 * @param dur
 */
void EdmondsKarpGraph::addEdge(int source, int to, int cap, int dur) {
    nodes[source].adj.push_back({source, to, cap, dur});
    nodes[to].res.push_back({to, source, 0, dur});
}


/**
 * @brief Edmond's-karp algorithm main loop that calculates max flow of all the paths
 */
void EdmondsKarpGraph::edmondsKarp() {
    int flow;
    do {
        unvisitAll();
        flow = bfs();
        maxFlow += flow;
    } while (flow != 0);
}

/**
 * @brief Returns a graph's max flow
 * @return maxFlow
 */
int EdmondsKarpGraph::getMaxFlow() const {
    return maxFlow;
}

/**
 * @brief Variation of the Edmond's-karp algorithm main loop that calculates paths according to a given max flow
 * @param group_size
 */
void EdmondsKarpGraph::edmondsKarpFixedFlow(int group_size) {
    int flow;
    do {
        unvisitAll();
        flow = bfs();
        maxFlow += flow;
        if(maxFlow >= group_size){
            break;
        }
    } while (flow != 0);
}

/**
 * @brief Prints calculated paths
 */
void EdmondsKarpGraph::printPath() {
    for(const auto& path : paths){
        for(auto it = path.rbegin(); it != path.rend(); it++)
            if(it != path.rend() - 1) cout << *it << " -> ";
            else cout << *it;

        cout << std::endl;
    }
}

/**
 * @brief Calculates critical path of the whole path and gets it's minimum traversal duration
 */
int EdmondsKarpGraph::criticalPath() {
    //this->edmondsKarp();

    vector<int> ES(t + 1, 0);
    vector<int> Prec(t + 1, -1);
    vector<int> GrauE(t + 1, 0);

    for(int i = 1; i < nodes.size(); i++){
        for(Edge edge : nodes[i].adj){
            //if(edge.flow == 0) continue;
            GrauE[edge.to]++;
        }
    }

    queue<int> q;
    for(int i = 1; i < GrauE.size(); i++){
        if (GrauE[i] == 0) q.push(i);
    }

    durMin = -1;
    int vf = -1;

    while(!q.empty()){
        int v = q.front(); q.pop();
        if(durMin < ES[v]){
            durMin = ES[v];
            vf = v;
        }
        for(Edge edge : nodes[v].adj){
            //if(edge.flow == 0) continue;
            int w = edge.to;
            if(ES[w] < ES[v] + edge.dur){
                ES[w] = ES[v] + edge.dur;
                Prec[w] = v;
            }
            GrauE[w]--;
            if(GrauE[w] == 0){
                q.push(w);
            }
        }
    }

    this->ES = ES;
    this->GrauE = GrauE;

    return durMin;
}

/**
 * @brief Checks if an element elem is in FT_nodes vector
 * @param FT_nodes
 * @param elem
 * @return true if elem is in FT_nodes, false otherwise
 */
bool inVector(vector<int> FT_nodes, int elem) {
    for(int i = 0; i < FT_nodes.size(); i++) {
        if(FT_nodes[i] == elem) return true;
    }

    return false;
}

/**
 * @brief Calculates a graph's latest finish, the max wait time for the graph and the nodes where that wait time occurs
 */
void EdmondsKarpGraph::latestFinish() {
    criticalPath();

    stack<int> stack;
    vector<Node> nodes2(t + 1);

    for (int i = 1; i <= t; i++) {
        LF[i] = durMin;
        GrauS[i] = 0;
    }

    //transposto
    for(int i = 1; i <= t; i++) {
        for(auto &e: nodes[i].adj) {
            nodes2[e.to].adj.push_back({e.to, e.from, e.cap, e.dur});
        }
    }
    /*for (int i = 0; i < paths.size(); i++) {
        for (int j = 0; j < paths[i].size() - 1; j++) {
            int from_node = paths[i][j];
            int to_node = paths[i][j + 1];

            for (auto e: nodes[to_node].adj) {
                if (e.to == from_node) {
                    nodes2[from_node].adj.push_back({from_node, to_node, e.cap, e.dur});
                }
            }
        }
    }*/

    for (int i = 1; i <= t; i++) {
        for (auto &w: nodes2[i].adj) {
            GrauS[w.to]++;
        }
    }

    for (int i = 1; i <= t; i++) {
        if (GrauS[i] == 0) stack.push(i);
    }

    while (stack.size() != 0) {
        int v = stack.top();
        stack.pop();

        for (auto &w: nodes2[v].adj) {
            if (LF[w.to] > (LF[v] - w.dur)) {
                LF[w.to] = LF[v] - w.dur;
            }

            GrauS[w.to]--;

            if (GrauS[w.to] == 0) stack.push(w.to);
        }
    }

    /*for (int i = 1; i <= t; i++) {
        if (LF[i] != durMin || i == t) {
            cout << i << ": " << LF[i] << endl;
        }
    }*/

    vector<int> all_nodes(t + 1, -1);

    //biggest FT = LF - ES - duracao
    for (int i = 1; i <= t; i++) {
        if (nodes2[i].adj.size() != 0) {
            for (auto e: nodes2[i].adj) {
                if (e.dur == 0) continue;

                int temp_FT = LF[i] - ES[e.to] - e.dur;

                if(temp_FT > all_nodes[i]) {
                    all_nodes[i] = temp_FT;
                }


                if (temp_FT > FT) {
                    FT = temp_FT;
                    FT_nodes.clear();
                    FT_nodes.push_back(i);
                } else if (temp_FT == FT && !inVector(FT_nodes, i)) {
                    FT_nodes.push_back(i);
                }
            }
        }
    }

    //this->ALL_FT_nodes = all_nodes;

    /*for(int i = 1; i <= t; i++) {
        if(all_nodes[i] != -1) {
            cout << i << ": " << all_nodes[i] << endl;
        }
    }*/

    cout << "Tempo Maximo de Espera: " << FT << endl;
    cout << "Locais onde ocorre esta espera: ";

    for (auto e: FT_nodes) cout << e << " ";

    cout << endl;
}

/**
 * @brief Reset's the flow of a graph to enable edmond's-karp algorithm re-running
 */
void EdmondsKarpGraph::clear() {
    for(int i = 1; i < nodes.size(); i++){
        for(auto &edge : nodes[i].adj){
            edge.flow = 0;
        }
        for(auto &edge : nodes[i].res){
            edge.flow = 0;
        }
    }
}
