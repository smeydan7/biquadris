#ifndef BIQUADRIS_ZBLOCK_H
#define BIQUADRIS_ZBLOCK_H
#include "../Block.h"

class ZBlock : public Block {
public:
    ZBlock(int level);
    ~ZBlock() override;
    string toString() override;
};


#endif
