#include "control.h"

Control::Control()
{
    m_timer = new QTimer(this);
    connect(m_timer,SIGNAL(timeout()), this, SLOT(iterate()));
    genRandom.seed(randDevice());
}

Control::~Control()
{
    deallocGrid(&gridCurrent);
    deallocGrid(&gridNext);
}

void Control::reset(int h, int w)
{
    for(int i=0; i < h+2; i++)
    {
        for(int j=0; j < w+2; j++)
        {
            gridCurrent[i][j] = '0';
            gridNext[i][j] = '0';
        }
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

bool Control::checkState(int row, int col){
    int neighbours = 0;
    for (int y = -1; y < 2; y++)
    {
        for (int x = -1; x < 2; x++)
        {
            if (!(x == 0 && y == 0)) {
                if (gridCurrent[row+y][col+x] != '0') {
                    neighbours++;
                }
            }
        }
    }
    if (neighbours == 3) return true;
    if (gridCurrent[row][col] != '0' && neighbours == 2) return true;
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
            if (gridNext[i][j])
            {
                if(gridCurrent[i][j] < '5') gridCurrent[i][j]++;
            }
            else
                gridCurrent[i][j] = '0';
        }
    }
}

void Control::changeDimensions(int height, int width){

    if(width*height > 250000)
        QMessageBox::information(nullptr, "Caution", "Setting a large board size may slow down the program on slower devices");

    char** tempGridCurrent = gridCurrent;
    char** tempGridNext = gridNext;

    allocGrid(&gridCurrent, height, width);
    allocGrid(&gridNext, height, width);
    reset(height, width);

    int minHeight = min(height, m_height);
    int minWidth = min(width, m_width);

    for (size_t i = 1; i < minHeight + 1; i++)
    {
        for (size_t j = 1; j < minWidth + 1; j++)
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
    if(entered_seed){
        genUser.seed(entered_seed);
        m_seed = entered_seed;
    }else{
        int randomSeed = genRandom();
        genUser.seed(randomSeed);
        m_seed = randomSeed;
    }

    bernoulli_distribution berDis(0.1);
    for(int i=1; i<m_height+1; i++)
    {
        for(int j=1; j<m_width+1; j++)
        {
            if(berDis(genUser))
                gridCurrent[i][j] = '1';
            else gridCurrent[i][j] = '0';
        }
    }
}

void Control::loadFromFile(QString path)
{
    QString fileName;
    if(path != "") fileName = path;
    else fileName = QFileDialog::getOpenFileName(nullptr,
                        tr("Choose a file to load"),"",
                        tr("Text file (*.txt);;All Files (*)"));

    if(fileName.isEmpty())
        return;
    else
    {
        QFile file(fileName);

        if(file.open(QIODevice::ReadOnly))
        {
            QTextStream stream(&file);

            int h = stream.readLine().toInt();
            int w = stream.readLine().toInt();
            unsigned int s = stream.readLine().toInt();

            changeDimensions(h, w);
            reset(m_height, m_width);
            m_seed = s;

            for(int i = 1; i < m_height+1; i++)
            {
                QString line = stream.readLine();
                for(int j = 1; j < m_width+1; j++)
                gridCurrent[i][j] = line.at(j-1).toLatin1();
            }

            file.close();
        }
        else
            QMessageBox::warning(nullptr, tr("Load Error!"),file.errorString());
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
            stream << m_height << "\n" << m_width << "\n" << m_seed << "\n";

            for(int i = 1; i < m_height+1; i++)
            {
                for(int j = 1; j < m_width+1; j++)
                    stream << gridCurrent[i][j];
                stream << "\n";
            }
            file.close();
        }
        else
            QMessageBox::warning(nullptr, tr("Save Error!"),file.errorString());
    }
}

void Control::simStart(double interval)
{
    m_timer->setInterval(interval*1000);
    m_timer->start();
}

void Control::simStop()
{
    m_timer->stop();
}

void Control::changeState(int row, int column)
{
    if(gridCurrent[row][column] == '0')
        gridCurrent[row][column] = '1';
    else
        gridCurrent[row][column] = '0';
}

















