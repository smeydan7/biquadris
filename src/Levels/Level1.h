#ifndef BIQUADRIS_LEVEL1_H
#define BIQUADRIS_LEVEL1_H
#include "../Level.h"

class Level1 : public Level{
private:
    void getBlocks() override;
public:
    Level1();
    ~Level1() override;
};

#endif //BIQUADRIS_LEVEL1_H
