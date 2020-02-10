#include <graph/graph.hpp>
#include <cassert>

#include "../priorityqueue/minPriorityQueue.cpp"

/* default constructor, allocating vertices from 0 to _V */
Graph::Graph(int vertices) : _V(vertices) {
  this->_vertices = new Vertices(_V);

  int i = 0;
  for(auto v = this->_vertices->begin(); v != this->_vertices->end(); v++)
    (*v) = new Vertex(i++); // i as key
}


void initSingleSource(Vertices *v, Vertex *source) {
  for(auto vv = v->begin(); vv != v->end(); vv++ ) {
    (*vv)->setD(inf); // set max int as D
    (*vv)->setParent(nullptr); // no parent discovered
  } // init all vertices distance and parents
  source->setD(0); // exept source
}


void relax(Vertex *u, Vertex *v, int w, MinPriorityQueue<Vertex *> *Q) {
  if(u->getD() == inf && u->getParent() == nullptr)
    u->setD(0); // fix for not connected graph that has D still as inf

  if(v->getD() > u->getD() + w) { // if adj node Dist is bigger then relax
    v->setD(u->getD() + w); // set to lower
    v->setParent(u); // parent found
    Q->decreasePriority(v, v->getD()); // set priority low
  }
}


void Graph::dijkstra(Vertex *s) {
  //init all source and creaty a Minimum priority queue
  initSingleSource(this->_vertices, s);
  MinPriorityQueue<Vertex *> *Q = new MinPriorityQueue<Vertex *>();
  
  for(auto v = this->_vertices->begin(); v != this->_vertices->end(); v++ )
    Q->insert((*v), (*v)->getD()); // insert all vertices
  
  while( Q->getPQSize() != 0 ) {
    Vertex *u = Q->extractMin().first;
    auto uAdj = u->getAdj();
    for(auto v : uAdj)
      relax(u, v.first, v.second, Q);
  }
}


Vertex* Graph::dijkstra(Vertex *s, std::function <bool (Vertex *)>const& lambda) {
  //init all source and creaty a Minimum priority queue
  Vertex * u = nullptr;
  initSingleSource(this->_vertices, s);
  MinPriorityQueue<Vertex *> *Q = new MinPriorityQueue<Vertex *>();
  
  for(auto v = this->_vertices->begin(); v != this->_vertices->end(); v++ )
    Q->insert((*v), (*v)->getD()); // insert all vertices

  while( Q->getPQSize() != 0 ) {
    u = Q->extractMin().first;
    auto uAdj = u->getAdj();
    for(auto v : uAdj)
      relax(u, v.first, v.second, Q);
    
    // if lambda func return true, stop dijkstra
    if(lambda(u))
      break;
  }
  // and return lastest extracted node
  return u;
}


std::vector<Vertex> Graph::getPath(Vertex *s, Vertex *d) {
  auto tmp = d;
  std::vector<Vertex> path;
  
  // tmp goes up untill no more nodes in graph
  // or source found
  while(tmp->getParent() != nullptr && tmp != s) {
    path.push_back(*tmp);
    tmp = tmp->getParent();
  }
  
  // if previous while stopped, insert source in path
  if(tmp->getParent() != nullptr)
    tmp = tmp->getParent();
  
  path.push_back(*tmp);

  return path;
}


int Graph::printPath(Vertex *s, Vertex *d, std::vector<Vertex> &path, bool print, bool reverse) {
  auto sum = 0;
  
  // if path hasn't source and dest as first and last, don't print
  if(path.back() != *s || path.front() != *d) {
    if(print)
      std::cout << "there are no paths that connect " << s->getKey()+1
      << " with " << d->getKey()+1 << std::endl;
    sum = -1;
  }
  else {
    if(!reverse) // inserted node from dest to source,
      std::reverse(path.begin(), path.end()); // need to reverse

    if(print)
      std::cout << path.at(0).getKey()+1;

    for(auto i = 1; i < (int)path.size(); i++ ) {
      if(print)
        std::cout << "-"<< path.at(i).getKey()+1;
      
      if(reverse)
        sum += path.at(i-1).getD() - path.at(i).getD();
      else 
        sum += path.at(i).getD() - path.at(i-1).getD();
    }
  }
  return sum; // O(E) print and sum path weight returned
}


int Graph::printPath(Vertex *s, Vertex *d, bool print, bool reverse) {
  // if no path given, calculate it
  auto path = getPath(s, d);
  return printPath(s, d, path, print, reverse);
}


// add undirected edge
void Graph::addEdge(Vertex *a, Vertex *b, int weight) {
  a->addEdge(WeightedVertex(b, weight));
  b->addEdge(WeightedVertex(a, weight));
}

// for all nodes, print adj map
void Graph::printGraph() {
  for(auto x = this->_vertices->begin(); x != this->_vertices->end(); x++)
    (*x)->printAdj();
}