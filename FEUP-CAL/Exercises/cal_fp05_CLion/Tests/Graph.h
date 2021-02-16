/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include <list>
#include <limits>
#include <cmath>
#include "MutablePriorityQueue.h"

using namespace std;

template <class T> class Edge;
template <class T> class Graph;
template <class T> class Vertex;

#define INF std::numeric_limits<double>::max()

/************************* Vertex  **************************/

template <class T>
class Vertex {
	T info;						// content of the vertex
	vector<Edge<T> > adj;		// outgoing edges
	
	double dist = 0;
	Vertex<T> *path = NULL;
	int queueIndex = 0; 		// required by MutablePriorityQueue

	bool visited = false;		// auxiliary field
	bool processing = false;	// auxiliary field

	void addEdge(Vertex<T> *dest, double w);

public:
	Vertex(T in);
	T getInfo() const;
	double getDist() const;
	Vertex *getPath() const;

	bool operator<(Vertex<T> & vertex) const; // // required by MutablePriorityQueue
	friend class Graph<T>;
	friend class MutablePriorityQueue<Vertex<T>>;

};


template <class T>
Vertex<T>::Vertex(T in): info(in) {}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
template <class T>
void Vertex<T>::addEdge(Vertex<T> *d, double w) {
	adj.push_back(Edge<T>(d, w));
}

template <class T>
bool Vertex<T>::operator<(Vertex<T> & vertex) const {
	return this->dist < vertex.dist;
}

template <class T>
T Vertex<T>::getInfo() const {
	return this->info;
}

template <class T>
double Vertex<T>::getDist() const {
	return this->dist;
}

template <class T>
Vertex<T> *Vertex<T>::getPath() const {
	return this->path;
}

/********************** Edge  ****************************/

template <class T>
class Edge {
	Vertex<T> * dest;      // destination vertex
	double weight;         // edge weight
public:
	Edge(Vertex<T> *d, double w);
	friend class Graph<T>;
	friend class Vertex<T>;
};

template <class T>
Edge<T>::Edge(Vertex<T> *d, double w): dest(d), weight(w) {}


/*************************** Graph  **************************/

template <class T>
class Graph {
	vector<Vertex<T> *> vertexSet;      // vertex set
    vector<vector<double>> matrixFloyd;      //matrix used to floyd warshall distances
    vector<vector<Vertex<T>*>> matrixPath;       //path matrix used for floyd warshall
public:
	Vertex<T> *findVertex(const T &in) const;
	bool addVertex(const T &in);
	bool addEdge(const T &sourc, const T &dest, double w);
	int getNumVertex() const;
	vector<Vertex<T> *> getVertexSet() const;

	// Fp05 - single source
	void unweightedShortestPath(const T &s);    //TODO...
	void dijkstraShortestPath(const T &s);      //TODO...
	void bellmanFordShortestPath(const T &s);   //TODO...
	vector<T> getPathTo(const T &dest) const;   //TODO...

	// Fp05 - all pairs
    double findConnection(T source,T target);
	void floydWarshallShortestPath();   //TODO...
	vector<T> getfloydWarshallPath(const T &origin, const T &dest) const;   //TODO...

};

template <class T>
int Graph<T>::getNumVertex() const {
	return vertexSet.size();
}

