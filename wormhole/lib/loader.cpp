#include <iostream>
#include <fstream>

#include <loader.hpp>

Loader::Loader(const std::string fn) : _filename(fn) {

  std::ifstream filestream(this->_filename);
  if(filestream.fail()){
    std::cerr << "Error opening file" << std::endl;
    exit(EXIT_FAILURE);
  }

  int V, E, W;
  filestream >> V;
  filestream >> E;
  filestream >> W;

  if(V < 1 || V > 1000 ) {
    std::cerr << "Solar systems must be at least 2 and less then 1k " << std::endl;
    exit(EXIT_FAILURE);
  }

  if(E < 0 || E > 10000 ) {
    std::cerr << "Connections must be at least one and less then 10k" << std::endl;
    exit(EXIT_FAILURE);
  }

  if(W < 1 || W > V) {
    std::cerr << "Wormholes must be at least 2 and less then V("<<V<<")" << std::endl;
    exit(EXIT_FAILURE);
  }

  std::cout << "Filling a graph with "<< V<<" nodes, ";
  std::cout << E <<" edges, ";
  std::cout << W <<" wormholes\n";

  this->_G = new GalacticGraph(V);
  auto vertices = this->_G->getVertices();

  IFDEBUG debug_print << "STARTING READING FILE: " <<E-W<< std::endl;
  for(auto it = 0; it < E-W; it++) {
    int a, b, w;
    filestream >> a;
    filestream >> b;
    filestream >> w;
    this->_G->addEdge(vertices->at(a-1), vertices->at(b-1), w);
  }
  
  
  IFDEBUG debug_print << "STARTING READING 2ndhalf: "<<W<< std::endl;
  for(auto it = 0; it < W; it++) {
     int a, b, w;
     filestream >> a;
     filestream >> b;
     filestream >> w;
     this->_G->addEdge(vertices->at(a-1), vertices->at(b-1), w);
     this->_G->addWormhole(vertices->at(b-1));
  }

  filestream.close();
  return;
}
