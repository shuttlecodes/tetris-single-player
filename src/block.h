#pragma once
#include <vector>
#include <map>
#include "position.h"
#include "colors.h"
using namespace std;

class Block{
public:
    Block();
    void Draw(int offsetX, int offsetY);
    void Move(int rows, int cols);
    vector<Position> GetCellPositions();
    void Rotate();
    void UndoRotation();
    int id;
    map<int, vector<Position>> cells; //maps integers to vectors of positions

private:
    int cellSize;
    int rotationState;
    vector<Color> colors;
    int rowOffset;
    int colOffset;
};