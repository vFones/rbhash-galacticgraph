#ifndef _VERTEX_HPP_
#define _VERTEX_HPP_

#include <limits>
#include <utility> //make_pair()
#include <unordered_map>

#include <other/debug.hpp>
#include <other/item.hpp>

// dijkstra algorithm
#define inf std::numeric_limits<int>::max()

// weighted node
#define WeightedVertex std::pair< Vertex *, int >

// using adjacent map instead of vector -> O(1) direct access
#define AdjacentMap std::unordered_map< Vertex *, int >


/**
 * @brief Vertex class inherites from generic Item
 * with double as key and void* as data.
 */
class Vertex : public Item<void *>{
  private:
    double _d = inf; // distance
    Vertex *_prev = nullptr; // parent
    AdjacentMap _adjmap; // map

  public:
    Vertex(int key) : Item<void *>(key) {}
    ~Vertex(){}

    void setParent(Vertex *p) { this->_prev = p; }
    Vertex* getParent() { return this->_prev;}

    void setD(double d) { this->_d = d; }
    double getD() { return this->_d; }

    // add edge to a node in map
    void addEdge(WeightedVertex u);
    
    void printAdj();
    AdjacentMap getAdj() { return this->_adjmap; };

    // overload of operator for comparing situation
    bool operator== (Vertex &other) {return this->getKey() == other.getKey();}
    bool operator!= (Vertex &other) {return this->getKey() != other.getKey();}

    // printing purpouse
    friend std::ostream& operator<<(std::ostream &Str, Vertex *v) {
        Str<<v->getKey()+1<<"\n";
      return Str;
    };
};

#endif // _VERTEX_HPP_
