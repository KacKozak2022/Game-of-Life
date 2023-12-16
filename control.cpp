#include "control.h"

Control::Control(){}

short Control::checkState(int row, int col){
    int neighbours = 0;
    for (int y = -1; y < 2; y++)
    {
        for (int x = -1; x < 2; x++)
        {
            if (!(x == 0 && y == 0)) {
                if (gridCurrent[row+y][col+x]) {
                    neighbours++;
                }
            }
        }
    }
    if (neighbours == 3) return true;
    if (gridCurrent[row][col] && neighbours == 2) return true;
    return false;
}

void Control::iterate(){
    //Zakresy pętli uwzględniają faktyczną wielkość tablicy (ramkę)
    for (size_t i = 1; i < m_height + 1; i++)
    {
        for (size_t j = 1; j < m_width + 1; j++)
        {
            gridNext[i][j] = checkState(i, j);
        }
    }
    for (size_t i = 1; i < m_height + 1; i++)
    {
        for (size_t j = 1; j < m_width + 1; j++)
        {
            if (gridNext[i][j]) {
                gridCurrent[i][j]++;
            }
            else {
                gridCurrent[i][j] = 0;
            }
        }
    }
    m_iterations++;
}

void Control::ChangeDimensions(int height, int width){

    char** tempGridCurrent = gridCurrent;
    bool** tempGridNext = gridNext;
    allocGrid<char>(gridCurrent, height, width);
    allocGrid<bool>(gridNext, height, width);
    int minHeight = min(height, m_height);
    int minWidth = min(width, m_width);
    for (size_t i = 1; i < minHeight; i++)
    {
        for (size_t j = 1; j < minWidth; j++)
        {
            gridCurrent[i][j] = tempGridCurrent[i][j];
        }
    }
    deallocGrid<char>(tempGridCurrent);
    deallocGrid<bool>(tempGridNext);
    m_width = width;
    m_height = height;
}
