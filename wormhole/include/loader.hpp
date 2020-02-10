#ifndef _LOADER_HPP_
#define _LOADER_HPP_

#include <string>
#include <galacticgraph.hpp>

/**
 * @brief Loader class for parse file.txt into Graph
 */
class Loader {
  private:
    std::string _filename;
    GalacticGraph *_G = nullptr;

  public:
    Loader(const std::string fn);
    ~Loader(){ delete _G;}

    GalacticGraph *getGraph(){return this->_G;}
};

#endif //_LOADER_HPP_