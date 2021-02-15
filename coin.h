#ifndef COIN
#define COIN

#include <iostream>
#include <string>
using namespace std;

class Coin{
public:
  Coin(string name, string price) : coinName(name), coinPrice(price) {}
  Coin(string name) : coinName(name), coinPrice("0.00") {}
  Coin() : coinName("Test"), coinPrice("0.00") {}

  //setters
  void setName(const string& newName) { coinName = newName; }
  void setPrice(const string& newPrice) { coinPrice = newPrice; }

  //getters
  string getName() const { return coinName; }
  string getPrice() const { return coinPrice; }

private:
  string coinName;
  string coinPrice;

};

#endif
