#include "Graph.hpp"

#include <iostream>
#include <climits>
#include <queue>

using namespace std;

Graph::Graph(int V, bool d) {
    Vcnt = V;
    Ecnt = 0;
    digraph = d;

    adj.resize(V);
    for (int i = 0 ; i < V ; i++)
        adj[i] = NULL;

    distance.resize(V);
    mark.resize(V);
    previous.resize(V);
    reset_vectors();
}

Graph::~Graph() {
    for (int v = 0 ; v < Vcnt ; v++) {
        while (adj[v]) {
            link t = adj[v]->next;;
            delete adj[v];
            adj[v] = t;
        }
    }
}

void Graph::reset_vectors() {
    for (int v = 0 ; v < Vcnt ; v++) {
        distance[v] = INT_MAX;
        mark[v] = false;
        previous[v] = -1;
    }
}

void Graph::insert(Edge e) {
    int v = e.v;
    int w = e.w;
    adj[v] = new AdjListNode(w, adj[v]);
    if (!digraph)
        adj[w] = new AdjListNode(v, adj[w]);
    Ecnt++;
}

void Graph::remove(Edge e) {
    int v = e.v;
    int w = e.w;
    if (adj[v] == NULL)
        return;
    if (adj[v]->v == w) {
        link tmp = adj[v];
        adj[v] = adj[v]->next;
        delete tmp;
    } else {
        link cur = adj[v];
        while (cur->next) {
            if (cur->next->v == w) {
                link tmp = cur->next;
                cur = tmp->next;
                delete tmp;
                break;
            } else
                cur = cur->next;
        }
    }
    Ecnt--;
}

bool Graph::isVertex(int v) {
    return (v >= 0 && v < Vcnt);
}

int Graph::degreeOf(int v) {
    link p = adj[v];
    int c = 0;
    while (p != NULL) {
        c++;
        p = p->next;
    }
    return c;
}

void Graph::BFS(int s) {
    queue<int> q;
    vector<int> adjNodes;
    reset_vectors();
    distance[s] = 0;
    q.push(s);
    while (!q.empty()) {
        int v = q.front();
        q.pop();

        adjNodes = adjNodesOf(v);
        for (int w = 0; w < adjNodes.size(); w++) {
            if (distance[adjNodes[w]] == INT_MAX) {
                distance[adjNodes[w]] = distance[v] + 1;
                previous[adjNodes[w]] = v;
                q.push(adjNodes[w]);
            }
        }
    }
}

void Graph::print() {
    cout << Vcnt << " vertices, " << Ecnt << " edges: " << endl;
    for (int v = 0; v < Vcnt; v++) {
        cout << v << ": ";
        link ptr = adj[v];
        while (ptr) {
            cout << ptr->v << " ";
            ptr = ptr->next;
        }
        cout << endl;
    }
}

bool Graph::isEdge(int v, int w) {
    /* TODO */
    
    if (adj[v] == NULL || adj[w] == NULL)
    {
        return false;
    }
    
    else if (adj[v]->v == w || adj[w]->v == v)
    {
        return true;
    }
    
    else if (adj[v]->next && adj[v]->next->v == w)
    {
        return true;
    }
    
    else if (adj[w]->next && adj[w]->next->v == v)
    {
        return true;
    }
    
    else
    {
        return false;
    }
}

vector<int> Graph::adjNodesOf(int v) {
    /* TODO */
    
    vector<int> adjacent_nodes;
    
    for (int i = 0; i < Vcnt; ++i)
    {
        if (isEdge(v, i))
        {
            adjacent_nodes.insert(adjacent_nodes.begin(), i);
        }
    }
    
    return adjacent_nodes;
}

void Graph::printPath(int v) {
    /* TODO */
    
    if (v < 0)
    {
        return;
    }
    
    printPath(previous[v]);
    
    cout << v << " ";
}
