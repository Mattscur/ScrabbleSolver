#ifndef SCRABBLEMOVE
#define SCRABBLEMOVE

#include <string>

class ScrabbleMove{
    public:
    std::string word;
    int x;
    int y;
    int score;
    bool horizontal;
    ScrabbleMove(std::string word, int x, int y, bool horizontal, int score);
    ScrabbleMove();
    int compare(ScrabbleMove otherMove);
    std::string toString();
};
#endif