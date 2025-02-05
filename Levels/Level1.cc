#include "Level1.h"

Level1::Level1() : Level(1) {}

Level1::~Level1() {}

void Level1::getBlocks() {
    for (int i = 0; i < bufferSize; ++i) {
        int random = rand() % 12;
         if (random < 1) {
             blocks.push_back("S");
         } else if (random < 2) {
             blocks.push_back("Z");
         } else if (random < 4) {
             blocks.push_back("T");
         } else if (random < 6) {
             blocks.push_back("O");
         } else if (random < 8) {
             blocks.push_back("L");
         } else if (random < 10) {
             blocks.push_back("J");
         } else {
             blocks.push_back("I");
         }
    }
}
