#ifndef NODE
#define NODE

#include <bitset>
#include <string>
#include <iostream>
#include <fstream>

class Node{
  public:
  Node();
  ~Node();
  Node** children;
  bool isWord;
};

#endif