/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>

using namespace std;

template<class T>
class Edge;

template<class T>
class Graph;

template<class T>
class Vertex;


/****************** Provided structures  ********************/

template<class T>
class Vertex {
    T info;                // contents
    vector<Edge<T> > adj;  // list of outgoing edges
    bool visited;          // auxiliary field used by dfs and bfs
    int indegree;          // auxiliary field used by topsort
    bool processing;       // auxiliary field used by isDAG

    void addEdge(Vertex<T> *dest, double w);

    bool removeEdgeTo(Vertex<T> *d);

public:
    Vertex(T in);

    friend class Graph<T>;
};

template<class T>
class Edge {
    Vertex<T> *dest;      // destination vertex
    double weight;         // edge weight
public:
    Edge(Vertex<T> *d, double w);

    friend class Graph<T>;

    friend class Vertex<T>;
};

template<class T>
class Graph {
    vector<Vertex<T> *> vertexSet;    // vertex set

    void dfsVisit(Vertex<T> *v, vector<T> &res) const;

    Vertex<T> *findVertex(const T &in) const;

    bool dfsIsDAG(Vertex<T> *v) const;

public:
    int getNumVertex() const;

    bool addVertex(const T &in);

    bool removeVertex(const T &in);

    bool addEdge(const T &sourc, const T &dest, double w);

    bool removeEdge(const T &sourc, const T &dest);

    vector<T> dfs() const;

    vector<T> bfs(const T &source) const;

    vector<T> topsort() const;

    int maxNewChildren(const T &source, T &inf) const;

    bool isDAG() const;
};

/****************** Provided constructors and functions ********************/

template<class T>
Vertex<T>::Vertex(T in): info(in) {}

template<class T>
Edge<T>::Edge(Vertex<T> *d, double w): dest(d), weight(w) {}


