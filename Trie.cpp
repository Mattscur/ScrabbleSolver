#include <string>
#include <iostream>
#include <fstream>
#include "Node.h"
#include "Trie.h"

Trie::Trie(){
    rootNode = new Node();
}
Trie::~Trie(){
    delete rootNode;
}

void Trie::addWord(std::string newWord){
    
    Node* currentNode = rootNode;
    
    for (int i = 0; i < newWord.length(); i++) {
        //Get to the letter we need to be at
        if(currentNode->children[(int)newWord[i] - 97] == 0){ //If no branch to next letter
            currentNode->children[(int)newWord[i] - 97] = new Node(); //Make a new node
            currentNode =  currentNode->children[(int)newWord[i] - 97]; //set current Node equal to it
        }
        else{ //There is a branch to the next letter
            currentNode =  currentNode->children[(int)newWord[i] - 97]; //set current Node equal to it
        }
    }
    
    currentNode->isWord = true;
}


bool Trie::isIn(std::string key){
     
    Node* currentNode = rootNode;
    
    for (int i = 0; i < key.length(); i++) {
        //Get to the letter we need to be at
        if(currentNode->children[(int)key[i] - 97] == 0){ //If no branch to next letter
            return false;
        }
        else{ //There is a bbranch to the next letter
            currentNode =  currentNode->children[(int)key[i] - 97];//set current Node equal to it
        }
    }
    
    return currentNode->isWord;
}