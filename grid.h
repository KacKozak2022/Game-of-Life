#ifndef GRID_H
#define GRID_H
#include <QMainWindow>

class Grid: public QObject
{
    Q_OBJECT
    int m_height = 0;
    int m_width = 0;
    char** m_tab = nullptr;

public:
    Grid() noexcept{}
    Grid(int height, int width) noexcept;
    ~Grid();
    void allocate(int height, int width);
    void deallocate();
};

#endif // GRID_H
