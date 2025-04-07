#include "Game.h"

Game::Game(bool withGraphics, int startLevel, unsigned int seed, string inputFiles[2]) : 
    withGraphics{withGraphics}, startLevel{startLevel}, inputFiles{inputFiles[2]} {
    srand(seed);
    if (withGraphics) {
        view = new View{};
    }
    for (int i = 0; i < 50; ++i) {
        rand();
    }
    for (int i = 0; i < 2; ++i) players[i] = new Board(startLevel, inputFiles[i], highscore);
}
Game::~Game() {
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }
    delete view;
}
void Game::switchPlayer() {
    playerTurn = (playerTurn + 1) % 2;
}

void Game::print() {
    cout << endl;
    cout << "Level:" << right << setw(5) << players[0]->getLevel() << left << "     ";
    cout << "Level:" << right << setw(5) << players[1]->getLevel() << left << endl;
    cout << "Score:" << right << setw(5) << players[0]->getScore() << left << "     ";
    cout << "Score:" << right << setw(5) << players[1]->getScore() << left << endl;
    if (playerTurn) {
        cout << "-----------     ***********" << endl;
    } else {
        cout << "***********     -----------" << endl;
    }
    for (int i = 0; i < 2; ++i) {
        players[i]->showCurrent();
    }
    for (int row = 0; row < Board::num_rows; ++row) {
        for (int col = 0; col < Board::num_cols; ++col) {
            cout << players[0]->charAt(row, col);
        }
        cout << "     ";
        for (int col = 0; col < Board::num_cols; ++col) {
            cout << players[1]->charAt(row, col);
        }
        cout << endl;
    }

    if (playerTurn) {
        cout << "-----------     ***********" << endl;
    } else {
        cout << "***********     -----------" << endl;
    }
    cout << setw(Board::num_cols) << "Next:" << "     ";
    cout << setw(Board::num_cols) << "Next:" << endl;
    istringstream iss1{players[0]->getNext()->toString()};
    istringstream iss2{players[1]->getNext()->toString()};
    for (int i = 0; i < 2; ++i) {
        string s1, s2;
        getline(iss1, s1);
        getline(iss2, s2);
        cout << setw(11) << s1 << "     " << setw(11) << s2 << endl;
    }

    if (withGraphics) {
        view->notify(getPlayer_1(), 0, 0);   // windows
        view->notify(getPlayer_2(), 15, 1);   // windows
    }

    for (int i = 0; i < 2; ++i) {
        players[i]->hideCurrent();
    }
}

void Game::restart(int turn) {
    players[turn]->resetBoard();
    // if (withGraphics) {
    //     view->high(highscore);
    // }
}

