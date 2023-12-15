#ifndef CONTROL_H
#define CONTROL_H
#include <QMainWindow>
#include "grid.h"

class Control: public QObject
{
    Q_OBJECT
    Grid grid;
    int m_iterations = 0;
    short howManyNeighbours(int X, int Y);


public:
    Control();
    void iterate();




};

#endif // CONTROL_H
