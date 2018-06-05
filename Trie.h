#ifndef TRIE
#define TRIE

#include <string>
#include <iostream>
#include <fstream>
#include "Node.h"

class Trie{
    Node* rootNode;
    
    public:
    Trie();
    ~Trie();
    void addWord(std::string newWord);
    bool isIn(std::string key);
};

#endif