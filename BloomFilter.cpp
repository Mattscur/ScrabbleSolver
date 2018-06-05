#include <bitset>
#include <string>
#include <cmath>
#include "BloomFilter.h"

BloomFilter::BloomFilter(){
    array = std::bitset<3000000>(0);
}


void BloomFilter::add(std::string key){
      for (int i = 0; i < 4; i++) {
        array.set(hash(key, i),true);
      }
  }  
bool BloomFilter::isIn(std::string key){
      for (int i = 0; i < 4; i++) {
        if(array.test(hash(key, i)) < 1){ //if false;
            return false;
        }
      }
      return true;
}

unsigned long BloomFilter::hashFunction1(std::string key){
        //Fowler–Noll–Vo hash
        unsigned long initialNumber = 1000;
        unsigned long hash = initialNumber;
        unsigned long fnvPrime = 1099511628211;
        for (unsigned long i = 0; i < key.length(); i++) {
            hash = hash * fnvPrime;
            hash = hash ^ key[i];
        }
        return hash;
    }
unsigned long BloomFilter::hashFunction2(std::string key){
        //java hash
        unsigned long hash = 0;
        for(int i = 0; i < key.length(); i++){
	        hash += key[i] * ((long) pow(31,key.length() - 1 - i));
        }
        return hash;
    }
unsigned long BloomFilter::hashFunction3(std::string key){
        //Jenkins Hash
        int len = key.size();
        long hash, i;
        hash = 0;
        i =0;
        for(; i < len; ++i)
        {
            hash += key[i];
            hash += (hash << 10);
            hash ^= (hash >> 6);
        }
        hash += (hash << 3);
        hash ^= (hash >> 11);
        hash += (hash << 15);
        return hash;
    }
unsigned long BloomFilter::hashFunction4(std::string key){
        //ElfHash
        const unsigned char *s = (const unsigned char *)key.c_str();
        unsigned long h = 0, high;
        while ( *s ){
            h = ( h << 4 ) + *s++;
            if ( high = h & 0xF0000000 )
                h ^= high >> 24;
            h &= ~high;
        }
        return h;
    }

unsigned long BloomFilter::hash(std::string key, int i){
        if(i == 0){
            return hashFunction1(key)%3000000;
        }
        if(i == 1){
            return hashFunction2(key)%3000000;
        }
        if(i == 2){
            return hashFunction3(key)%3000000;
        }
        if(i == 3){
            return hashFunction4(key)%3000000;
        }
        
}    