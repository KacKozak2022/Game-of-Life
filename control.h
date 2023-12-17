#ifndef CONTROL_H
#define CONTROL_H
#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QApplication>
#include <QTime>
#include <QDebug>
#include <windows.h>

using namespace std;

class Control: public QObject
{
    Q_OBJECT

    int m_height = 0;
    int m_width = 0;
    int m_iterations = 0;
    int m_seed = 0;

    bool m_isSimRunning = 0;
    bool m_isSimPaused = 0;
    int m_simTimeRemaining = 0;

    char** gridCurrent = nullptr;
    bool** gridNext = nullptr;

    short checkState(int row, int col);

    template<typename type>
    void deallocGrid(type** tab)
    {
        if(tab != nullptr)
        {
          for(int i = 0;i < m_height+2; i++)
          {
              delete[] tab[i];
              tab[i]=nullptr;
          }
          delete[] tab;
          tab = nullptr;
        }
    }

    template<typename type>
    void allocGrid(type** tab, int height, int width)
    {
        tab = new type* [height+2];

        for(int i = 0;i < height+2; i++)
        {
            tab[i] = new type [width+2];
        }
    }

public:
    Control();
    void ChangeDimensions(int height, int width);
    void iterate();
    void seed(unsigned int entered_seed);
    void loadFromFile();
    void saveToFile();
    void simStart(int duration);
    void simPause();
    void simStop();
};

#endif // CONTROL_H
