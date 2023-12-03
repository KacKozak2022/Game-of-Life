#ifndef GRID_H
#define GRID_H
#include <QMainWindow>

class grid
{
    Q_OBJECT
    int height = 0;
    int width = 0;
    char** tab[];




public:
    grid() noexcept;


    void allocate(int height, int width);




};

#endif // GRID_H
