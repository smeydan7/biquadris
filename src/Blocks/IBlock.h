#ifndef BIQUADRIS_IBLOCK_H
#define BIQUADRIS_IBLOCK_H
#include "../core/Block.h"

class IBlock : public Block {
public:
    IBlock(int level);
    ~IBlock() override;
    string toString() override;
};


#endif //BIQUADRIS_IBLOCK_H
