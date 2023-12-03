#ifndef GRID_H
#define GRID_H
#include <QMainWindow>

class grid
{
    Q_OBJECT
    int m_height = 0;
    int m_width = 0;
    char** m_tab;

public:
    grid() noexcept;
    void allocate(int height, int width);
    void deallocate();

};

#endif // GRID_H
