#include "Node.h"
#include <string>

Node::Node(){
    children = new Node*[26];
    for (int i = 0; i < 26; i++) {
        children[i] = 0;
    }
    isWord = false;
}

Node::~Node(){
  for (int i = 0; i < 26; i++) {
      if(children[i] != 0){
          delete children[i];
      }
  }
}