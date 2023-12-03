#include "grid.h"

grid::grid() noexcept
{




}

void grid::allocate(int height, int width)
{
    m_tab = new char* [height+2];
    for(int i = 0;i < height+2; i++){
        m_tab[i] = new char [width+2];
    }

}

void grid::deallocate()
{

    for(int i = 0;i < m_height+2; i++){
        delete[] m_tab[i];
    }
    delete[] m_tab;
    m_tab = nullptr;

}
