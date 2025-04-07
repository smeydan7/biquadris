#include "SBlock.h"

SBlock::SBlock(int level) : Block('S', level) {
    lower_left = Posn{3, 0};
    top_right = Posn{2,2};
    points = {Posn{2, 1}, Posn{2, 2}, Posn{3, 0}, Posn{3, 1}};
}

SBlock::~SBlock() {}
string SBlock::toString() {
    return " SS\nSS";
}