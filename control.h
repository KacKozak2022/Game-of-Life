#ifndef CONTROL_H
#define CONTROL_H
#include <QMainWindow>
#include "grid.h"

class Control: public QObject
{
    Q_OBJECT
    Grid gridCurrent, gridNext;
    int m_iterations = 0;

    short checkState(int row, int col);


public:
    Control();
    void iterate();
};

#endif // CONTROL_H
