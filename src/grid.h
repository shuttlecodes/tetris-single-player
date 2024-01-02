#pragma once
#include <vector>
#include <raylib.h>
using namespace std;

class Grid{
public:
    Grid();
    void Initialize();
    void Print();
    void Draw();
    bool IsCellOutside(int row, int col);
    bool IsCellEmpty(int row, int col);
    int ClearFullRows();
    int grid[20][10];

private:
    bool IsRowFull(int row);
    void ClearRow(int row);
    void MoveRowDown(int row, int numRows);
    vector<Color> colors;
    int numRows;
    int numCols;
    int cellSize;
};