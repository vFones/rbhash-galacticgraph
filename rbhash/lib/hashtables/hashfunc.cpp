#include <hashtables/hashfunc.hpp>

// hashfunction overload operator()
int HashFunction::operator() (double k, int i, int m) {
  //double hashing function
  int h1 = static_cast<int>(std::fmod(k, m)); // using fmod -> double % int
  int h2 = 1 + static_cast<int>(std::fmod(k, m-1));
  return (h1+i*h2) % m;
}