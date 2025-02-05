#include "Board.h"

Board::Board(int startLevel, string inputFile, int highscore) : inputFile{inputFile}{
    for (int row = 0; row < Board::num_rows; ++row) {
        char* r = new char[Board::num_cols];
        for (int col = 0; col < Board::num_cols; ++col) {
            r[col] = ' ';
        }
        tiles.push_back(r);
    }
    pscore = new Score(highscore);
    level = generateLevel(startLevel);
    current = generateBlock();
    next = generateBlock();
}
Board::~Board() {
    delete current;
    delete next;
    delete level;
    delete pscore;
    current = nullptr;
    next = nullptr;
    level = nullptr;
    pscore = nullptr;

    for (char* tile : tiles) {
        delete [] tile;  // Use delete[] to delete C-style strings
        tile = nullptr;
    }
    tiles.clear();  // Clear the vector to release its memory

    
    for (auto p:blocks) {
        delete p;
    }
}

int Board::moveDown() {
    // cout << "reached" << endl;
    bool canMove = true;
    int failed = 1;
    for (int i = 0; i < 4; ++i) {
        canMove = canMove && (current->tileRow(i) < Board::num_rows - 1) && (tiles[current->tileRow(i) + 1][current->tileCol(i)] == ' ');
    }
    if (canMove) {
        failed = 0;
        for (int i = 0; i < 4; ++i) {
            ++current->tileRow(i);
        }
        current->update_points("down");
    }
    return failed;
}

int Board::moveLeft() {
    bool canMove = true;
    int failed = 1;
    for (int i = 0; i < 4; ++i) {
        canMove = canMove && (current->tileCol(i) > 0) && (tiles[current->tileRow(i)][current->tileCol(i) - 1] == ' ');
    }
    if (canMove) {
        failed = 0;
        for (int i = 0; i < 4; ++i) {
            --current->tileCol(i);
        }
        current->update_points("left");
    }
    if (level->getLevel() == 3 || level->getLevel() == 4){
        moveDown();
    }
    return failed;
}

int Board::moveRight() {
    bool canMove = true;
    int failed = 1;
    for (int i = 0; i < 4; ++i) {
        canMove = canMove && (current->tileCol(i) < Board::num_cols - 1) && (tiles[current->tileRow(i)][current->tileCol(i) + 1] == ' ');
    }
    if (canMove) {
        failed = 0;
        for (int i = 0; i < 4; ++i) {
            ++current->tileCol(i);
        }
        current->update_points("right");
    }
    if (level->getLevel() == 3 || level->getLevel() == 4){
        moveDown();      
    }
    return failed;
}

int Board::clockwise() {
    current->rotateCW(1);  // 1 is true, clockwise
    if (level->getLevel() == 3 || level->getLevel() == 4){
        moveDown();
    }
    return 1;
}

int Board::counterClockwise() {
    current->rotateCW(0);  // 0 is false, counter-clockwise
    if (level->getLevel() == 3 || level->getLevel() == 4){
        moveDown();
    }
    return 1;
}

int Board::drop() {
    while (!moveDown()) {}
    for (int i = 0; i < 4; ++i) {
        tiles[current->tileRow(i)][current->tileCol(i)] = current->getType();
    }
    blocks.push_back(current);
    current = next;
    next = generateBlock();
    int rowsCleared = 0;
    rowsCleared += clearRows();
    if (level->getLevel() == 4 && level->getTurns() % 5 == 0) {
        int dropRow = 2;
        while (dropRow + 1 < Board::num_rows && tiles[dropRow + 1][Board::num_cols / 2] == ' ') {
            ++dropRow;
        }
        tiles[dropRow][Board::num_cols / 2] = '*';
        rowsCleared += clearRows();
    }
    isBlind = false;
    isHeavy = false;
    return rowsCleared;
}
bool Board::gameOver() {
   for (int i = 0; i < 4; ++i) {
       if (tiles[current->tileRow(i)][current->tileCol(i)] != ' ') {
           return true;
       }
   }
   return false;
}
void Board::showCurrent() {
    for (int i = 0; i < 4; ++i) {
        tiles[current->tileRow(i)][current->tileCol(i)] = current->getType();
    }
}
void Board::hideCurrent() {
    for (int i = 0; i < 4; ++i) {
        tiles[current->tileRow(i)][current->tileCol(i)] = ' ';
    }
}
int Board::getLevel() {
    return level->getLevel();
}
int Board::getScore() {
    return pscore->getScore();
}

