#ifndef EDGE_H
#define EDGE_H

#include "Node.h"

class Edge {
public:

    Edge() {}

    Edge(const Node& tailNode, long import_) : tailNode(tailNode), import(import_) {}


    const Node& getTailNode() const {
        return tailNode;
    }

    void setTailNode(const Node& tailNode_) {
        tailNode = tailNode_;
    }

    long getImport() const {
        return import;
    }

    void setImport(long import_) {
        import = import_;
    }


private:
    Node tailNode; // the country that imports the metal
    long import; // import value (in 1000 US$)

};
#endif //EDGE_H
