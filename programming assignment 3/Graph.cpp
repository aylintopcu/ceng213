#include "Graph.h"

/*Do not add new libraries or files*/

Graph::Graph() {
    // TODO: IMPLEMENT THIS FUNCTION.
    
    this->adjList = HashTable<string, list<Edge>>();
}

Graph::Graph(const Graph& rhs) {
    // TODO: IMPLEMENT THIS FUNCTION.
    
    this->adjList = rhs.adjList;
}

Graph& Graph::operator=(const Graph& rhs) {
    // TODO: IMPLEMENT THIS FUNCTION.
    
    if (this != &rhs)
    {
        this->adjList = rhs.adjList;
    }
    
    return *this;
}

Graph::~Graph() {
// TODO: IMPLEMENT THIS FUNCTION.

}

void Graph::addNode(const Node &node) {
    // TODO: IMPLEMENT THIS FUNCTION.
    
    list<Edge> imports;
    
    adjList.Insert(node.getCountry(), imports);
}

void Graph::addConnection(const Node& headNode, const Node& tailNode, int import) {
    // TODO: IMPLEMENT THIS FUNCTION.
    
    Edge new_import = Edge(tailNode, import);
    adjList.Get(headNode.getCountry()).push_back(new_import);
}

list<Node> Graph::getAdjacentNodes(const Node& node) {
    // TODO: IMPLEMENT THIS FUNCTION.
    
    list<Node> adj_nodes;
    list<Edge> imports = adjList.Get(node.getCountry());
    list<Edge>::iterator it;
    
    for (it = imports.begin(); it != imports.end(); ++it)
    {
        adj_nodes.push_back(it->getTailNode());
    }
    
    return adj_nodes;
}

long Graph::getTotalImports(const Node& node) {
    // TODO: IMPLEMENT THIS FUNCTION.
    
    long total_imports = 0;
    list<Edge> imports = adjList.Get(node.getCountry());
    list<Edge>::iterator it;
    
    for (it = imports.begin(); it != imports.end(); ++it)
    {
        total_imports += it->getImport();
    }
    
    return total_imports;
}

void Graph::deleteNode(const Node& node) {
    // TODO: IMPLEMENT THIS FUNCTION.
    
    adjList.Delete(node.getCountry());
    
    int size = adjList.Size();
    string *keys = new string[size];
    
    adjList.getKeys(keys);
    
    for (int i = 0; i < size; ++i)
    {
        list<Edge>::iterator it;
        list<Edge> &imports = adjList.Get(keys[i]);
        
        for (it = imports.begin(); it != imports.end(); ++it)
        {
            if (it->getTailNode().getCountry() == node.getCountry())
            {
                imports.erase(it--);
                break;
            }
        }
    }
    
    delete [] keys;
}