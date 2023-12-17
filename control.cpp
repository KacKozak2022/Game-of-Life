#include "control.h"
#include <algorithm>
#include <random>

Control::Control(){}

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
    //Zakresy pętli uwzględniają faktyczną wielkość tablicy (ramkę)
    for (size_t i = 1; i < m_height + 1; i++)
    {
        for (size_t j = 1; j < m_width + 1; j++)
        {
            gridNext[i][j] = checkState(i, j);
        }
    }
    for (size_t i = 1; i < m_height + 1; i++)
    {
        for (size_t j = 1; j < m_width + 1; j++)
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

void Control::ChangeDimensions(int height, int width){

    char** tempGridCurrent = gridCurrent;
    bool** tempGridNext = gridNext;
    allocGrid<char>(gridCurrent, height, width);
    allocGrid<bool>(gridNext, height, width);
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
    deallocGrid<char>(tempGridCurrent);
    deallocGrid<bool>(tempGridNext);
    m_width = width;
    m_height = height;
}

void Control::seed(unsigned int entered_seed)
{
    mt19937 gen;
    gen.seed(entered_seed);

    for(int i=1; i<m_height+1; i++)
    {
        for(int j=1; j<m_width+1; j++)
        {
            gridCurrent[i][j] = (char)(gen() % 2);
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
        file.close();

        if(file.open(QIODevice::ReadOnly))
        {
            deallocGrid<char>(gridCurrent);
            deallocGrid<bool>(gridNext);

            QTextStream stream(&file);
            stream >> m_height >> m_width;

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
        file.close();

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





















