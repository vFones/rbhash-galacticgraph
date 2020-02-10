#include <chrono>
#include <loader.hpp>

int main(int argc, char **argv)
{
  if ( argc < 4 ) {
    std::cerr<<
    "./exe <string>/path/to/file{.txt} <integer>Source <integer> Destination\n";
    exit(EXIT_FAILURE);
  }
  auto l = new Loader(argv[1]);

  auto space = l->getGraph();
  if(!space)
    exit(EXIT_FAILURE);

  auto *s = space->getVertex(atoi(argv[2])-1);
  auto *d = space->getVertex(atoi(argv[3])-1);

  // if valid Vertices
  if(s != nullptr && d != nullptr) {
    std::cout<<"\nLooking for a path from "
      <<s->getKey()+1<<" to "<<d->getKey()+1<<"\n\n";
    
    space->galacticDijkstra(s, d); // main core
  }
  else {
    std::cerr << " no suitable vertices "<<std::endl;
    exit(EXIT_FAILURE);
  }
  exit(EXIT_SUCCESS);
}
