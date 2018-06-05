#ifndef SCRABBLESCORER
#define SCRABBLESCORER

class ScrabbleScorer{
  private:
  int* scores;
  public:
  ScrabbleScorer();
  int getScore(char letter);
};


#endif