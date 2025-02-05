#include "Level3.h"

Level3::Level3() : Level(3), random{true} {}

Level3::~Level3() {}

void Level3::setRandomFile(bool rnd, string file) { 
    random = rnd;
    inputFile = file;
}

void Level3::getBlocks() {
    if (random) {   // random is on
        for (int i = 0; i < bufferSize; ++i) {
            int random = rand() % 9;
            if (random < 2) {
                blocks.push_back("S");
            } else if (random < 4) {
                blocks.push_back("Z");
            } else if (random < 5) {
                blocks.push_back("T");
            } else if (random < 6) {
                blocks.push_back("O");
            } else if (random < 7) {
                blocks.push_back("L");
            } else if (random < 8) {
                blocks.push_back("J");
            } else {
                blocks.push_back("I");
            }
        }
    } else {
        ifstream f{inputFile};
        string temp;
        while (f >> temp) blocks.push_back(temp);
    }
}
