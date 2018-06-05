#include "ScrabbleScorer.h"

ScrabbleScorer::ScrabbleScorer(){
    scores = new int[26];
    scores[0] = 1;
    scores[1] = 3;
    scores[2] = 3;
    scores[3] = 2;
    scores[4] = 1;
    scores[5] = 4;
    scores[6] = 2;
    scores[7] = 4;
    scores[8] = 1;
    scores[9] = 8;
    scores[10] = 5;
    scores[11] = 1;
    scores[12] = 3;
    scores[13] = 1;
    scores[14] = 1;
    scores[15] = 3;
    scores[16] = 10;
    scores[17] = 1;
    scores[18] = 1;
    scores[19] = 1;
    scores[20] = 1;
    scores[21] = 4;
    scores[22] = 4;
    scores[23] = 8;
    scores[24] = 4;
    scores[25] = 10;
}

int ScrabbleScorer::getScore(char letter){
    int index = letter-65;
    if ((index < 0) || (index > 25))
        return 0;
    return scores[index];
}