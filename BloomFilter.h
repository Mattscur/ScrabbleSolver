#ifndef BLOOMFILTER
#define BLOOMFILTER

#include <bitset>
#include <string>
class BloomFilter{
  private:
  std::bitset<3000000> array;  
  unsigned long hash(std::string key, int i);
  unsigned long hashFunction1(std::string key);
  unsigned long hashFunction2(std::string key);
  unsigned long hashFunction3(std::string key);
  unsigned long hashFunction4(std::string key);
  
  public:
  BloomFilter();
  
  void add(std::string key);
  bool isIn(std::string key);
    
};

#endif