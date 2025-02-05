#ifndef BIQUADRIS_LEVEL2_H
#define BIQUADRIS_LEVEL2_H
#include "../Level.h"

class Level2 : public Level{
private:
    void getBlocks() override;
public:
    Level2();
    ~Level2() override;
};

#endif //BIQUADRIS_LEVEL2_H
