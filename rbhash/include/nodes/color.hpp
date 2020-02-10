#ifndef _COLOR_HPP_
#define _COLOR_HPP_

#include <iostream>

/**
 * @brief Colours tag as enum
 */
enum colours {RED, BLACK};


/**
 * @brief Color setter of a node
 * @details used for generic implementation
 */
class Color {
  private:
    colours _color;
  
  public:
    Color();
    Color(colours c) : _color(c) {};
    
    //various setter and getter
    colours getColor(){return this->_color;}
    void setColor(colours c){this->_color = c;}

    void setBlack(){this->_color = BLACK;}
    bool isBlack(){return (this->_color == BLACK);}

    void setRed(){this->_color = RED;}
    bool isRed(){return (this->_color == RED);}
    
    friend std::ostream& operator<<(std::ostream &Str, colours &c){
      (c==RED) ? Str<<"red" : Str<<"black";
      return Str;
    }
};

#endif //_COLOR_HPP_