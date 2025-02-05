#include "JBlock.h"

JBlock::JBlock(int level) : Block('J', level) {
    lower_left = Posn{3, 0};
    top_right = Posn{2,2};
    points = {Posn{2, 0}, Posn{3, 0}, Posn{3, 1}, Posn{3, 2}};
}

JBlock::~JBlock() {}
string JBlock::toString() {
    return "J\nJJJ";
}