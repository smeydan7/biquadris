#include "OBlock.h"

OBlock::OBlock(int level) : Block('O', level) {
    lower_left = Posn{3, 0};
    top_right = Posn{2,1};
    points = {Posn{2, 0}, Posn{2, 1}, Posn{3, 0}, Posn{3, 1}};
}

OBlock::~OBlock() {}
string OBlock::toString() {
    return "OO\nOO";
}