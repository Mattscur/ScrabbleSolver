#ifndef BOARD
#define BOARD

#include <bitset>
#include <string>
#include <iostream>
#include <fstream>
#include <assert.h>
#include "Trie.h"
#include "Dictionary.h"
#include "ScrabbleScorer.h"

class Board{
    private:
    Dictionary* dictionary;
    std::string boardFileName;
    ScrabbleScorer scorer;
    
    public:
    std::string* rows; //The rows of the board
    std::string* immutableRows; //The rows of the board, not to be changed. For use in scoring

    Board();
    Board(std::string fileName);
    
    std::string getWordMade(int x, int y, bool horizontal); //Gets the word made at a particular location and direction
    
    bool isLetter(char character);//Returns true if character is an uppercase or lowercase character
    bool moveCanExist(int x, int y, bool horizontal);//Is there a letter 7 or less away
    
    int scoreHorizontalWord(int x,int y); //Scores the horizontal word at the location
    int scoreVerticalWord(int x,int y); //Scores the vertical word at the location
    int scoreMove(int x, int y, bool horizontal); //Scores the move played at the location and direction
    
    void print(); //Prints the board
    
};


#endif