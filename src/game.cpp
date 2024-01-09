#include "game.h"
#include <random>
#include <unordered_map>
using namespace std;
#include <iostream>

Game::Game()
{
    grid = Grid();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    isBlockHeld = false;
    gameOver = false;
    score = 0;
    InitAudioDevice(); //sets up audio system
    rotateSound = LoadSound("sound/rotate.mp3");
    clearSound = LoadSound("sound/clear.mp3");
    speed = 0.3;
    level = 1;
}

Game::~Game()
{
    UnloadSound(rotateSound);
    UnloadSound(clearSound);
    CloseAudioDevice();
}

Block Game::GetRandomBlock()
{
    if(blocks.empty())
    {
        blocks = GetAllBlocks();
    }
    int randomIndex = rand() % blocks.size(); //get a random number from 0 to 6
    Block block = blocks[randomIndex];
    blocks.erase(blocks.begin() + randomIndex);
    return block;
}


vector<Block> Game::GetAllBlocks()
{
    return {IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock()};
}

void Game::Draw()
{
    grid.Draw();
    currentBlock.Draw(11, 11);
    switch(nextBlock.id){
        case 3: //I block
            nextBlock.Draw(255, 265);
            break;
        case 4: //O block
            nextBlock.Draw(255, 255);
            break;
        default:
            nextBlock.Draw(270, 245);
            break;
    }
    switch(heldBlock.id){
        case 3: //I block
            heldBlock.Draw(255, 430);
            break;
        case 4: //O block
            heldBlock.Draw(255, 420);
            break;
        default:
            heldBlock.Draw(270, 410);
            break;
    }
}

void Game::HandleInput()
{
    int keyPressed = GetKeyPressed();
    if(gameOver && keyPressed != 0) //any key pressed once game over
    {
        gameOver = false;
        Reset();
    }
    switch(keyPressed)
    {
    case KEY_LEFT:
        MoveBlockLeft();
        break;
    case KEY_RIGHT:
        MoveBlockRight();
        break;
    case KEY_DOWN:
        MoveBlockDown();
        UpdateScore(0, 1);
        break;
    case KEY_UP:
        RotateBlock();
        break;
    case KEY_C:
        HoldBlock(isBlockHeld);
        break;
    }
}

void Game::MoveBlockLeft()
{
    if(!gameOver){
        currentBlock.Move(0, -1);
        if(IsBlockOutside() || BlockFits() == false) 
        {
            currentBlock.Move(0, 1);
        }
    }
}

void Game::MoveBlockRight()
{
    if(!gameOver){
        currentBlock.Move(0, 1);
        if(IsBlockOutside() || BlockFits() == false) 
        {
            currentBlock.Move(0, -1);
        }
    }
}

void Game::MoveBlockDown()
{
    if(!gameOver){
        currentBlock.Move(1, 0);
        if(IsBlockOutside() || BlockFits() == false)
        {
            currentBlock.Move(-1, 0);
            LockBlock();
        }
    }
}

bool Game::IsBlockOutside()
{
    vector<Position> tiles = currentBlock.GetCellPositions();
    for(Position item : tiles)
    {
        if(grid.IsCellOutside(item.row, item.col))
        {
            return true;
        }
    }
    return false;
}

void Game::RotateBlock()
{
    if(!gameOver){
        currentBlock.Rotate();
        if(IsBlockOutside() || BlockFits() == false)
        {
            currentBlock.UndoRotation();
        }
        else 
        {
            PlaySound(rotateSound);
        }
    }
}

void Game::LockBlock()
{
    vector<Position> tiles = currentBlock.GetCellPositions();
    for(Position item : tiles)
    {
        grid.grid[item.row][item.col] = currentBlock.id; 
        //permanently sets the color of tile in game grid to be the color of the current block's tile color
    }
    currentBlock = nextBlock;
    if(BlockFits() == false)
    {
        gameOver = true;
    }
    nextBlock = GetRandomBlock();
    int rowsCleared = grid.ClearFullRows();
    if(rowsCleared > 0)
    {
        PlaySound(clearSound);
        UpdateScore(rowsCleared, 0);
    }
}

bool Game::BlockFits()
{
    vector<Position> tiles = currentBlock.GetCellPositions(); 
    //need to check if any of the cells are currently occupied on the grid
    for(Position item : tiles)
    {
        if(grid.IsCellEmpty(item.row, item.col) == false)
        {
            return false;
        }
    }
    return true;
}

void Game::UpdateScore(int linesCleared, int moveDownPoints)
{
    switch(linesCleared)
    {
        case 1:
            score += 100;
            break;
        case 2:
            score += 300;
            break;
        case 3:
            score += 500;
            break;
        case 4:
            score += 800;
            break;
        default:
            break;
    }

    score += moveDownPoints;
    UpdateLevel(score, level);
}

void Game::UpdateLevel(int score, int &level)
{
    if(score >= level*1000)
    {
        level++;
        speed = speed / (level*0.25);
    }
}

void Game::Reset()
{
    grid.Initialize(); //this method clears and resets all cells to 0
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    isBlockHeld = false;
    score = 0;
    speed = 0.3;
    level = 1;
}

void Game::HoldBlock(bool &isBlockHeld)
{
    if(!isBlockHeld)
    {
        Block temp = Block();
        temp = currentBlock;

        currentBlock = nextBlock;
        nextBlock = GetRandomBlock();
        heldBlock = temp;
        
        isBlockHeld = true;
    }
    else
    {
        Block temp = Block();
        temp = currentBlock;

        currentBlock = heldBlock;
        heldBlock = temp;
        currentBlock.Draw(11, 11);
    }
}