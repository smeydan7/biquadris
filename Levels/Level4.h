#ifndef BIQUADRIS_LEVEL4_H
#define BIQUADRIS_LEVEL4_H
#include "../Level.h"
#include <iostream>
#include <fstream>
#include <string>
class Level4 : public Level{
private:
    void getBlocks() override;
    bool random = true;
    string inputFile;
public:
    void setRandomFile(bool rnd, string file);
    Level4();
    ~Level4() override;
};

#endif //BIQUADRIS_LEVEL4_H
