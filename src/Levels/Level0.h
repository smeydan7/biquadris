#ifndef BIQUADRIS_LEVEL0_H
#define BIQUADRIS_LEVEL0_H

#include <iostream>
#include <string>
#include <fstream>
#include "../Level.h"
using namespace std;

class Level0 : public Level {
private:
    string inputFile;
    void getBlocks() override;
public:
    Level0(string inputFile);
    ~Level0() override;
};

#endif
