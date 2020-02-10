#include <graph/vertex.hpp>

// insert node and weight
void Vertex::addEdge(WeightedVertex u) {
  this->_adjmap.insert(u);
}


void Vertex::printAdj() {
  std::cout << "Adj list of [" << this->getKey()+1 <<"]:"<< std::endl;
  for(auto it = this->_adjmap.begin(); it != this->_adjmap.end(); it++) {
    std::cout << " " << it->second << " to reach --> [";
    std::cout << it->first->getKey()+1 <<"]"<< std::endl;
  }
}

