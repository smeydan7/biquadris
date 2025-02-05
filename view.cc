#include "view.h"
#include "Game.h"
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>
#include "sstream"
#include <iomanip>
#include <vector>
#include "Position.h"
#include "window.h"
#include "score.h"
using namespace std;

const int numRows = 18;
const int numCols = 11;

View::View(): xw{nullptr} {
    // 1st para is col, 2nd para is row
    xw = make_unique<Xwindow>(1080, 800);
    xw->fillRectangle(0, 0, 1080, 800, Xwindow::Black);
    xw->drawString(460, 50, "BIQUADRIS", Xwindow::White);
    xw->drawString(100, 66, "LEVEL:",Xwindow::White);  
    xw->drawString(550, 66, "LEVEL:",Xwindow::White);
    xw->drawString(100, 88, "SCORE:",Xwindow::White);
    xw->drawString(550, 88, "SCORE:",Xwindow::White);
    xw->drawString(100, 666, "NEXT:", Xwindow::White);
    xw->drawString(550, 666, "NEXT:", Xwindow::White);  
    for (int row = 0; row < Board::num_rows; ++row) {
        char* r = new char[Board::num_cols];
        char* s = new char[Board::num_cols];
        for (int col = 0; col < Board::num_cols; ++col) {
            r[col] = '?';   // on purpose
            s[col] = '?';   // on purpose
        }
        previous_1.push_back(r);
        previous_2.push_back(s);
    }    
    // high(0);
}


View::~View() {
    for (char* tile : previous_1) {
        delete [] tile;  // Use delete[] to delete C-style strings
        tile = nullptr;
    }
    previous_1.clear();  // Clear the vector to release its memory

    for (char* tile : previous_2) {
        delete [] tile;  // Use delete[] to delete C-style strings
        tile = nullptr;
    }
    previous_2.clear();  // Clear the vector to release its memory    
}
int& View::getLevel(int x) {
    if (x) {  // zero is false
        return level_p2;  // player 2
    } 
    return level_p1;    // zero is player 1
}

int& View::getScore(int x) {
    if (x) {  
        return score_p2;  
    } 
    return score_p1;    
}

vector<char*>& View::getPrevious(int x) {
    if (x) {  // zero is false
        return previous_2;  // player 2
    } 
    return previous_1;    // zero is player 1
}

void View::fillPosn(char c, int x, int y, int width) {
    int color = 0;
    if (c == ' ') {
        color = 0;
    } else if (c == 'I') {
        color = 9;       // don't use black
    } else if (c == 'J') {
        color = 2;
    } else if (c == 'L') {
        color = 3;
    } else if (c == 'O') {
        color = 4;
    } else if (c == 'S') {
        color = 5;
    } else if (c == 'Z') {
        color = 6;
    } else if (c == 'T') {
        color = 7;
    } else if (c == '*') {
        color = 9;  // brown
    } else {
        color = 1;
    }                            
    xw->fillRectangle(100+x*30, 100+y*30, width, width, color);
}

void View::notify(Board* board, int adj, int number) {
    vector<char*> &previous = getPrevious(number);  // zero is player 1
    int &level = getLevel(number);
    int &score = getScore(number);
    Block* n = board->getNext();
    char c = n->getType();
    int x, y;

    if (end_count <= 0) {
        xw->fillRectangle(888, 20, 190, 80, Xwindow::Black); // cover end game
        end_count = 1;   // 1 is equilb
    } 
    if (end_count > 1) {
        --end_count;
        if (end_count == 1) {
            end_count = 0;
        }
    }

    if (board->getLevel() != level) {
        level = board->getLevel();
        if (number) {   // player 2
            xw->fillRectangle(593, 53, 20, 20, Xwindow::Black);
            xw->drawString(600, 66, to_string(level),Xwindow::White);  
        } else {
            xw->fillRectangle(143, 53, 20, 20, Xwindow::Black);
            xw->drawString(150, 66, to_string(level),Xwindow::White);
        }               
    }

    if (board->getScore() != score) {
        score = board->getScore();
        if (number) {
            xw->fillRectangle(593, 75, 20, 20, Xwindow::Black);
            xw->drawString(600, 88, to_string(score),Xwindow::White);   
        } else {
            xw->fillRectangle(143, 75, 20, 20, Xwindow::Black);
            xw->drawString(150, 88, to_string(score),Xwindow::White);
        }      
    }
    for (int row = 0; row < Board::num_rows; ++row) {
        for (int col = 0; col < Board::num_cols; ++col) {
            char upd = board->charAt(row, col);
            char org = previous[row][col];
            if (upd != org) {
                fillPosn(upd, col+adj, row, 26);
                previous[row][col] = upd;
            }
        }
    }
    xw->fillRectangle(100+adj*30, 670, 120, 80, Xwindow::Black);  // cover
    for (int i = 0; i < 4; ++i) {
        x = n->tileRow(i)+17;
        y = n->tileCol(i);
        fillPosn(c, y+adj, x, 26);
    }
}

void View::high(int x) {
    if (x != high_score) {
        high_score = x;  // update highscore
        cout << "inside view hi is " << high_score << endl;
        xw->fillRectangle(863, 38, 20, 15, Xwindow::Black); // cover hi
        xw->drawString(795, 50, "High score: " + to_string(high_score), Xwindow::Orange);
    }
}

void View::endGame(Game* game) {
    end_count = 3;
    string winner;
    if (score_p1 > score_p2) {
        winner = "Congratulations! Player 1 Wins.";
    }
    else if ( score_p1 < score_p2) {
        winner = "Congratulations! Player 2 Wins!";
    }
    else {
        winner = "Tie Game!";
    }
    
    xw->drawString(890, 50,"Player 1 highest score: " + to_string(score_p1), Xwindow::Orange);
    xw->drawString(890, 70,"Player 2 highest score: " + to_string(score_p2), Xwindow::Orange);
    xw->drawString(890, 90, winner, Xwindow::Orange);
}

