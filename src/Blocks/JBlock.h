#ifndef BIQUADRIS_JBLOCK_H
#define BIQUADRIS_JBLOCK_H
#include <vector>
#include <string>
#include "../core/Block.h"

class JBlock : public Block {
public:
    JBlock(int level);
    ~JBlock() override;
    string toString() override;
};


#endif
