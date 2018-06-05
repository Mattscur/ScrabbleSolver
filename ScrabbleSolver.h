#ifndef SCRABBLESOLVER
#define SCRABBLESOLVER

#include <bitset>
#include <string>
#include <iostream>
#include <fstream>
#include <assert.h>
#include "Trie.h"
#include "Dictionary.h"
#include "Board.h"
#include "ScrabbleMove.h"

class ScrabbleSolver{
    
    public:
    ScrabbleSolver();
    ~ScrabbleSolver();
    ScrabbleSolver(std::string initialBoard);
    
    Board currentBoard;
    int count;
    Dictionary* dictionary;
    std::string boardFileName;
    std::string currentRack;
    
    std::string getRack(); //Returns the letter rack of the board
    
    bool isLetter(char character);
    
    ScrabbleMove getBestOnPosition(int x, int y); //Returns the best move to be made at the position
    ScrabbleMove getBestHorizontal(int x, int y, std::string rackLeft); //Returns the best horizontal move at the position
    ScrabbleMove getBestVertical(int x, int y, std::string rackLeft); //Returns the best vertical move at the position
    
    std::string getTopTwenty(); //Returns a string containing the top twenty moves that can be made.
};

#endif