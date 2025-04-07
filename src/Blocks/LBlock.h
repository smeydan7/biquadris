#ifndef BIQUADRIS_LBLOCK_H
#define BIQUADRIS_LBLOCK_H
#include "../core/Block.h"

class LBlock : public Block {
public:
    LBlock(int level);
    ~LBlock() override;
    string toString() override;
};


#endif
