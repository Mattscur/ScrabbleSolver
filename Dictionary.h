#ifndef DICTIONARY
#define DICTIONARY

#include <string>
#include <iostream>
#include <fstream>
#include "Trie.h"
#include "BloomFilter.h"

class Dictionary{
    private:
    Trie* wordTrie;
    BloomFilter* wordBloomFilter;
   
   public:
   Dictionary();
   ~Dictionary();
   bool isIn(std::string key);
   
};

#endif 