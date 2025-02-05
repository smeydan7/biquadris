#include <iostream>
#include <fstream>
#include <string>
#include "Level0.h"

using namespace std;

Level0::Level0(string inputFile) : Level(0), inputFile{inputFile} {}

Level0::~Level0() {}

void Level0::getBlocks() {
    ifstream f{inputFile};
    string temp;
    while (f >> temp) blocks.push_back(temp);
}
