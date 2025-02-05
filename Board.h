#ifndef BIQUADRIS_BOARD_H
#define BIQUADRIS_BOARD_H
#include <iostream>
#include <cstdlib>
#include <vector>
#include "score.h"
#include "Level.h"
#include "Levels/Level0.h"
#include "Levels/Level1.h"
#include "Levels/Level2.h"
#include "Levels/Level3.h"
#include "Levels/Level4.h"
#include "Block.h"
#include "Blocks/IBlock.h"
#include "Blocks/JBlock.h"
#include "Blocks/LBlock.h"
#include "Blocks/OBlock.h"
#include "Blocks/SBlock.h"
#include "Blocks/ZBlock.h"
#include "Blocks/TBlock.h"
using namespace std;

class Board
{
public:
    static const int num_rows = 18;
    static const int num_cols = 11;
    Board(int startLevel, string inputFile, int highscore);
    ~Board();
    void applyEffects(string effect, string block);
    int drop();
    int moveLeft();
    int moveRight();
    int moveDown();
    bool gameOver();
    void showCurrent();
    void hideCurrent();
    int getLevel();
    void levelUp();
    void levelDown();
    int getScore();
    int getHighscore();
    void setScore(int x);  // mutator
    Block* getNext();
    char charAt(int row, int col);
    int clockwise();
    int counterClockwise();
    void changeBlock(string block);
    bool dropHeavy();
    void resetBoard();
    void changeRandom(bool rnd, string file);  // mutator
    Score* pscore;
private:
    Level* level;
    bool isBlind = false;
    bool isHeavy = false;
    string inputFile;
    vector<char*> tiles;
    vector<Block*> blocks;
    Block* current;
    Block* next;
    Block* generateBlock();
    Level* generateLevel(int level);
    int clearRows();
    
};
#endif