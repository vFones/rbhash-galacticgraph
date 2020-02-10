#ifndef _ITEM_HPP_
#define _ITEM_HPP_

#include <limits>

/**
 * @brief Generic Item
 * @details using a double as a key
 * @tparam Data parameter as value
 */
template <class Data>
class Item {
  private:
    double _key;
    Data _data;

  public:
    Item() : _key(std::numeric_limits<double>::min()), _data {} {}
    Item(double &k) : _key(k), _data {} {}
    Item(double &k, Data &d) : _key(k), _data(d) {}

    //generic setter and getter
    void setKey(double &k) { this->_key = k; }
    double& getKey() { return this->_key; }

    void setData(Data &data) { this->_data = data; }
    Data& getData() { return this->_data; }
};

#endif //_ITEM_HPP_