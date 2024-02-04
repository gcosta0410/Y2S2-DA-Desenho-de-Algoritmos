#include <fstream>
#include <iostream>
#include <thread>
#include <iomanip>
#include <set>
#include "maxHeap.h"
#include "Ctcp.h"


/**
 * @brief Constructor: nr nodes and direction (default: directed)
 * @param num
 * @param lines
 * @param dir
 */
Ctcp::Ctcp(int num, int lines, bool dir) : n(num), hasDir(dir), nodes(num + 1), t(lines), finish(num) {

}

/**
 * @brief  Adds edge from source to destination with a certain capacity and duration
 * @param src
 * @param dest
 * @param capacity
 * @param duration
 */
void Ctcp::addLine(int src, int dest, int capacity, int duration) {
    if (src<1 || src>n || dest<1 || dest>n) return;
    nodes[src].adj.push_back({dest, capacity, duration, 0});
    nodes[dest].res.push_back({src, 0, duration});
}

/**
 * @brief Loads a graph from a given file
 * @param filename
 */
void Ctcp::load(const string& filename) {
    std::string line, word;
    std::vector<std::string> row;
    std::fstream file (filename, std::ios::in);
    if(file.is_open()){
        getline(file, line);
        while(getline(file, line)) {
            std::stringstream str(line);
            row.clear();
            while (getline(str, word, ' ')) {
                row.push_back(word);
            }
        this->addLine(stoi(row[0]),stoi(row[1]),stoi(row[2]),stoi(row[3]));
        }
        file.close();

    }
    else
        std::cerr<<"Could not open the file\n";
}

void Ctcp::clear() {
    if(!this->nodes.empty())
        this->nodes.clear();
}

/**
 * @brief Determine a path for a group
 * @param st
 * @param end
 * @param path
 * @return maximum group capacity
 */
int Ctcp::getMaxCapacityPath(int st, int end, list<int> *path){

    for (auto& v:nodes) {
        v.visited = false;
        v.distance = 0;
        v.parent = -1;
    }

    nodes[0].visited = true;
    nodes[st].distance = INT_MAX;
    MaxHeap<int,double> q(n,-1);

    for(int i = 1; i <= n ; i++){
        q.insert(i,nodes[i].distance);
    }
    while(q.getSize() > 0){
        int u = q.removeMax();
        for(const auto& v: nodes[u].adj){
            if(nodes[v.dest].distance < min(nodes[u].distance, v.capacity)){
                nodes[v.dest].distance = min(nodes[u].distance, v.capacity);
                nodes[v.dest].parent = u;
                q.increaseKey(v.dest,v.capacity);
            }
        }
    }

    path->clear();
    int shortestCapacity = INT_MAX;
    int v = end;
    path->push_front(v);

    if(nodes[v].parent == -1) {
        path->clear();
        return -1;
    }

    while(v != st){
        int aux = v;
        v = nodes[v].parent;

        for(auto e: nodes[v].adj) {
            if(e.dest == aux && e.capacity < shortestCapacity) {
                shortestCapacity = e.capacity;
            }
        }

        path->push_front(v);
    }

    return shortestCapacity;
}

/**
 * @brief Output possible non-comparable paths that maximize group size
 * and minimize edges
 * @param st
 * @param end
 * @param path
 * @return whether function was successful
 */
int Ctcp::getMaxCapacityOrLeastChanges(int st, int end, list<int> *path) {
    list<list<int>> solutions;

    vector<int> capacities;

    bfs2(st,end);
    list<int> pathAux,pathAux2;
    path->clear();
    int maxCapacity = INT_MAX;
    int v = end;
    pathAux.push_front(v);

    if(nodes[v].parent == -1) {
        cout << "We couldn't find a path for you!" << endl;
        return -1;
    }

    while(v!=st){
        v = nodes[v].parent;
        pathAux.push_front(v);
    }

    setPathToUse(pathAux);
    while(nodesUnused()){
        maxCapacity = getMaxCapacityWithUsableNodes(st,end, &pathAux2);
        if(solutions.back() != pathAux2){
            solutions.push_back(pathAux2);
            capacities.push_back(maxCapacity);
        }
        for(int i = 1; i <= n; i++){
            if(!nodes[i].use){
                nodes[i].use = true;
                break;
            }
        }
    }


    vector<unsigned long long> transbordos;
    for(const auto& sol : solutions){
        transbordos.push_back(sol.size());
    }
    vector<list<int>> s(solutions.begin(), solutions.end());
    int i = 1;


    for(int b = 0 ; b < s.size() ; b++){
        int capacity = capacities[b];
        unsigned long long transbordosAux = transbordos[b];
        for(int g = 0 ; g < s.size() ; g++){
            if(g == b) continue;
            if(transbordos[g]<transbordosAux && capacities[g]>= capacity){
                s.erase(s.begin()+b);
                capacities.erase(capacities.begin()+b);
                transbordos.erase(transbordos.begin()+b);
                b--;
                break;
            }

            if(transbordos[g]==transbordosAux && capacities[g]> capacity){
                s.erase(s.begin()+b);
                capacities.erase(capacities.begin()+b);
                transbordos.erase(transbordos.begin()+b);
                b--;
                break;
            }
            if(transbordos[g]>transbordosAux && capacities[g]<= capacity){
                s.erase(s.begin()+g);
                capacities.erase(capacities.begin()+g);
                transbordos.erase(transbordos.begin()+g);
                g--;
            }
        }
    }
    cout << endl;
    for(auto path1 : s){

        cout << "Solution " << i << ":" << endl;
        cout << "Maximum number of passengers: " << capacities[i-1] << endl;
        cout << "Transbordos: " << path1.size()-1 << endl;

        cout << "PATH: ";
        for(auto e = path1.begin() ; e != path1.end() ; e++ ) {
                if(e == --path1.end()){
                    cout << *e;
                }
                else {
                    cout << *e << " -> ";
                }
        }
        cout << endl << endl;
        i++;

    }

    return EXIT_SUCCESS;
}

