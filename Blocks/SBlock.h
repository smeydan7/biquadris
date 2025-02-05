#ifndef BIQUADRIS_SBLOCK_H
#define BIQUADRIS_SBLOCK_H
#include "../Block.h"

class SBlock : public Block {
public:
    SBlock(int level);
    ~SBlock() override;
    string toString() override;
};


#endif
