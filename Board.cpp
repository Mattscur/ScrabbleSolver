#include <bitset>
#include <string>
#include <iostream>
#include <fstream>
#include <assert.h>
#include "Trie.h"
#include "Board.h"
#include "Dictionary.h"
#include "ScrabbleScorer.h"
    
    
Board::Board(){
    dictionary = new Dictionary();
    scorer = ScrabbleScorer();
    rows = new std::string[15];
    immutableRows = new std::string[15];
    boardFileName = "board.txt";
    const char * file = boardFileName.c_str();
    std::ifstream wordListFile;
    wordListFile.open (file);
    std::string line ="";
    getline(wordListFile,line); //Throws out the line that contains the rack
    
    if (wordListFile.is_open()){
        for (int i = 0; i < 15; i++) 
        {
            getline(wordListFile,line);
            rows[i] = line;
            immutableRows[i] = line;
        }
    }
    
}

Board::Board(std::string fileName){
    dictionary = new Dictionary();
    scorer = ScrabbleScorer();
    rows = new std::string[15];
    immutableRows = new std::string[15];
    boardFileName = fileName;
    const char * file = boardFileName.c_str();
    std::ifstream wordListFile;
    wordListFile.open (file);
    std::string line ="";
    getline(wordListFile,line); //Throws out the line that contains the rack
    
    if (wordListFile.is_open()){
        for (int i = 0; i < 15; i++) 
        {
            getline(wordListFile,line);
            rows[i] = line;
            immutableRows[i] = line;
        }
    }
}

bool Board::isLetter(char character){
    return (character >= 65 && character <= 90) || 
           (character >= 97 && character <= 122);
}

std::string Board::getWordMade(int x, int y, bool horizontal){
    if(x < 0 || x > 14 || y < 0 || y >14 || !isLetter(rows[x][y])){ return ""; }
    

    std::string returnString = "";
    if(horizontal){
        //Walk back until you reach the first letter
        while( y > 0 && isLetter(rows[x][y])){
            y--;
        }
        //Corrects off by one error
        if(y < 15 && !isLetter(rows[x][y])){
            y++;
        }
        
        //Walk forward, adding characters, until last letter
        while(y < 15 && isLetter(rows[x][y])){
            returnString += rows[x][y];
            y++;
        }
        return returnString;
    }
    else{
        //Walk back until you reach the first letter
        while(x > 0 && isLetter(rows[x][y])){
            x--;
        }
        
        //Corrects off by one error
        if(x < 15 && !isLetter(rows[x][y])){
            x++;
        }
        
        //Walk forward, adding characters, until last letter
        while(x < 15 && isLetter(rows[x][y])){
            returnString += rows[x][y];
            x++;
        }
        return returnString;
    }
}

bool Board::moveCanExist(int x, int y, bool horizontal){
    if(x < 0 || y < 0){
        return false;
    }
    if(x > 14 || y > 14){
        return false;
    }
    if(isLetter(rows[x][y])){ 
        return false;
    }
    
    if(horizontal){
        //Check for letter to left
        if(y > 0){
            if(isLetter(rows[x][y-1])){
                return true;
            }
        }
        for (int i = 0; i < 8 && y + i < 15; i++) {
            if(y+i+1 < 15 && isLetter(rows[x][y+i+1])){ //check if the tile to the right is occupied
                return true;
            }
            if(x > 0 && isLetter(rows[x-1][y+i])){ //Checks if the tile above is occupied
                return true;            
            }
            if(x < 14 && isLetter(rows[x+1][y+i])){ //Checks if the tile below is occupied
                return true;            
            }
        }
        
        return false;
    }

    else{
        //Check for letter above
        if(x > 0){
            if(isLetter(rows[x-1][y])){
                return true;
            }
        }
        for (int i = 0; i < 8 && x + i < 15; i++) {
            if(x+i+1 < 15 && isLetter(rows[x+i+1][y])){ //check if the tile below is occupied
                return true;
            }
            if(y < 14 && isLetter(rows[x+i][y+1])){ //Checks if the tile to the right is occupied
                return true;            
            }
            if(y > 0 && isLetter(rows[x+i][y-1])){//Checks if the tile to the left  is occupied
                return true;            
            }
        }
        return false;
    }
}