template<class T>
int Graph<T>::getNumVertex() const {
    return vertexSet.size();
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
template<class T>
Vertex<T> *Graph<T>::findVertex(const T &in) const {
    for (auto v : vertexSet)
        if (v->info == in)
            return v;
    return NULL;
}

/****************** 1a) addVertex ********************/

/*
 *  Adds a vertex with a given content/info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
template<class T>
bool Graph<T>::addVertex(const T &in) {
    if (findVertex(in) != NULL)
        return false;
    Vertex<T> *v = new Vertex<T>(in);
    this->vertexSet.push_back(v);
    return true;
}

/****************** 1b) addEdge ********************/

/*
 * Adds an edge to a graph (this), given the contents of the source (sourc) and
 * destination (dest) vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
template<class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w) {
    Vertex<T> *u = NULL;
    Vertex<T> *v = NULL;
    if ((u = findVertex(sourc)) == NULL)return false;
    if ((v = findVertex(dest)) == NULL) return false;
    u->addEdge(v, w);
    return true;
}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
template<class T>
void Vertex<T>::addEdge(Vertex<T> *d, double w) {
    this->adj.push_back(Edge<T>(d, w));
}


/****************** 1c) removeEdge ********************/

/*
 * Removes an edge from a graph (this).
 * The edge is identified by the source (sourc) and destination (dest) contents.
 * Returns true if successful, and false if such edge does not exist.
 */
template<class T>
bool Graph<T>::removeEdge(const T &sourc, const T &dest) {
    Vertex<T> *u = NULL;
    Vertex<T> *v = NULL;
    if ((u = findVertex(sourc)) == NULL) return false;
    if ((v = findVertex(dest)) == NULL) return false;
    return u->removeEdgeTo(v);
}

/*
 * Auxiliary function to remove an outgoing edge (with a given destination (d))
 * from a vertex (this).
 * Returns true if successful, and false if such edge does not exist.
 */
template<class T>
bool Vertex<T>::removeEdgeTo(Vertex<T> *d) {
    // TODO (6 lines)
    bool erased = false;
    for (auto it = this->adj.begin(); it != this->adj.end(); it++)
        if (it->dest == d) {
            adj.erase(it);
            it--;
            erased = true;
        }
    return erased;
}


/****************** 1d) removeVertex ********************/

/*
 *  Removes a vertex with a given content (in) from a graph (this), and
 *  all outgoing and incoming edges.
 *  Returns true if successful, and false if such vertex does not exist.
 */
template<class T>
bool Graph<T>::removeVertex(const T &in) {
    Vertex<T> *u = NULL;
    if ((u = findVertex(in)) == NULL) return false;
    for (auto it = vertexSet.begin(); it != vertexSet.end(); it++)   //erases the edges with the vertice
        (*it)->removeEdgeTo(u);
    for (auto it = vertexSet.begin(); it != vertexSet.end(); it++)  //erases the vertex
        if ((*it)->info == in) {
            vertexSet.erase(it);
            break;
        }

    return true;
}


/****************** 2a) dfs ********************/

/*
 * Performs a depth-first search (dfs) in a graph (this).
 * Returns a vector with the contents of the vertices by dfs order.
 * Follows the algorithm described in theoretical classes.
 */
template<class T>
vector<T> Graph<T>::dfs() const {
    vector<T> res;
    for (auto it = vertexSet.begin(); it != vertexSet.end(); it++)
        (*it)->visited = false;
    for (auto it = vertexSet.begin(); it != vertexSet.end(); it++)  //loop to ensure non-connected graphs
        if (!(*it)-> visited) dfsVisit(*it, res);
    return res;
}

/*
 * Auxiliary function that visits a vertex (v) and its adjacent not yet visited, recursively.
 * Updates a parameter with the list of visited node contents.
 */
template<class T>
void Graph<T>::dfsVisit(Vertex<T> *v, vector<T> &res) const {
    res.push_back(v->info);
    v->visited = true;
    for (auto it = v->adj.begin(); it != v->adj.end(); it++) {
        if (it->dest->visited == false)
            dfsVisit(it->dest, res);
    }

}

/****************** 2b) bfs ********************/

/*
 * Performs a breadth-first search (bfs) in a graph (this), starting
 * from the vertex with the given source contents (source).
 * Returns a vector with the contents of the vertices by dfs order.
 * Follows the algorithm described in theoretical classes.
 */
template<class T>
vector<T> Graph<T>::bfs(const T &source) const {
    vector<T> res;
    for (auto it = vertexSet.begin(); it != vertexSet.end(); it++) {
        (*it)->visited = false;
    }
    queue<Vertex<T> *> V;
    V.push(findVertex(source));
    while (!V.empty()) {
        Vertex<T> *v = V.front();  //get the vertex
        V.pop();
        v->visited = true;
        res.push_back(v->info);
        for (auto it = v->adj.begin(); it != v->adj.end(); it++) {
            if (it->dest->visited == false)
                V.push(it->dest);
        }
    }
    return res;
}

/****************** 2c) toposort ********************/

/*
 * Performs a topological sorting of the vertices of a graph (this).
 * Returns a vector with the contents of the vertices by topological order.
 * If the graph has cycles, returns an empty vector.
 * Follows the algorithm described in theoretical classes.
 */

template<class T>
vector<T> Graph<T>::topsort() const {

    for (auto it = vertexSet.begin(); it != vertexSet.end(); it++)
        (*it)->indegree = 0;


    for (auto it = vertexSet.begin(); it != vertexSet.end(); it++) {
        for (auto et = (*it)->adj.begin(); et != (*it)->adj.end(); et++) {
            et->dest->indegree += 1;
        }
    }
    queue<Vertex<T> *> V;
    V.push(vertexSet[0]);
    vector<T> res;

    while (!V.empty()) {
        Vertex<T> *v = V.front();
        V.pop();
        res.push_back(v->info);
        v->visited = true;
        for (auto it = v->adj.begin(); it != v->adj.end(); it++) {
            it->dest->indegree -= 1;
            if (it->dest->indegree == 0)
                V.push(it->dest);
        }
    }
    if (res.size() != vertexSet.size()) return {};
    return res;

}

/****************** 3a) maxNewChildren (HOME WORK)  ********************/

/*
 * Performs a breadth-first search in a graph (this), starting
 * from the vertex with the given source contents (source).
 * During the search, determines the vertex that has a maximum number
 * of new children (adjacent not previously visited), and returns the
 * contents of that vertex (inf) and the number of new children (return value).
 */

template<class T>
int Graph<T>::maxNewChildren(const T &source, T &inf) const {
    Vertex<T> *u = NULL;
    int res = 0, aux;
    if ((u = findVertex(source)) == NULL) return 0;
    for (auto it = vertexSet.begin(); it != vertexSet.end(); it++)
        (*it)-> visited = false;
    queue<Vertex<T>*> q;
    q.push(u);
    while(!q.empty()){
        Vertex<T> *v = q.front();
        q.pop();
        v->visited = true;
        aux = 0;
        for (auto it = v->adj.begin(); it != v->adj.end(); it++){
            if (it->dest->visited == false) {
                q.push(it->dest);
                aux ++;
            }
        }
        //setting
        if (aux > res){
            res = aux;
            inf = v->info;
        }

    }
    return res;
}

/****************** 3b) isDAG   (HOME WORK)  ********************/

/*
 * Performs a depth-first search in a graph (this), to determine if the graph
 * is acyclic (acyclic directed graph or DAG).
 * During the search, a cycle is found if an edge connects to a vertex
 * that is being processed in the the stack of recursive calls (see theoretical classes).
 * Returns true if the graph is acyclic, and false otherwise.
 */

template<class T>
bool Graph<T>::isDAG() const {

    for (auto it = vertexSet.begin(); it!= vertexSet.end(); it++) {
        for (auto et = vertexSet.begin(); et != vertexSet.end(); et++)
            (*et)-> visited = false;
        if (!(*it)->visited)
            if (!dfsIsDAG((*it))) return false; //cycle
    }

    return true;    //it's acycle
}

/**
 * Auxiliary function that visits a vertex (v) and its adjacent not yet visited, recursively.
 * Returns false (not acyclic) if an edge to a vertex in the stack is found.
 */
template<class T>
bool Graph<T>::dfsIsDAG(Vertex<T> *v) const {
    v->visited = true;
    bool cycle_inside = false;          //case there are connections, but they are already visited
    for (auto it = v->adj.begin(); it!= v->adj.end(); it++)
        if (!it->dest->visited) {
            if (!dfsIsDAG(it->dest)) return false;
            cycle_inside = true;
        }

    if (v->adj.empty()) return true;        //acycle
    else if (!cycle_inside) return false;   //cycle
    return true;
}

#endif /* GRAPH_H_ */
