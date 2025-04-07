#ifndef BIQUADRIS_LEVEL_H
#define BIQUADRIS_LEVEL_H

#include <iostream>
#include <string>
#include <vector>
#include "Block.h"
#include "Blocks/IBlock.h"
#include "Blocks/JBlock.h"
#include "Blocks/LBlock.h"
#include "Blocks/OBlock.h"
#include "Blocks/SBlock.h"
#include "Blocks/ZBlock.h"
#include "Blocks/TBlock.h"
using namespace std;

class Level {
private:
    int level;
    int turns;
    virtual void getBlocks() = 0;
protected:
    int bufferSize = 10;
    vector<string> blocks;
public:
    Level(int level);
    virtual ~Level();
    Block* nextBlock();
    Block* getBlock(string c);
    int getLevel();
    int getTurns();
};

#endif
