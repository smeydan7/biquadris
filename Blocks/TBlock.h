#ifndef BIQUADRIS_TBLOCK_H
#define BIQUADRIS_TBLOCK_H
#include "../Block.h"

class TBlock : public Block {
public:
    TBlock(int level);
    ~TBlock() override;
    string toString() override;
};


#endif
