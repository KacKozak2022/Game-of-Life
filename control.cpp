#include "control.h"
#include <random>

Control::Control()
    :m_height(100), m_width(100)
{
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()), this, SLOT(iterate()));

    allocGrid(&gridCurrent, 100, 100);
    allocGrid(&gridNext, 100, 100);
}

void Control::deallocGrid(char*** tab)
{
    if(*tab != nullptr)
    {
        for(int i = 0;i < m_height+2; i++)
        {
            delete[] (*tab)[i];
        }
        delete[] *tab;
        *tab = nullptr;
    }
}

void Control::allocGrid(char*** tab, int height, int width)
{
    *tab = new char* [height+2];

    for(int i = 0;i < height+2; i++)
    {
        (*tab)[i] = new char [width+2];
    }
}

short Control::checkState(int row, int col){
    int neighbours = 0;
    for (int y = -1; y < 2; y++)
    {
        for (int x = -1; x < 2; x++)
        {
            if (!(x == 0 && y == 0)) {
                if (gridCurrent[row+y][col+x]) {
                    neighbours++;
                }
            }
        }
    }
    if (neighbours == 3) return true;
    if (gridCurrent[row][col] && neighbours == 2) return true;
    return false;
}

void Control::iterate(){

    for (int i = 1; i < m_height + 1; i++)
    {
        for (int j = 1; j < m_width + 1; j++)
        {
            gridNext[i][j] = checkState(i, j);
        }
    }

    for (int i = 1; i < m_height + 1; i++)
    {
        for (int j = 1; j < m_width + 1; j++)
        {
            if (gridNext[i][j]) {
                gridCurrent[i][j]++;
            }
            else {
                gridCurrent[i][j] = 0;
            }
        }
    }

    m_iterations++;
}

void Control::changeDimensions(int height, int width){

    char** tempGridCurrent = gridCurrent;
    char** tempGridNext = gridNext;

    allocGrid(&gridCurrent, height, width);
    allocGrid(&gridNext, height, width);

    int minHeight = min(height, m_height);
    int minWidth = min(width, m_width);

    for (size_t i = 1; i < minHeight; i++)
    {
        for (size_t j = 1; j < minWidth; j++)
        {
            gridCurrent[i][j] = tempGridCurrent[i][j];
            gridNext[i][j] = tempGridNext[i][j];
        }
    }

    deallocGrid(&tempGridCurrent);
    deallocGrid(&tempGridNext);

    m_width = width;
    m_height = height;
}

void Control::seed(unsigned int entered_seed)
{
    mt19937 gen;
    gen.seed(entered_seed);
    bernoulli_distribution berDis(0.5);

    for(int i=1; i<m_height+1; i++)
    {
        for(int j=1; j<m_width+1; j++)
        {
            if(berDis(gen)) gridCurrent[i][j] = '1';
            else gridCurrent[i][j] = '0';
        }
    }

    m_seed = entered_seed;
}

void Control::loadFromFile()
{
    QString fileName = QFileDialog::getOpenFileName(nullptr,
                        tr("Choose a file to load"),"",
                        tr("Text file (*.txt);;All Files (*)"));

    if(fileName.isEmpty())
        return;
    else
    {
        QFile file(fileName);

        if(file.open(QIODevice::ReadOnly))
        {
            deallocGrid(&gridCurrent);

            QTextStream stream(&file);
            stream >> m_height >> m_width;

            allocGrid(&gridCurrent, m_height, m_width);

            for(int i = 0; i < m_height+2; i++)
            {
                for(int j = 0; j < m_width+2; j++)
                    stream >> gridCurrent[i][j];
            }

            file.close();
        }
        else
            QMessageBox::information(nullptr, tr("Load Error!"),file.errorString());
    }

}

void Control::saveToFile()
{
    QString fileName = QFileDialog::getSaveFileName(nullptr,
                      tr("Choose save destination"),"",
                      tr("Text file (*.txt);;All Files (*)"));

    if(fileName.isEmpty())
        return;
    else
    {
        QFile file(fileName);

        if(file.open(QIODevice::WriteOnly))
        {
            QTextStream stream(&file);
            stream << m_height << " " << m_width << "\n";

            for(int i = 0; i < m_height+2; i++)
            {
                for(int j = 0; j < m_width+2; j++)
                    stream << gridCurrent[i][j] << " ";
                stream << "\n";
            }

            file.close();
        }
        else
            QMessageBox::information(nullptr, tr("Save Error!"),file.errorString());
    }
}

void Control::simStart(double interval)
{
    timer->setInterval(interval*1000);
    timer->start();
}

void Control::simStop()
{
    timer->stop();
}



















