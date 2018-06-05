#include <bitset>
#include <string>
#include <iostream>
#include <fstream>
#include "Dictionary.h"
#include "Trie.h"
#include "BloomFilter.h"

Dictionary::Dictionary(){
  wordTrie = new Trie();
  wordBloomFilter = new BloomFilter();
  const char * file = "dictionary.txt";//.c_str(); // open only takes in a const char
  std::ifstream wordListFile;
  wordListFile.open (file);
  std::string line = "";
  if (wordListFile.is_open())
  { 
    while (getline(wordListFile,line))
    {  
      wordTrie->addWord(line);
      wordBloomFilter->add(line);
    }
    wordListFile.close();
  }
  else{
      std::cout << "File not found" << std::endl;
  }
}

Dictionary::~Dictionary(){
  delete wordTrie;
  delete wordBloomFilter;
}




bool Dictionary::isIn(std::string key){
  for (int i = 0; i < key.length(); i++) 
    if(key[i] >= 65 && key[i] <=90)
      key[i] = key[i] + 32;
    
   return wordTrie->isIn(key);
  //return wordBloomFilter->isIn(key) && wordTrie->isIn(key);
}

