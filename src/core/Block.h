#ifndef BIQUADRIS_BLOCK_H
#define BIQUADRIS_BLOCK_H
#include <string>
#include <vector>
#include "Position.h"
using namespace std;


class Block {
private:
    char c;
    int level;
protected:
    vector<Posn> points;
    Posn lower_left;  // lower left of the smallest rectangle containing the block
    Posn top_right;   // top right of the smallest rectangle containing the block
	public:
        Block(char c, int level) : c{c}, level{level} {}
		virtual ~Block() {}
        virtual string toString() = 0;
        void update_points(string dir);
        void rotateCW(int dir);
        char getType() {
            return c;
        }
        int getLevel() {
            return level;
        }
        int& tileRow(int i) {
            return points[i].x;
        }
        int& tileCol(int i) {
            return points[i].y;
        }
        void LowerL_and_TopR();
};
#endif