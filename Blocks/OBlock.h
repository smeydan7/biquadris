#ifndef BIQUADRIS_OBLOCK_H
#define BIQUADRIS_OBLOCK_H
#include "../Block.h"

class OBlock : public Block {
public:
    OBlock(int level);
    ~OBlock() override;
    string toString() override;
};


#endif