int Board::scoreHorizontalWord(int x,int y){
    int score = 0;
    int wordMultiplier = 1;
    int letterMultiplier = 1;
    bool connectsToLetter = false;
    
    //Goes left until end of board or last letter
    while(y > 0 && isLetter(rows[x][y])){
        y--;
    }
    //corrects off by one error
    if( y < 15 && !isLetter(rows[x][y])){
        y++;
    }
    
    //Scores letters already on board that make the prefix
    while(y < 15 && rows[x][y] == immutableRows[x][y]){
        score += scorer.getScore(rows[x][y]);
        y++;
    }
    
    //Scores letter placed
    while(y < 15 && rows[x][y] != immutableRows[x][y]){
        if((y > 0 && isLetter(immutableRows[x][y-1])) || (y < 14 && isLetter(immutableRows[x][y+1]))){//Checks ends of word placed if any letters are there
            connectsToLetter = true;
        } 
        if((x > 0 && isLetter(immutableRows[x-1][y])) || (x < 14 && isLetter(immutableRows[x+1][y]))){//Checks above and below word placed if any letters are there
            connectsToLetter = true;
        } 
        
        letterMultiplier = 1;
        char emptyBoardChar = immutableRows[x][y];
        if(emptyBoardChar == '2'){
            letterMultiplier = 2;
        }
        else if(emptyBoardChar == '3'){
            letterMultiplier = 3;
        }
        else if(emptyBoardChar == '4'){
            wordMultiplier *= 2;
        }
        else if(emptyBoardChar == '9'){
            wordMultiplier *= 3;
        }
        
        score += scorer.getScore(rows[x][y]) * letterMultiplier;
        y++;
    }
    
    //Scores letters already on board that make the suffix
    while(y < 15 && isLetter(rows[x][y]) && rows[x][y] == immutableRows[x][y] ){
        score += scorer.getScore(rows[x][y]);
        y++;
    }
    
    if(!connectsToLetter){
        return 0;
    }
    
    return score * wordMultiplier;
}

int Board::scoreVerticalWord(int x,int y){
    int score = 0;
    int wordMultiplier = 1;
    int letterMultiplier = 1;
    bool connectsToLetter = false;
    
    
    //Goes up to end of board or last letter
    while(x > 0 && isLetter(rows[x][y])){
        x--;
    }
    
    //Corrects off by one error
    if( x < 15 && !isLetter(rows[x][y])){
        x++;
    }
    
    //Scores letters already on board that make the prefix
    while(x < 15 && rows[x][y] == immutableRows[x][y]){
        score += scorer.getScore(rows[x][y]);
        x++;
    }
    
    while(x < 15 && rows[x][y] != immutableRows[x][y]){
        if((y > 0 && isLetter(immutableRows[x][y-1])) || (y < 14 && isLetter(immutableRows[x][y+1]))){//Checks ends of word placed if any letters are there
            connectsToLetter = true;
        } 
        if((x > 0 && isLetter(immutableRows[x-1][y])) || (x < 14 && isLetter(immutableRows[x+1][y]))){//Checks above and below word placed if any letters are there
            connectsToLetter = true;
        } 
        letterMultiplier = 1;
        char emptyBoardChar = immutableRows[x][y];
        if(emptyBoardChar == '2'){
            letterMultiplier = 2;
        }
        else if(emptyBoardChar == '3'){
            letterMultiplier = 3;
        }
        else if(emptyBoardChar == '4'){
            wordMultiplier *= 2;
        }
        else if(emptyBoardChar == '9'){
            wordMultiplier *= 3;
        }
        
        score += scorer.getScore(rows[x][y]) * letterMultiplier;
        x++;
    }
    
    //Scores letters already on board that make the suffix
    while(x < 15 && isLetter(rows[x][y]) && rows[x][y] == immutableRows[x][y] ){
        score += scorer.getScore(rows[x][y]);
        x++;
    }
    
    if(!connectsToLetter){
        return 0;
    }
       
    return score * wordMultiplier;
}

int Board::scoreMove(int x, int y, bool horizontal){
    int score = 0;
    
    if(horizontal){
        score += scoreHorizontalWord(x,y);
         while(y < 15 && rows[x][y] != immutableRows[x][y]){
             if((x > 0 && isLetter(rows[x-1][y])) || (x < 14 && isLetter(rows[x+1][y]))){ //If there is a letter below or above the letter
                score += scoreVerticalWord(x,y);
             }
             y++;
         }
    }
    else{
        score += scoreVerticalWord(x,y);
        while(x < 15 && rows[x][y] != immutableRows[x][y]){
            if((y > 0 && isLetter(rows[x][y-1])) || (y < 14 && isLetter(rows[x][y+1]))){//If there is a letter to the left or the right of the letter
                score += scoreHorizontalWord(x,y);
            }
            x++;
        }
    }
    return score;
}


void Board::print(){
    for (int i = 0; i < 15; i++) {
        std::cout << rows[i] << std::endl;
    }
}