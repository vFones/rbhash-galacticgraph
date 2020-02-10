#include <parser.hpp>
#include <redblackhash.hpp>
#include "redblackhash.cpp"

#include <sstream>
#include <fstream>

// Parser 
Parser::Parser(const std::string fn, int hashsize) :
  // set hashsize
  _hashsize(hashsize),
  // set filename
  _filename(fn),
  // allocate new RBHash
  _rh(new RedBlackHash<std::string>(this->_hashsize)) {  
  
  std::ifstream filestream(this->_filename);
  std::string line;

  if(filestream.fail()){
    std::cerr << "Error opening file" << std::endl;
    exit(EXIT_FAILURE);
  }

  while(std::getline(filestream, line))
    this->insert(line);
  
  filestream.close();
}


// insert a tuple
bool Parser::insert(std::string str) {
  std::string key, data;
  std::stringstream tmpstream(str);

  int key1 = 0, key2 = 0;

  if(!std::getline(tmpstream, key, ':')) {
      std::cerr << "no delimiter key 1" << std::endl;
      return false;
  }
  key1 = atoi(key.c_str());

  if(!std::getline(tmpstream, key, ':')) {
    std::cerr << "no delimiter key 2" << std::endl;
    return false;
  }
  key2 = atoi(key.c_str());

  if(!std::getline(tmpstream, data)) {
    std::cerr << "no data" << std::endl;
    return false;
  }
  
  return this->_rh->insert(key1, key2, data);
}


// search a tuple
bool Parser::search(std::string str) {
  std::string key, data;
  std::stringstream tmpstream(str);

  int key1 = 0, key2 = 0;

  if(!std::getline(tmpstream, key, ':')) {
    IFDEBUG debug_print << "no delimiter key 1" << std::endl;
    return false;
  } key1 = atoi(key.c_str());

  if(!std::getline(tmpstream, key, ':')) {
    IFDEBUG debug_print << "no delimiter key 2" << std::endl;
    return false;
  } key2 = atoi(key.c_str());
  

  if(!std::getline(tmpstream, data)) {
    IFDEBUG debug_print << "no data" << std::endl;
    return false;
  }

  
  return this->_rh->search(key1, key2, data);
}


bool Parser::remove(std::string str) {
  std::string key, data;
  std::stringstream tmpstream(str);

  int key1 = 0, key2 = 0;

  if(!std::getline(tmpstream, key, ':')) {
    std::cerr << "no delimiter key 1" << std::endl;
    return false;
  } key1 = atoi(key.c_str());

  if(!std::getline(tmpstream, key, ':')) {
    std::cerr << "no delimiter key 2" << std::endl;
    return false;
  } key2 = atoi(key.c_str());
  

  if(!std::getline(tmpstream, data)) {
    std::cerr << "no data" << std::endl;
    return false;
  }

  return this->_rh->remove(key1, key2, data);
}

void Parser::print(){
  auto r = this->_rh->getRBHashTree()->getRoot();
  IFDEBUG {
    if(r != this->_rh->getRBHashTree()->getNil())
      std::cout<<"Root:\n"<<this->_rh->getRBHashTree()->getRoot()<<"\n";
  }
  std::cout<<"\n"<<this->_rh<<"\n";
}