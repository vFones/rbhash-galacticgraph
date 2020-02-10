#ifndef _DEBUG_HPP_
#define _DEBUG_HPP_

#include <iostream>

/**
 * printer and debugging purpouse
 */

#define debug_print std::cerr

#ifdef DEBUG
  #define IFDEBUG if(1)
#else
  #define IFDEBUG if(0)
#endif

#endif //_DEBUG_HPP_
