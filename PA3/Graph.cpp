#include "Graph.h"
#include <iostream>


Graph::Graph() {

}

Graph::Graph(const Graph& rhs) {
    adjList = rhs.adjList;
}

Graph& Graph::operator=(const Graph& rhs) {
    adjList = rhs.adjList;
    return *this;

}

Graph::~Graph() {

}


void Graph::addNode(const Node& node) {
    list<Edge> edgelist;
    dv inserted;
    adjList.Insert(node.getCountry(), edgelist);

}

void Graph::addConnection(const Node& headNode, const Node& tailNode, int import) {
    Edge newEdge(tailNode, import);
    adjList.Get(headNode.getCountry()).push_back(newEdge);

}

list<Node> Graph::getAdjacentNodes(const Node& node) {
    list<Edge> edgelist;
    list<Node> adjacentNodes;
    try {
        edgelist = adjList.Get(node.getCountry());

    }
    catch (ItemNotFoundException i) {
        throw ItemNotFoundException();
    }
    for (std::list<Edge>::const_iterator it = edgelist.begin(); it != edgelist.end(); ++it) {
        adjacentNodes.push_back((*it).getTailNode());
    }
    return adjacentNodes;
}

long Graph::getTotalImports(const Node& node) {
    string key = node.getCountry();
    long totalImports = 0;
    list<Edge> edgelist = adjList.Get(key);
    for (std::list<Edge>::const_iterator it = edgelist.begin(); it != edgelist.end(); ++it) {
        totalImports += (*it).getImport();
    }
    return totalImports;
}

void Graph::deleteNode(const Node& node) {
    string key = node.getCountry();
    int size = adjList.Size();
    string* keys = new string[size];
    adjList.getKeys(keys);

    for (int i = 0; i < size; i++) {
        string currkey = keys[i];
        std::list<Edge>::const_iterator it = adjList.Get(currkey).begin();

        for (; it != adjList.Get(keys[i]).end(); ++it) {
            if (it->getTailNode().getCountry() == key) {
                it = adjList.Get(keys[i]).erase(it);
                break;
            }
        }
    }

    adjList.Delete(key);
    delete[] keys;


}

list<string> Graph::findLeastCostPath(const Node& srcNode, const Node& destNode) {
    HashTable<string, dv> dvgraph;
    minList ml;
    list<string> ret;
    list<string> finalret;
    int size = adjList.Size();
    string* keys = new string[size];
    adjList.getKeys(keys);
    for (int i = 0; i < size; i++) {
        pair p;
        dv inserted;
        p.key = keys[i];
        if (p.key == srcNode.getCountry()) {
            p.distance = 0;
            inserted.distance = 0;
        }
        dvgraph.Insert(p.key, inserted);
        ml.insertList(p);
    }
    while (!ml.isEmpty()) {
        pair min = ml.pop();
        list<Edge>::const_iterator it = adjList.Get(min.key).begin();
        list<Edge>::const_iterator it2 = adjList.Get(min.key).end();
        for (; it != it2; ++it) {
            long oldDistance = dvgraph.Get((*it).getTailNode().getCountry()).distance;
            
            long newDistance;
            
            if (dvgraph.Get(min.key).distance == LONG_MAX) {
                newDistance = LONG_MAX;
            }
            else {
                newDistance = dvgraph.Get(min.key).distance + (*it).getImport();
            }
            if (newDistance < oldDistance) {
                string id = (*it).getTailNode().getCountry();
                dvgraph.Get(id).distance = newDistance;
                dvgraph.Get(id).prevkey = min.key;
                ml.changeDistance(id, newDistance);

            }
        }
    }
    string traceName = destNode.getCountry();
    while (traceName != srcNode.getCountry()) {

        if (traceName == "") {
            ret.clear();
            delete[] keys;
            return ret;
        }

        ret.push_back(traceName);
        traceName = dvgraph.Get(traceName).prevkey;
    }
    ret.push_back(srcNode.getCountry());
    ret.reverse();
    delete[] keys;
    return ret;

}
bool Graph::searchCycle(string key, HashTable<string, cycleHelper>& cycleGraph) {
    if (cycleGraph.Get(key).visited) {
        return true;
    }
    cycleGraph.Get(key).visited = true;
    list<Edge>::const_iterator it = adjList.Get(key).begin();
    list<Edge>::const_iterator it2 = adjList.Get(key).end();
    for (; it != it2; ++it) {
        string adj = (*it).getTailNode().getCountry();
        if (!cycleGraph.Get(adj).completed) {
            bool isCycle = searchCycle(adj, cycleGraph);
            if (isCycle) {
                return true;
            }
        }
    }
    cycleGraph.Get(key).visited = false;
    cycleGraph.Get(key).completed = true;
    return false;
}

bool Graph::isCyclic() {
    HashTable<string, cycleHelper> cycleGraph;
    int size = adjList.Size();
    string* keys = new string[size];
    adjList.getKeys(keys);
    for (int i = 0; i < size; i++) {
        cycleHelper ch;
        cycleGraph.Insert(keys[i], ch);
    }
    for (int i = 0; i < size; i++) {

        if (!cycleGraph.Get(keys[i]).completed) {
            bool isCycle = searchCycle(keys[i], cycleGraph);
            if (isCycle) {
                delete[] keys;
                return true;
            }
        }
    }
    delete[] keys;
    return false;
}

list<string> Graph::getBFSPath(const Node& srcNode, const Node& destNode) {
    HashTable<string, bfstruct> bfsGraph;
    list<string> bfsPath;
    queue<string> visits;
    string destId = destNode.getCountry();
    list<Edge> adj = adjList.Get(srcNode.getCountry());
    int size = adjList.Size();
    string* keys = new string[size];
    adjList.getKeys(keys);
    for (int i = 0; i < size; i++) {
        bfstruct bf;
        bfsGraph.Insert(keys[i], bf);
    }
    bfsGraph.Get(srcNode.getCountry()).visited = true;
    visits.push(srcNode.getCountry());
    bool found = false;
    while (!visits.empty() && !found) {
        string fr = visits.front();
        visits.pop();
        bfsPath.push_back(fr);
        list<Edge> adj = adjList.Get(fr);
        list<Edge>::const_iterator it = adj.begin();
        list<Edge>::const_iterator it2 = adj.end();
        for (; it != it2; ++it) {
            string name = (*it).getTailNode().getCountry();
            if (!bfsGraph.Get(name).visited) {
                bfsGraph.Get(name).visited = true;
                bfsGraph.Get(name).prev = fr;
                visits.push(name);
                if (name == destId) {
                    int visize = visits.size();
                    for (int j = 0; j < visize; j++) {
                        bfsPath.push_back(visits.front());
                        visits.pop();
                    }
                    found = true;
                    break;
                }
            }

        }
    }
    if (bfsPath.size() == 1) {
        bfsPath.clear();
    }
    delete[] keys;
    return bfsPath;
}
