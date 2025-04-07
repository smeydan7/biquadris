#include "score.h"
#include <iostream>
using namespace std;

Score::Score(int existingHiScore) : playerScore{0} {
    existingHiScore = existingHiScore;
}

void Score::lineCleared(int level, int numLines) { 
    int points = (level + numLines) * (level + numLines);
    updateScore(points);
    updateHiScore();
}
    
void Score::blockRemoved(int level) {
    int points = (level + 1) * (level + 1);
    updateScore(points);
    updateHiScore();
} 

void Score::updateScore(int value) { playerScore += value; }

void Score::restartGame() { 
    playerScore = 0;
}

int Score::getScore() { return playerScore; }
int Score::getHiScore() { return existingHiScore; }

void Score::updateHiScore() {
    if (playerScore > existingHiScore) existingHiScore = playerScore;
}