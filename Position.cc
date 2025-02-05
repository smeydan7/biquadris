#include "Position.h"
#include <iostream>
#include <string>
using namespace std;
class Extreme_Right {};

Posn::Posn(int x, int y) : x{x}, y{y} {
    int num_cols = 11;
    if (y >= num_cols) {
        cout << "The block is at the extreme right-hand side of the board!" << endl;
        cout << "There is no horizontal room to rotate it." << endl;
        throw Extreme_Right{};
    } else if (y < 0) {
        cout << "The block is at the extreme left-hand side of the board!" << endl;
        cout << "There is no horizontal room to rotate it." << endl;
        throw Extreme_Right{};
    }
}

bool Posn::operator==(const Posn& other) const {
    return (x == other.x) && (y == other.y);
}

bool Posn::operator!=(const Posn& other) const {
    return !(*this == other);
}
