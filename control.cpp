#include "control.h"

Control::Control(){}



short Control::checkState(int row, int col){
    int neighbours = 0;
    for (int y = -1; y < 2; y++)
    {
        for (int x = -1; x < 2; x++)
        {
            if (!(x == 0 && y == 0)) {
                if (gridCurrent.getCell(row+y, col+x)) {
                    neighbours++;
                }
            }
        }
    }
    if (neighbours == 3) return true;
    if (gridCurrent.getCell(row, col) && neighbours == 2) return true;
    return false;
}



void Control::iterate(){
    const int WIDTH = gridCurrent.getWidth();
    const int HEIGHT = gridCurrent.getHeight();
    for (size_t i = 1; i < HEIGHT + 1; i++)
    {
        for (size_t j = 1; j < WIDTH + 1; j++)
        {
            gridNext.setCell(i,j,checkState(i, j));
        }
    }
    for (size_t i = 1; i < HEIGHT + 1; i++)
    {
        for (size_t j = 1; j < WIDTH + 1; j++)
        {
            if (gridNext.getCell(i,j)) {
                gridCurrent.setCell(i,j,gridCurrent.getCell(i,j)+1);
            }
            else {
                gridCurrent.setCell(i,j,0);
            }
        }
    }




}
