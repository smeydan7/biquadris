#include "Level2.h"

Level2::Level2() : Level(2) {}

Level2::~Level2() {}

void Level2::getBlocks() {
    for (int i = 0; i < bufferSize; ++i) {
        int random = rand() % 7;
        if (random == 0) {
            blocks.push_back("S");
        } else if (random == 1) {
            blocks.push_back("Z");
        } else if (random == 2) {
            blocks.push_back("T");
        } else if (random == 3) {
            blocks.push_back("O");
        } else if (random == 4) {
            blocks.push_back("L");
        } else if (random == 5) {
            blocks.push_back("J");
        } else {
            blocks.push_back("I");
        }
    }
}
