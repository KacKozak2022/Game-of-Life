#include "grid.h"

Grid::Grid(int height, int width) noexcept: m_height(height), m_width(width)
{
    allocate(height, width);
}

Grid::~Grid(){
    deallocate();
}

void Grid::allocate(int height, int width)
{
    m_tab = new char* [height+2];
    for(int i = 0;i < height+2; i++){
        m_tab[i] = new char [width+2];
    }
}

void Grid::deallocate()
{
    if(m_tab != nullptr){
        for(int i = 0;i < m_height+2; i++){
            delete[] m_tab[i];
        }
        delete[] m_tab;
        m_tab = nullptr;
    }
}
