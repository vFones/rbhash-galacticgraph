#include <galacticgraph.hpp>


bool GalacticGraph::isWormhole(Vertex *x) {
  if(x != nullptr)
    return this->_wormholes.find(x) != this->_wormholes.end();
  // O(1) search
  return false;
}


void GalacticGraph::galacticDijkstra(Vertex *s, Vertex *d) {
  auto wFound = new Vertices();

  // calculate minimum path tree from source
  // saving all wormhole found
  dijkstra(s, [this, d, wFound](Vertex *tmp){
    if(isWormhole(tmp))
      wFound->push_back(tmp);
    return tmp == d; // stop criteria
  });

  std::cout<<"Travel without wormholes: ";
  auto traveldist = printPath(s, d, true);
  if(traveldist>0)
    std::cout<<" in "<< traveldist <<" time unit\n\n";
  else
    std::cout<<"\t(disconnected graph)\n\n";

  auto w1 = wFound->empty() ? nullptr : wFound->front();
  // if there was a wormhole in path, get the first extracted
  if(w1 != nullptr) {
    auto p1 = getPath(s, w1); // calculate path 

    wFound->clear();
    // calculate minimum path tree from source
    dijkstra(d, [this, s, wFound](Vertex *tmp){
      if(isWormhole(tmp))
        wFound->push_back(tmp);
      return tmp == s; // stop criteria
    });

    // if there was a womrhole in path, get the first one extracted
    auto w2 = wFound->empty() ? nullptr : wFound->front();
    
    if(w2 != nullptr && w1 != w2) { // if womrhole are different
      std::cout<<"Using wormholes -> [" << w1->getKey()+1
        << ", "<< w2->getKey()+1 <<"]: ";
      
      auto t1 = printPath(s, w1, p1, true); // print first path
      std::cout<<"^";
      auto t2 = printPath(d, w2, true, true); // print second one half
      
      std::cout<<" in "<<t1+1+t2<<" unit time\n\n";
    }
    else
      std::cerr<<"No fast travel with wormhole.\n";
  }
  else
    std::cerr<<"No wormhole from Source to Destination.\n";
}