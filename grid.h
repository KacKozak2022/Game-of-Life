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
    void setCell(int row, int col, char val){m_tab[row][col] = val;}
    char getCell(int row, int col){return m_tab[row][col];}
    int getHeight(){return m_height;}
    int getWidth(){return m_width;}
    void allocate(int height, int width);
    void deallocate();
};

#endif // GRID_H
