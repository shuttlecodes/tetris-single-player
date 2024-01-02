#include "grid.h"
#include <iostream>
#include "colors.h"
using namespace std;

Grid::Grid()
{
    numRows = 20;
    numCols = 10;
    cellSize = 30;
    Initialize();
    colors = GetCellColors();
}

void Grid::Initialize()
{
    for(int row = 0; row < numRows; row++)
    {
        for(int col = 0; col < numCols; col++)
        {
            grid[row][col] = 0;
        }
    }
}

void Grid::Print()
{
    for(int row = 0; row < numRows; row++)
    {
        for(int col = 0; col < numCols; col++)
        {
            cout << grid[row][col] << " ";
        }
        cout << endl;
    }
}

void Grid::Draw()
{
    for(int row = 0; row < numRows; row++)
    {
        for(int col = 0; col < numCols; col++)
        {
            int cellValue = grid[row][col];
            DrawRectangle(col*cellSize +11, row*cellSize +11, cellSize-1, cellSize-1, colors[cellValue]);
        }
    }
}

bool Grid::IsCellOutside(int row, int col)
{
    if(row >= 0 && row < numRows && col >= 0 && col < numCols)
    {
        return false;
    }
    return true;
}

bool Grid::IsCellEmpty(int row, int col)
{
    if(grid[row][col] == 0)
    {
        return true;
    }
    return false;
}

int Grid::ClearFullRows()
{
    int completed = 0;
    for(int row = numRows - 1; row >= 0; row--) //iterate from bottom row and upward
    {
        if(IsRowFull(row)) //If the row is full
        {
            ClearRow(row); //Clear it
            completed++; //Increase the count for # of completed rows
        } //Then loop back and check if statement for the next row above

        else if (completed > 0) //If the row is NOT full, just move the rows down
        {
            MoveRowDown(row, completed);
        } //Then loop back and check if statement for the next row above
    }
    return completed;
}

bool Grid::IsRowFull(int row)
{
    for(int col = 0; col < numCols; col++)
    {
        if(grid[row][col] == 0) //go through all cells in the row
        {
            return false; //row is NOT full if there is an empty cell
        }
    }
    return true;
}

void Grid::ClearRow(int row)
{
    for(int col = 0; col < numCols; col++)
    {
        grid[row][col] = 0;
    }
}

void Grid::MoveRowDown(int row, int numRows) 
{
    for(int col = 0; col < numCols; col++)
    {
        grid[row + numRows][col] = grid[row][col]; //move the row down by #numRows
        grid[row][col] = 0; //clear previously occupied row
    }
}
