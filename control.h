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
#include <windows.h>

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

    QTimer *timer = nullptr;

    short checkState(int row, int col);
    void deallocGrid(char** tab);
    void allocGrid(char*** tab, int height, int width);

public:
    Control();
    void changeDimensions(int height, int width);
    void seed(unsigned int entered_seed);
    void loadFromFile();
    void saveToFile();
    void iterate();
    void simStart(double interval);
    void simStop();

};

#endif // CONTROL_H
