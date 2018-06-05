#include <string>
#include <sstream>
#include "ScrabbleMove.h"

ScrabbleMove::ScrabbleMove(std::string word, int x, int y, bool horizontal, int score){
    this->word = word;
    this->x = x;
    this->y = y;
    this->horizontal = horizontal;
    this->score = score;
}
ScrabbleMove::ScrabbleMove(){
    this->word = "";
    this->x = -1;
    this->y = -1;
    this->horizontal = false;
    this->score = 0;
}

int ScrabbleMove::compare(ScrabbleMove otherMove){
    if(this->score == otherMove.score){
        return 0;
    }
    
    if(this->score < otherMove.score){
        return -1;
    }
    
    return 1;
}

std::string ScrabbleMove::toString(){
    std::string returnString = "";
    returnString += word;
    returnString += ", (";
    
    std::stringstream ss;//create a stringstream
    ss.str("");
    ss << x;//add number to the stream
    returnString += ss.str();//return a string with the contents of the stream
    returnString += ",";
    ss.str("");
    ss << y;
    returnString += ss.str();//return a string with the contents of the stream
    returnString += "), ";
    if(horizontal){
        returnString += "Horizontal, ";
    }
    else{
        returnString += "Vertical, ";  
    }
    ss.str("");
    ss << score;
    returnString += "Score is: ";
    returnString += ss.str();//return a string with the contents of the stream
    
    return returnString;
}