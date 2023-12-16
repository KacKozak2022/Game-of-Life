#ifndef CONTROL_H
#define CONTROL_H
#include <QMainWindow>
#include <algorithm>
//#include "grid.h"
using namespace std;

class Control: public QObject
{
    Q_OBJECT
    //Grid gridCurrent, gridNext;
    int m_height = 0;
    int m_width = 0;
    int m_iterations = 0;

    char** gridCurrent = nullptr;
    bool** gridNext = nullptr;

    short checkState(int row, int col);


    template<typename type>
    void deallocGrid(type** tab){
          if(tab != nullptr){
              for(int i = 0;i < m_height+2; i++){
                  delete[] tab[i];
                  tab[i]=nullptr;
              }
              delete[] tab;
              tab = nullptr;
          }
      }

    template<typename type>
    void allocGrid(type** tab, int height, int width){
            tab = new type* [height+2];
            for(int i = 0;i < height+2; i++){
            tab[i] = new type [width+2];
        }
    }

    void ChangeDimensions(int height, int width);

public:
    Control();
    void iterate();
};

#endif // CONTROL_H
