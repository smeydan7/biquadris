#include "Level.h"
using namespace std;

// File does not include most functions as they are level-specific
Level::Level(int level) : level{level}, turns{-2} {};
Level::~Level() {}

Block* Level::getBlock(string c) {
    if (c == "Z") return new ZBlock(level);
    else if (c == "I") return new IBlock(level);
    else if (c == "J") return new JBlock(level);
    else if (c == "L") return new LBlock(level);
    else if (c == "O") return new OBlock(level);
    else if (c == "S") return new SBlock(level);
    else return new TBlock(level);
}
Block* Level::nextBlock() {
    if (blocks.empty()) {
        getBlocks();
    }
    string c = blocks.front();
    blocks.erase(blocks.begin());
    Block* b = getBlock(c);
    ++turns;
    return b;
}
int Level::getLevel() {
    return level;
}
int Level::getTurns() {
    return turns;
}
