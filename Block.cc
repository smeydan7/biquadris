#include "Block.h"
#include <algorithm>
using namespace std;

class Extreme_Right {};

void Block::update_points(std::string dir) {  // updates lower left and top right
    if (dir == "left") {
        --lower_left.y;
        --top_right.y;
    } else if (dir == "right") {
        ++lower_left.y;
        ++top_right.y;
    } else if (dir == "down") {
        ++lower_left.x;
        ++top_right.x;
    }
}

void Block::LowerL_and_TopR(){
    int size = 4;
    Posn Lower_L{points[0].x, points[0].y};
    Posn Top_R{points[0].x, points[0].y}; // initialize to be the first point

    for(int i = 1; i < size; i++) {   // start from second point
        if (points[i].x > Lower_L.x ) {
            Lower_L.x = points[i].x;   // new lower left x is found
        }
        if (points[i].y < Lower_L.y) {
            Lower_L.y = points[i].y;
        }
        if (points[i].x < Top_R.x) {
            Top_R.x = points[i].x;   // new top right y is found
        }
        if (points[i].y > Top_R.y) {
            Top_R.y = points[i].y;
        }
    }
    lower_left = Lower_L;
    top_right = Top_R;    // update the field
}

void Block::rotateCW(int dir) {
    int old_rows = lower_left.x-top_right.x+1;  // old # of rows
    int old_cols = top_right.y-lower_left.y+1;
    int new_rows = old_cols;    // new # of rows
    int new_cols = old_rows;
    vector<Posn> new_points;   // new vector

    int start_x = lower_left.x-new_rows+1;
    int end_y = lower_left.y+new_cols;
    int count = 0;
    try {
        for (int i = start_x; i <= lower_left.x; ++i) {
            int k = 0;
            for (int s = lower_left.y; s < end_y; ++s) {
                // 0 is false => represents counterclockwise
                Posn p = (dir) ? Posn{lower_left.x-k, lower_left.y+count} : 
                                 Posn{top_right.x+k, top_right.y-count};  
                if(find(points.begin(), points.end(), p) != points.end()) {
                    new_points.emplace_back(Posn{i, s});   // transformed
                }
                ++k;
            }
            ++count;
        }
    }
    catch (Extreme_Right e) {  // no horizontal room to rotate
        return;
    }
    points = new_points;
    this->LowerL_and_TopR();  // update lower left and top right of the rect
}
