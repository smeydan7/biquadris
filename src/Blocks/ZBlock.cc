#include "ZBlock.h"

ZBlock::ZBlock(int level) : Block('Z', level) {
    lower_left = Posn{3, 0};
    top_right = Posn{2,2};
    points = {Posn{2, 0}, Posn{2, 1}, Posn{3, 1}, Posn{3, 2}};
}

ZBlock::~ZBlock() {}
string ZBlock::toString() {
    return "ZZ\n ZZ";
}