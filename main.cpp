#include <bitset>
#include <ctime>
#include <string>
#include <iostream>
#include <fstream>
#include <assert.h>
#include "Trie.h"
#include "Dictionary.h"
#include "Board.h"
#include "ScrabbleSolver.h"

using namespace std;

void topTwentyTester(std::string file){
    ScrabbleSolver s = ScrabbleSolver(file);

    std::cout << "Board is as follows: " << std::endl;
    s.currentBoard.print();

    std::cout << std::endl << std::endl << "Rack is: " << s.currentRack << std::endl << std::endl << std::endl;
    
    
    std::cout << "Top twenty moves are: " << std::endl;
    std::cout << s.getTopTwenty() << std::endl;    
    
}

void timedTester(int numTrials){
    ScrabbleSolver s = ScrabbleSolver();
    std::cout << "Starting timing." << std::endl;
    clock_t begin = clock();
    for (int i = 0; i < numTrials; i++) {
        s.getTopTwenty();
    }
    clock_t end = clock();
    double timeSec = (end - begin) / static_cast<double>( CLOCKS_PER_SEC );
    std::cout << "It took " << timeSec << " seconds. It took " << timeSec/numTrials <<  " seconds on average" << std::endl;
}


 
int main(){
    int input;
    std::cout << "1: Get top twenty moves for board in board.txt" << std::endl;
    std::cout << "2: Get average time to compute top twenty moves." << std::endl;
    std::cout << "3: Get top twenty moves for board in specified board." << std::endl;
    std::cout << "Please make selection: " << std::endl;
    
    while(true){
        std::cin >> input;
        if(input == 1){
            topTwentyTester("board.txt");
            break;
        }
        else if(input == 2){
            int numTrials = 0;
            std::cout << "Please enter number of trials " << std::endl;
            while(true){
                std::cin >> numTrials;
                if(numTrials < 1){
                    std::cout << "Please enter a positive number. " << std::endl;
                    continue;
                }
                break;
            }
            timedTester(numTrials);
            break;
        }
        else if(input == 3){
            std::string fileName = "";
            std::cout << "Enter file name: " << std::endl;
            std::cin >> fileName;
            topTwentyTester(fileName);
            break;
        }
        std::cout << "Invalid input. Please try again: " << std::endl;
    }
    return 0;
}