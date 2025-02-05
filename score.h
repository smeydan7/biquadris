#ifndef BIQUADRIS_SCORE_H
#define BIQUADRIS_SCORE_H

#include <iostream>
using namespace std;

class Score {
    int playerScore;
    int existingHiScore;
public:
    Score(int existingHiScore);
    void lineCleared(int level, int numLines); // Points = (level + #lines)^2
    void blockRemoved(int level); // Points = (level @ removal + 1)^2

    void updateScore(int value); // increments playerScore with value
    void restartGame(); // set playerScore = 0

    int getScore(); // returns current player score
    int getHiScore(); // returns current high score

    void updateHiScore(); // checks if playerScore > existingHiScore
};
#endif