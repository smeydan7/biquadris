#ifndef BIQUADRIS_GAME_H
#define BIQUADRIS_GAME_H
#include "Board.h"
#include <iomanip>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <fstream>
#include "trie.cc"
#include "ui/view.h"
using namespace std;


class Game {
private:
    Board* players[2];
    int playerTurn = 0;
    int highscore = 0;
    bool withGraphics;
    void print();
    void switchPlayer();
    int startLevel = 0;
    string inputFiles[2];
    View* view = nullptr;
public:
    Game(bool withGraphics, int startLevel, unsigned int seed, string inputFiles[2]);
    ~Game();
    void play();
    void processCommands(std::istream &in, TrieNode* trie, Board* player);
    void endGame(std::ostream &out);
    void restart(int turn);
    Board* getPlayer_1();
    Board* getPlayer_2();
};


#endif //BIQUADRIS_GAME_H