template <class T>
vector<Vertex<T> *> Graph<T>::getVertexSet() const {
	return vertexSet;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
template <class T>
Vertex<T> * Graph<T>::findVertex(const T &in) const {
	for (auto v : vertexSet)
		if (v->info == in)
			return v;
	return NULL;
}

/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
template <class T>
bool Graph<T>::addVertex(const T &in) {
	if ( findVertex(in) != NULL)
		return false;
	vertexSet.push_back(new Vertex<T>(in));
	return true;
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w) {
	auto v1 = findVertex(sourc);
	auto v2 = findVertex(dest);
	if (v1 == NULL || v2 == NULL)
		return false;
	v1->addEdge(v2,w);
	return true;
}


/**************** Single Source Shortest Path algorithms ************/

template<class T>
void Graph<T>::unweightedShortestPath(const T &orig) {
    for (Vertex<T>* v: this->vertexSet){
        v->dist = INT_MAX;
        v->path = NULL;
    }
    Vertex<T> * vert = findVertex(orig);
    vert->dist = 0;
	queue<Vertex<T>*> q;
	q.push(vert);
	while(!q.empty()){
        Vertex<T> *v = q.front();
        q.pop();
        for (Edge<T> edge: v->adj){
            Vertex<T> * adj = edge.dest;
            if (adj->dist == INT_MAX){
                adj->path = v;
                adj->dist = v->dist + 1;
                q.push(adj);
            }

        }
	}
}
template <class T>
struct compare{
    bool operator()(const Vertex<T>* v1, const Vertex<T>* v2){
        return v1->getDist() > v2->getDist();
    }
};

template<class T>
void Graph<T>::dijkstraShortestPath(const T &origin) {
    for (Vertex<T> * v: this->vertexSet){
        v->path = NULL;
        v->dist = INT_MAX;
        v->processing = false;
        v->visited = false;
    }

    Vertex<T>* v = this->findVertex(origin);
    v->dist = 0;

    MutablePriorityQueue<Vertex<T>> q;
    q.insert(v);
    v->processing = true;
    while(!q.empty()){
        v = q.extractMin();
        for (Edge<T> edge: v->adj){
            Vertex <T> * adj = edge.dest;
            if (adj->dist > v->dist + edge.weight){
                adj->dist = v->dist + edge.weight;
                adj->path = v;
                if (adj->processing && !adj->visited)
                    q.decreaseKey(adj);
                else {
                    adj->processing = true;
                    q.insert(adj);
                }
            }


        }
        v->visited = true;
    }
}


template<class T>
void Graph<T>::bellmanFordShortestPath(const T &orig) {
	for (Vertex<T> * v: this->vertexSet){
	    v->path = NULL;
	    v->dist = INT_MAX;
	}
	Vertex<T> * v1 = this->findVertex(orig);
	v1->dist = 0;
	for (int i = 1; i < vertexSet.size(); i++){
        for (Vertex<T> * v: this->vertexSet){
            for (Edge<T> edge: v->adj){
                Vertex<T> * adj = edge.dest;
                if (adj->dist > v->dist + edge.weight){
                    adj->dist = v->dist + edge.weight;
                    adj->path = v;
                }
            }

        }
	}
	/**
	for (Vertex<T> *v : vertexSet){
	    for (Edge<T> edge: v->adj){
	        Vertex <T> * adj = edge.dest;
	        if (adj->dist < edge.weight + v->dist){
	            cout << "Error" << endl;
	        }
	    }
	}**/
}


template<class T>
vector<T> Graph<T>::getPathTo(const T &dest) const{
	vector<T> res;
	res.push_back(dest);
	Vertex<T>* v = findVertex(dest);
	Vertex<T>* path = v->path;
	while(path != NULL) {
        res.push_back(path->info);
        path = path->path;
    }
	reverse(res.begin(), res.end());
	return res;
}



/**************** All Pairs Shortest Path  ***************/
template <class T>
double Graph<T>::findConnection(T source, T target){
    Vertex<T>* n = findVertex(source);
    if (n == NULL) return 0;
    for (Edge<T> edge: n->adj){
        if (edge.dest->getInfo() == target) return edge.weight;
    }
    return 0;
}
template<class T>
void Graph<T>::floydWarshallShortestPath() {
    double weight;
    int nVertex = getNumVertex();           //avoid calling the same function many times
    matrixFloyd = vector<vector<double>> (nVertex, vector<double>(getNumVertex(), INFINITY));
    matrixPath = vector<vector<Vertex<T>*>>(nVertex, vector<Vertex<T>*>(getNumVertex(), NULL));

    for (int i = 0; i < nVertex; i++){
        for (int j = 0; j < nVertex; j++){
            if (i == j) matrixFloyd[i][j] = 0;      	//keep matrixPath being NULL
            if ((weight = findConnection(i+1, j+1))){   //there's a direct connection
                matrixFloyd[i][j] = weight;
                matrixPath[i][j] = vertexSet[i];
            }
        }
    }
    for (int inter = 0; inter< nVertex; inter++){   //intermediate vertex
        for (int i = 0; i< nVertex; i++){
            for (int j = 0; j < nVertex; j++){
                if (matrixFloyd[i][j] > matrixFloyd[i][inter] + matrixFloyd[inter][j]){
                    matrixFloyd[i][j] = matrixFloyd[i][inter] + matrixFloyd[inter][j];
                    matrixPath[i][j] = matrixPath[inter][j];
                }
            }
        }
    }
}

template<class T>
vector<T> Graph<T>::getfloydWarshallPath(const T &orig, const T &dest) const{
    vector<T> res;
    //get the first half
    queue<Vertex<T>*> q;
    q.push(matrixPath[orig-1][dest-1]);
    while(!q.empty()){
        Vertex<T>* v = q.front();
        q.pop();
        res.push_back(v->info);
        if (v->info == orig) break;
        q.push(matrixPath[orig-1][v->info-1]);
    }
    reverse(res.begin(), res.end());
    res.push_back(dest);

	return res;
}


#endif /* GRAPH_H_ */
