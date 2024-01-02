#include "block.h"
using namespace std;

Block::Block()
{
    cellSize = 30;
    rotationState = 0;
    colors = GetCellColors();
    rowOffset = 0;
    colOffset = 0;
}

// void Block::Draw(int offsetX, int offsetY)
void Block::Draw(int offsetX, int offsetY)
{
    vector<Position> tiles = GetCellPositions();
    for(Position item : tiles)
    {
        DrawRectangle(item.col * cellSize +offsetX, item.row * cellSize +offsetY, cellSize-1, cellSize-1, colors[id]);
    }
}

void Block::Move(int rows, int cols)
{
    rowOffset += rows;
    colOffset += cols;
}

vector<Position> Block::GetCellPositions()
{
    vector<Position> tiles = cells[rotationState];
    vector<Position> movedTiles;
    for(Position item : tiles)
    {
        Position newPos = Position(item.row + rowOffset, item.col + colOffset);
        movedTiles.push_back(newPos);
    }
    return movedTiles;
}

void Block::Rotate()
{
    rotationState ++;
    if(rotationState == (int)cells.size()) //cast the number to an int. checks if max rotation state number
    {
        rotationState = 0;
    }
}

void Block::UndoRotation()
{
    rotationState --;
    if(rotationState == -1)
    {
        rotationState = cells.size() - 1;
    }
}
