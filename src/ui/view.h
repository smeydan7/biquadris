#ifndef _VIEW_H_
#define _VIEW_H_
#include <iostream>
#include <memory>
#include "window.h"
#include "Board.h"
#include "Level.h"


using namespace std;

class Game;

class View {
    std::unique_ptr<Xwindow> xw = nullptr;
    vector<char*> previous_1;   // for player 1
    vector<char*> previous_2;   // for player 2
    int level_p1 = -1;
    int level_p2 = -1;
    int score_p1 = -1;
    int score_p2 = -1;
    int end_count = 1;
public:
    View();
    ~View();
    void endGame(Game* game);
    void fillPosn(char c, int x, int y, int width);
    void notify(Board* board, int adjustment, int number);
    // number is player number  
    vector<char*>& getPrevious(int x);  // mutate vector
    int& getLevel(int x);  // mutate level
    int& getScore(int x);  // mutate score
    int high_score = -1;
    void high(int x);
};



#endif

