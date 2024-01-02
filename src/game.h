#pragma once
#include "grid.h"
#include "blocks.cpp"
using namespace std;

class Game{
public:
    Game(); //default constructor
    ~Game();
    void Draw();
    void HandleInput();
    void MoveBlockDown();
    bool gameOver;
    int score;
    double speed;
    int level;

private:
    Block GetRandomBlock();
    vector<Block> GetAllBlocks();
    void MoveBlockLeft();
    void MoveBlockRight();
    bool IsBlockOutside();
    void RotateBlock();
    void LockBlock();
    bool BlockFits();
    void Reset();
    void UpdateScore(int linesCleared, int moveDownPoints);
    void UpdateLevel(int score, int &level);
    Grid grid;
    vector<Block> blocks;
    Block currentBlock;
    Block nextBlock;
    Sound rotateSound;
    Sound clearSound;
};