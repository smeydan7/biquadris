#include "TBlock.h"

TBlock::TBlock(int level) : Block('T', level) {
    lower_left = Posn{3, 0};
    top_right = Posn{2,2};
    points = {Posn{2, 0}, Posn{2, 1}, Posn{2, 2}, Posn{3, 1}};
}
TBlock::~TBlock() {}
string TBlock::toString() {
    return "TTT\n T ";
}