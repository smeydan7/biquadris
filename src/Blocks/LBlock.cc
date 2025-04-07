#include "LBlock.h"

LBlock::LBlock(int level) : Block('L', level) {
    lower_left = Posn{3, 0};
    top_right = Posn{2,2};
    points = {Posn{2, 2}, Posn{3, 0}, Posn{3, 1}, Posn{3, 2}};
}

LBlock::~LBlock() {}
string LBlock::toString() {
    return "  L\nLLL";
}