void Game::processCommands(std::istream &in, TrieNode* trie, Board* player) {
    string command, arg, prev_cmd;
    while (in >> command) {
        int x = 1;
        if (istringstream iss{command}; iss >> x) {
            iss >> command;   // multiplier prefix
        } else {  // no multiplier prefix
            x = 1; // default is 1
        }

        if (command == "I" || command == "J" || command == "L" || command == "O"
            || command == "S" || command == "Z" || command == "T") {
            player->changeBlock(command);   // Capital case
            prev_cmd = command;
            print();
            continue;   // next ieration
        } 
        // handles invalid input
        for (char c : command) {  
            if (c < 'a' || c > 'z') {
                command = ""; // If any character is not a lowercase letter
                cout << "Oops! Invalid input." << endl;
            }  
        }        

        command = trie->find(command);   
        
        if (command == "p") {   // extra feature
            command = prev_cmd;
        }
        if (command == "sequence") {
            in >> arg;  // read file name
            std::ifstream fileIn{arg};
            processCommands(fileIn, trie, player);
        } else if (command == "norandom") {
            in >> arg;  // read file name
            if (player->getLevel() == 3 || player->getLevel() == 4) {
                player->changeRandom(false, arg);
            }
        } else if (command == "random") {
            if (player->getLevel() == 3 || player->getLevel() == 4) {
                player->changeRandom(true, "");
            }
        } else if (command == "restart") {
            restart(playerTurn);
            print();
        } else if (command == "q") {
            return;   // extra feature, exits the game
        } 
        for (int t = 0; t < x; ++t) {   // multiplier prefix
            if (command == "drop") {
                if (player->drop() >= 2) {
                    cout << "You cleared more than 1 row on your last turn!" << endl;
                    cout << "What effect would you like to apply on player " << ((playerTurn + 1) % 2) + 1 << endl;
                    cout << "Your options are: [b]lind, [h]eavy, [f]orce" << endl;
                    string effect, block;
                    cin >> effect;
                    if (effect == "force") {
                        cout << "Choose a block, please enter I, J, L, O, S, Z, or T" << endl;
                        cin >> block;
                    }
                    players[(playerTurn + 1) % 2]->applyEffects(effect, block);
                }
                if (t == x-1) {
                    switchPlayer();
                    player = players[playerTurn];  // multiplier only affect current player
                }

            } else if (command == "left") {
                    player->moveLeft();
                    if (player->dropHeavy()) {
                        if (player->drop() >= 2) {
                            cout
                                    << "You cleared more than 1 row on your last turn! What effect would you like to apply on player "
                                    << ((playerTurn + 1) % 2) + 1 << endl;
                            cout << "your options are: [b]lind, [h]eavy, [f]orce" << endl;
                            string effect, block;
                            cin >> effect;
                            if (effect == "force") {
                                cout << "choose a block: I, J, L, etc";
                                cin >> block;
                            }
                            players[(playerTurn + 1) % 2]->applyEffects(effect, block);
                        }
                        switchPlayer();
                        player = players[playerTurn];  // change player
                    }
                } else if (command == "right") {
                    player->moveRight();
                    if (player->dropHeavy()) {
                        if (player->drop() >= 2) {
                            cout
                                    << "You cleared more than 1 row on your last turn! What effect would you like to apply on player "
                                    << ((playerTurn + 1) % 2) + 1 << endl;
                            cout << "your options are: [b]lind, [h]eavy, [f]orce" << endl;
                            string effect, block;
                            cin >> effect;
                            if (effect == "force") {
                                cout << "choose a block: I, J, L, etc" << endl;
                                cin >> block;
                            }
                            players[(playerTurn + 1) % 2]->applyEffects(effect, block);
                        }
                        switchPlayer();
                        player = players[playerTurn];  // change player
                    }
                } else if (command == "down") {
                    player->moveDown();
                } else if (command == "clockwise") {
                    player->clockwise();
                } else if (command == "counterclockwise") {
                    player->counterClockwise();
                } else if (command == "levelup") {
                    player->levelUp();
                } else if (command == "leveldown") {
                    player->levelDown();
                } 
            }
            for (int i = 0; i < 2; ++i) highscore = max(highscore, players[i]->getHighscore());
            prev_cmd = command;
            if (players[0]->gameOver() || players[1]->gameOver()) {
                endGame(std::cout);
                if (withGraphics) {
                    view->endGame(this);
                }
                restart(0);
                restart(1); // restart both
            }
            print();
    }
    endGame(std::cout);
    // cout << "Highscore: " << highscore << endl;
    if (withGraphics) {
        view->endGame(this);
    }
}

void Game::endGame(std::ostream &out) {
	// end game
    cout << "Player 1's highest score: " << players[0]->getScore() <<endl;
    cout << "Player 2's highest score: " << players[1]->getScore() <<endl;
    if ( players[0]->getScore() > players[1]->getScore()){
        cout << "Player 1 has the highest score\nThe winner is Player 1!" << endl;
    } else if (players[0]->getScore() < players[1]->getScore()){
        cout << "Player 2 has the highest score\nThe winner is Player 2!" << endl;
    } else{
        cout << "This is a tie!" << endl;
    }		    
}

void Game::play() {
    TrieNode *trie = new TrieNode;
    trie->insert_update("left");   // insertion
    trie->insert_update("right");
    trie->insert_update("down");
    trie->insert_update("clockwise");
    trie->insert_update("counterclockwise");
    trie->insert_update("drop");
    trie->insert_update("levelup");
    trie->insert_update("leveldown");
    trie->insert_update("norandom");
    trie->insert_update("random");
    trie->insert_update("sequence");
    trie->insert_update("norandom");
    trie->insert_update("random");
    trie->insert_update("restart");
    trie->insert_update("p");
    trie->insert_update("q");
    print();
    Board* player = players[playerTurn];
    processCommands(std::cin, trie, player); 

    delete trie;
}

Board* Game::getPlayer_1() {
    return players[0];
}
Board* Game::getPlayer_2() {
    return players[1];
}