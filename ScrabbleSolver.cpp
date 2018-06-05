#include <bitset>
#include <string>
#include <iostream>
#include <fstream>
#include <assert.h>
#include <vector>
#include "Trie.h"
#include "Dictionary.h"
#include "Board.h"
#include "ScrabbleSolver.h"
#include "ScrabbleMove.h"
ScrabbleSolver::ScrabbleSolver(){
    boardFileName = "board.txt";
    count = 0;
    currentRack = getRack();
    currentBoard = Board(boardFileName);
    dictionary = new Dictionary();
    count = 0;
}

ScrabbleSolver::~ScrabbleSolver(){
    delete dictionary;
}

ScrabbleSolver::ScrabbleSolver(std::string initialBoard){
    boardFileName = initialBoard;
    currentRack = getRack();
    currentBoard = Board(boardFileName);
    dictionary = new Dictionary();
}

std::string ScrabbleSolver::getRack(){
    const char * file = boardFileName.c_str();
    std::ifstream wordListFile;
    wordListFile.open (file);
    std::string line ="";
    if (wordListFile.is_open())
    {
        getline(wordListFile,line);
        wordListFile.close();
    }
    else{
        std::cout << "File not found" << std::endl;
    }
       
    for (int i = 0; i < line.size(); i++) {
        if(line[i] >= 65 && line[i] <=90){
            line[i] = line[i];// + 32;
        }
    }
    
    return line;
}

ScrabbleMove ScrabbleSolver::getBestHorizontal(int x, int y, std::string rackLeft){
    ScrabbleMove bestMove = ScrabbleMove("DEFAULT BEST MOVE",0,0,true,0); //Best move that can be made
    int count = 0;
    
        
    if(isLetter(currentBoard.rows[x][y])){
        return bestMove; //No move possible
    }
    
    
    char initialBoardChar = currentBoard.rows[x][y]; //Saves character on board to restore it later
    int rackLength = rackLeft.length(); 
    
    for (int i = 0; i < rackLength; i++) {
        ScrabbleMove moveGenerated;
        moveGenerated = ScrabbleMove("DEFAULT BEST MOVE",0,0,true,0);
        
        currentBoard.rows[x][y] = rackLeft[i]; //Place letter down
        
        
        std::string verticalWord = currentBoard.getWordMade(x,y,false);
        if(verticalWord.length() > 1 && !dictionary->isIn(verticalWord)){ //If letter placed does not make a valid word vertically
            continue;
        }
        
        if(y < 14 && rackLength > 1){ //If not at end of board and there are letters still in rack
            std::string insertString = ""; //String to restore Rack later
            insertString += rackLeft[i];
            
            rackLeft.erase(i,1); //Removes letter from Rack
            
            moveGenerated = getBestHorizontal(x,y+1,rackLeft); //Recursive call with the tile placed
            rackLeft.insert(i,insertString); //Restores Rack
        }
        if(moveGenerated.score == 0){ //If no bigger words could be made
        
            std::string word = currentBoard.getWordMade(x,y,true); //Gets Word made from placing tile down
            
            if(dictionary->isIn(word)){ //If the word made is in dictionary
                int moveScore = currentBoard.scoreMove(x,y-(7-rackLength),true);
                moveGenerated = ScrabbleMove(word, x, y-(7-rackLength), true, moveScore); 
            }
        }
        if(bestMove.compare(moveGenerated) <= 0){
            bestMove = moveGenerated;
        }
    }
    
    currentBoard.rows[x][y] = initialBoardChar;
    return bestMove;
}

ScrabbleMove ScrabbleSolver::getBestVertical(int x, int y, std::string rackLeft){
    ScrabbleMove bestMove = ScrabbleMove("DEFAULT BEST MOVE",0,0,false,0); //Best move that can be made
    
    
    if(isLetter(currentBoard.rows[x][y])){
        return bestMove; //No move possible
    }
    
    
    char initialBoardChar = currentBoard.rows[x][y]; //Saves character on board to restore it later
    int rackLength = rackLeft.length();
    
    
    for (int i = 0; i < rackLength; i++) {
        ScrabbleMove moveGenerated;
        moveGenerated = ScrabbleMove("DEFAULT BEST MOVE",0,0,false,0);
        
        currentBoard.rows[x][y] = rackLeft[i]; //Place letter down
        
        std::string horizontalWord = currentBoard.getWordMade(x,y,true);
        if(horizontalWord.length() > 1 && !dictionary->isIn(horizontalWord)){ //If letter placed does not make a valid word horizontally
           continue;
        }
        
        if(x < 14 && rackLength > 1){ //If not at end of board and there are letters still in rack
            std::string insertString = ""; //String to restore Rack later
            insertString += rackLeft[i];
            
            rackLeft.erase(i,1); //Removes letter from Rack
            
            moveGenerated = getBestVertical(x+1,y,rackLeft); //Recursive call with the tile placed
            
            rackLeft.insert(i,insertString); //Restores Rack
        }
        
        if(moveGenerated.score == 0){ //If no bigger words could be made
            
            std::string word = currentBoard.getWordMade(x,y,false); //Gets Word made from placing tile down
            
            if(dictionary->isIn(word)){ //If the word made is in dictionary
                
                int moveScore = currentBoard.scoreMove(x-(7-rackLength),y,false);
                
                moveGenerated = ScrabbleMove(word, x-(7-rackLength), y, false, moveScore); 
                
            }
        }
        
        if(bestMove.compare(moveGenerated) < 0){
            bestMove = moveGenerated;
        }
    }
    currentBoard.rows[x][y] = initialBoardChar;
    
    return bestMove;
}