/**
* @brief Simple bfs
* @param v
*/
void Ctcp::bfs(int v) {
    for (int i=1; i<=n; i++) nodes[i].visited = false;
    std::queue<int> q; // queue of unvisited nodes
    q.push(v);
    nodes[v]. visited = true;
    while (!q.empty()) { // while there are still unvisited nodes
        int u = q.front(); q.pop();
        cout << u << " "; // show node order
        for (auto e : nodes[u].adj) {
            int w = e.dest;
            if (!nodes[w].visited) {
                q.push(w);
                nodes[w].visited = true;
            }
        }
    }
}

/**
 * BFS which keeps track of path
 * @param v
 * @param end
 */
void Ctcp::bfs2(int v, int end) {
    for (int i=1; i<=n; i++) nodes[i].visited = false;
    std::queue<int> q; // queue of unvisited nodes
    q.push(v);
    nodes[v]. visited = true;
    while (!q.empty()) { // while there are still unvisited nodes
        int u = q.front(); q.pop();
        for (auto e : nodes[u].adj) {
            int w = e.dest;
            if(w == end) { nodes[w].parent = u; return;}
            if (!nodes[w].visited) {
                q.push(w);
                nodes[w].parent = u;
                nodes[w].visited = true;
            }
        }
    }
}

/**
 * @brief Sets all nodes being used to true, others to false
 * @param path
 */
void Ctcp::setPathToUse(list<int> const& path) {
    for(auto node : nodes) node.use = false;
    for(auto i : path) nodes[i].use = true;
}

/**
 * @brief Determine a path for a group in a graph with used nodes
 * @param st
 * @param end
 * @param path
 * @return maximum group capacity in used nodes graph
 */
int Ctcp::getMaxCapacityWithUsableNodes(int st, int end, list<int> *path) {
    for (auto& v:nodes) {
        v.visited = false;
        v.distance = 0;
        v.parent = -1;
    }


    nodes[st].distance = INT_MAX;
    MaxHeap<int,double> q(n,-1);

    for(int i = 1; i <= n ; i++){
        q.insert(i,nodes[i].distance);
    }
    while(q.getSize() > 0){
        int u = q.removeMax();
        for(const auto& v: nodes[u].adj){
            if(nodes[v.dest].distance < min(nodes[u].distance, v.capacity) && nodes[v.dest].use){
                nodes[v.dest].distance = min(nodes[u].distance, v.capacity);
                nodes[v.dest].parent = u;
                q.increaseKey(v.dest,v.capacity);
            }
        }
    }

    path->clear();
    int shortestCapacity = INT_MAX;
    int v = end;
    path->push_front(v);

    if(nodes[v].parent == -1) {
        return 0;
    }

    while(v != st){
        int aux = v;
        v = nodes[v].parent;

        for(auto e: nodes[v].adj) {
            if(e.dest == aux && e.capacity < shortestCapacity) {
                shortestCapacity = e.capacity;
            }
        }

        path->push_front(v);
    }
    return shortestCapacity;
}


/**
 * @brief Check nodes being unused
 * @return true if unused nodes, false otherwise
 */
bool Ctcp::nodesUnused() {
    for(int i = 1; i < nodes.size(); i++) {
        if(!nodes[i].use) return true;
    }

    return false;
}


void Ctcp::visit(int i) {
    nodes[i].visited = true;
}

void Ctcp::unvisit(int i) {
    nodes[i].visited = false;
}

bool Ctcp::visited(int i) {
    return nodes[i].visited;
}



