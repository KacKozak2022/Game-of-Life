#ifndef CONTROL_H
#define CONTROL_H
#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QApplication>
#include <QTime>
#include <QTimer>
#include <QDebug>

using namespace std;

class Control: public QObject
{
private:
    Q_OBJECT

    int m_height = 0;
    int m_width = 0;
    int m_iterations = 0;
    int m_seed = 0; //????????
    char** gridCurrent = nullptr;
    char** gridNext = nullptr;

    QTimer *m_timer = nullptr;

    bool checkState(int row, int col);
    void deallocGrid(char*** tab);
    void allocGrid(char*** tab, int height, int width);

public slots:
    void iterate();

public:
    Control();
    void changeDimensions(int height, int width);
    void seed(unsigned int entered_seed);
    void loadFromFile();
    void saveToFile();

    void simStart(double interval);
    void simStop();
    void reset(int h, int w);
    void changeState(int row, int column);

    int getHeight(){return m_height;}
    int getWidth(){return m_width;}
    char*** getGridCurrent(){return &gridCurrent;}
    QTimer* getTimer(){return m_timer;}
};

#endif // CONTROL_H
