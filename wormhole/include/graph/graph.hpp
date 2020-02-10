#ifndef _GRAPH_HPP_
#define _GRAPH_HPP_

#include <list>
#include <vector>
#include <functional>

#include <graph/vertex.hpp>
#include <priorityqueue/minPriorityQueue.hpp>

#define Vertices std::vector<Vertex *>

/**
 * @brief Undirected Graph class
 * 
 */
class Graph {
  private:
    const int _V; // no need to modify once set
    Vertices *_vertices;
    
  public:
    Graph(int vertices);
    ~Graph(){ delete [] _vertices; }

    // return all vertex
    Vertices* getVertices() {return _vertices;}
    
    //get single vertex if correctly indexed
    Vertex* getVertex(int i) { return (i < (int)this->_vertices->size() ? this->_vertices->at(i) : nullptr) ;}

    void printGraph();

    // add two Edge per call (undirected)
    void addEdge(Vertex *a, Vertex *b, int weight);
    
    /* Apply dijkstra algorithm starting from a node */
    void dijkstra(Vertex *s);

    /* overloaded dijkstra -> get a lambda function for stop criteria after 
     * extraced node finished relaxing. Return extracted node. */
    Vertex* dijkstra(Vertex *s, std::function <bool (Vertex *)>const& lambda);

    /* return a path from node D up to last prev (nullptr) or S */
    std::vector<Vertex> getPath(Vertex *s, Vertex *d);

    /* print path */
    int printPath(Vertex *s, Vertex *d, bool print = false, bool reverse = false);
    int printPath(Vertex *s, Vertex *d, std::vector<Vertex> &path, bool print = false, bool reverse = false);
};

#endif //_GRAPH_HPP_