ScrabbleMove ScrabbleSolver::getBestOnPosition(int x, int y){
    if(x < 0 || y < 0){
        return ScrabbleMove();
    }
    if(x > 14 || y > 14){
        return ScrabbleMove();
    }
    if(isLetter(currentBoard.rows[x][y])){ //If space has a letter 
        return ScrabbleMove();
    }
    ScrabbleMove horizontalMove = ScrabbleMove();
    ScrabbleMove verticalMove = ScrabbleMove();
    
    
    //Searches for wildCard
    int wildCardIndex = -1;
    for (int i = 0; i < currentRack.length(); i++) {
        if(currentRack[i] == '*'){
            wildCardIndex = i;
            break;
        }
    }
    
    if(wildCardIndex == -1){
        if(currentBoard.moveCanExist(x,y,true)){ //If no word played will touch any other tiles
          horizontalMove = getBestHorizontal(x,y, currentRack);
        }
        if(currentBoard.moveCanExist(x,y,false)){ //If no word played will touch any other tiles
          verticalMove = getBestVertical(x,y, currentRack);
        }
        if(horizontalMove.compare(verticalMove) >= 0){
            return horizontalMove;
        }
        return verticalMove;
    }
    
    
    ScrabbleMove bestMove = ScrabbleMove();
    currentRack[wildCardIndex] = 'a' - 1;
    for (int i = 0; i < 26; i++) {
        currentRack[wildCardIndex]++;
        if(currentBoard.moveCanExist(x,y,true)){ //If no word played will touch any other tiles
            horizontalMove = getBestHorizontal(x,y, currentRack);
        }
        if(currentBoard.moveCanExist(x,y,false)){ //If no word played will touch any other tiles
            verticalMove = getBestVertical(x,y, currentRack);
        }
        if(horizontalMove.compare(bestMove) >= 0){
            bestMove = horizontalMove;
        }
        if(verticalMove.compare(bestMove) >= 0){
            bestMove = verticalMove;
        }
    }
        return bestMove;
}

bool ScrabbleSolver::isLetter(char character){
    return (character >= 65 && character <= 90) || 
           (character >= 97 && character <= 122);
}


std::string ScrabbleSolver::getTopTwenty(){
    /*
    The following were computed with an average of 10 calls
    Average time with dictionary NOT using Bloom Filter: 0.723061 seconds
    Average time with dictionary using Bloom Filter with 1 hashes: 0.735829 seconds
    Average time with dictionary using Bloom Filter with 2 hashes: 0.737845
    Average time with dictionary using Bloom Filter with 3 hashes: 0.99647
    Average time with dictionary using Bloom Filter with 4 hashes: 1.0585
    Average time with dictionary NOT using Bloom Filter without search space reduction: 1.91696 seconds
    */
    
    std::vector<ScrabbleMove> topList (20);
    
    ScrabbleMove moveGenerated;    
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            
            moveGenerated = getBestOnPosition(i,j);
            
            if(topList.size() < 20){
                if(i == 13 && j == 14)
                for (int a = 0; a < topList.size(); a++) {
                    if(moveGenerated.compare(topList[a]) == 1){
                        std::vector<ScrabbleMove>::iterator iter;
                        iter = topList.begin();
                        topList.insert(iter+a, moveGenerated);
                        break;
                    }
                }
            }
            else if((moveGenerated.compare(topList[19]) == 1))
            {
                for (int a = 0; a < topList.size(); a++) {
                    if(moveGenerated.compare(topList[a]) == 1){
                        std::vector<ScrabbleMove>::iterator iter;
                        iter = topList.begin();
                        topList.insert(iter+a, moveGenerated);
                        topList.pop_back();
                        break;
                    }
                }
                
            }
        }
    }
    
    std::string returnString = "";
    for (int i = 0; i < 20; i++) {
        returnString += topList[i].toString() + "\n";
    }
    return returnString;
}