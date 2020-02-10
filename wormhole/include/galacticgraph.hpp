#ifndef _GALACTICTGRAPH_HPP_
#define _GALACTICTGRAPH_HPP_

#include <unordered_map>
#include <graph/graph.hpp>

/**
 * @brief GalacticGraph. Using wormholes for fast travel.
 * if there is a wormhole near s and d,
 * use that to teleport in 1 unit time.
 */
class GalacticGraph : public Graph {
  private:
    std::unordered_map<Vertex *, int> _wormholes;
    bool isWormhole(Vertex *x); // return true if a node is in hashmap
    
  public:
    GalacticGraph(int V) : Graph(V) {};

    // compute path from s to d, then from s to first worm and reapply dijkstra
    // using d as source, and get path from d to worm
    void galacticDijkstra(Vertex *s, Vertex *d);

    // load a vertex in hashmap
    void addWormhole(Vertex *w){this->_wormholes.insert(std::make_pair(w, 1));};
};

#endif //_GALACTICTGRAPH_HPP_