void Board::setScore(int x) {
    pscore->updateScore(x);
}

Block* Board::getNext() {
    return next;
}
char Board::charAt(int row, int col) {
    return (isBlind && (row + 1) >= 3
                    && (row + 1) <= 12
                    && (col + 1) >= 3
                    && (col + 1) <= 9) ? '?' : tiles[row][col];
}
Block* Board::generateBlock() {
    return level->nextBlock();
}
Level* Board::generateLevel(int level) {
    if (level == 0) {
        return new Level0(inputFile);
    } else if (level == 1) {
        return new Level1();
    } else if (level == 2) {
        return new Level2();
    } else if (level == 3) {
        return new Level3();
    } else if (level == 4) {
        return new Level4();
    } else {
        return this->level;
    }
}

void Board::levelUp() {
    int lev_num = level->getLevel() + 1;
    delete level;   // free old memory
    level = generateLevel(lev_num);
}

void Board::levelDown() {
    int lev_num = level->getLevel() - 1;
    delete level;
    level = generateLevel(lev_num);    
}

void Board::changeRandom(bool rnd, string file) {
    if (getLevel() == 3) {  // know with certainty
        Level3 *lev = static_cast<Level3 *>(level);  // downcast
        lev->setRandomFile(rnd, file);
        this->level = static_cast<Level *>(lev); // upcasting
    } else if (getLevel() == 4) {
        Level4 *lev = static_cast<Level4 *>(level);
        lev->setRandomFile(rnd, file); 
        this->level = static_cast<Level *>(lev); // upcasting
    }
}

int Board::clearRows() {
    int rowsCleared = 0;
    int rowNum = 0;
    for (auto it = tiles.begin(); it != tiles.end();) {
        char* row = *it;
        bool isFull = true;
        for (int i = 0; i < Board::num_cols; ++i) {
            isFull = isFull && (row[i] != ' ');
        }
        if (isFull) {
            for (auto b = blocks.begin(); b != blocks.end(); ++b) {
               for (int i = 0; i < 4; ++i) {
                   if ((*b)->tileRow(i) == rowNum) {
                       (*b)->tileRow(i) = -1;
                   } else if((*b)->tileRow(i) != -1 && (*b)->tileRow(i) < rowNum) {
                       ++(*b)->tileRow(i);
                   }
               }
            }
            it = tiles.erase(it);
            ++rowsCleared;
        } else {
            ++it;
        }
        ++rowNum;
    }
    for (int i = 0; i < rowsCleared; ++i) {
        char* row = new char[Board::num_cols];
        for (int j = 0; j < Board::num_cols; ++j) row[j] = ' ';
        tiles.insert(tiles.begin(), row);
    }
    if (rowsCleared > 0) {
        pscore->lineCleared(level->getLevel(), rowsCleared);
    }
    for (auto b = blocks.begin(); b != blocks.end();) {
        bool clearBlock = true;
        for (int i = 0; i < 4; ++i) {
            clearBlock = clearBlock && ((*b)->tileRow(i) == -1);
        }
        if (clearBlock) {
            pscore->blockRemoved((*b)->getLevel());
            delete (*b);
            b = blocks.erase(b);
        } else {
            ++b;
        }
    }
    return rowsCleared;
}
void Board::changeBlock(std::string block) {
    hideCurrent();
    delete current;   // free old
    current = nullptr; // Reassign to nullptr
    current = level->getBlock(block);
    showCurrent();
}
void Board::applyEffects(std::string effect, std::string block) {
    if (effect == "blind") {
        isBlind = true;
    } else if (effect == "heavy") {
        isHeavy = true;
    } else if (effect == "force") {
        changeBlock(block);
    }
}
bool Board::dropHeavy() {
    return isHeavy && (moveDown() || moveDown());
}

void Board::resetBoard() {
    pscore->restartGame();
    hideCurrent();
    delete current;   // free old
    current = nullptr; // Reassign to nullptr 
    current = generateBlock(); // keep next since didn't specify
    
    for (char* tile : tiles) {
        delete [] tile;  // Use delete[] to delete C-style strings
        tile = nullptr;
    }

    tiles.clear();  // Clear the vector to release its memory
    for (int row = 0; row < Board::num_rows; ++row) {
        char* r = new char[Board::num_cols];
        for (int col = 0; col < Board::num_cols; ++col) {
            r[col] = ' ';
        }
        tiles.push_back(r);
    }
}
int Board::getHighscore() {
    return pscore->getHiScore();
}