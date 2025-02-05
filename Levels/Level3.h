#ifndef BIQUADRIS_LEVEL3_H
#define BIQUADRIS_LEVEL3_H
#include "../Level.h"
#include <iostream>
#include <fstream>
#include <string>

class Level3 : public Level{
private:
    void getBlocks() override;
    bool random;
    string inputFile;
public:
    void setRandomFile(bool rnd, string file);
    Level3();
    ~Level3() override;
};

#endif //BIQUADRIS_LEVEL3_H
