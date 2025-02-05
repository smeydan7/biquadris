#include "IBlock.h"

IBlock::IBlock(int level) : Block('I', level) {
    lower_left = Posn{3, 0};
    top_right = Posn{3,3};
    points = {Posn{3, 0}, Posn{3, 1}, Posn{3, 2}, Posn{3, 3}};
}

IBlock::~IBlock() {}
string IBlock::toString() {
    return "\n IIII";
}
