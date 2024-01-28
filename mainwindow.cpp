#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(Con.getTimer(),SIGNAL(timeout()), this, SLOT(updateBoardContents()));
    //this->setFixedSize(QSize(800, 900));
    //ui->horizontalLayout_2->SetMaximumSize(QLayout::sizeConstraint());
    qInfo()<<"konstruktor Mainwindow";
    updateBoardSize();
    updateBoardContents();
    updateStatusBar();

}

MainWindow::~MainWindow()
{
    delete ui;
}

QBrush c_blue(QColor::fromRgb(64,25,255));
QBrush c_blurple(QColor::fromRgb(140,25,255));
QBrush c_purple(QColor::fromRgb(217,25,255));
QBrush c_pink(QColor::fromRgb(225,25,217));
QBrush c_red(QColor::fromRgb(255,25,140));

void MainWindow::updateSingleCell(int row, int column)
{
    int state = static_cast<int>((*Con.getGridCurrent())[row][column]);
    switch(state){
    case '0':
        ui->tableWidget->item(row, column)->setBackground(Qt::black); break;
    case '1':
        ui->tableWidget->item(row, column)->setBackground(c_blue); break;
    case '2':
        ui->tableWidget->item(row, column)->setBackground(c_blurple); break;
    case '3':
        ui->tableWidget->item(row, column)->setBackground(c_purple); break;
    case '4':
        ui->tableWidget->item(row, column)->setBackground(c_pink); break;
    case '5':
        ui->tableWidget->item(row, column)->setBackground(c_red); break;
    }
/*
    if((*Con.getGridCurrent())[row + 1][column + 1] == '0')
    {
        ui->tableWidget->item(row, column)->setBackground(Qt::black);
    }
    else if((*Con.getGridCurrent())[row + 1][column + 1] < '5')
    {
        ui->tableWidget->item(row, column)->setBackground(Qt::gray);
    }
    else
    {
        ui->tableWidget->item(row, column)->setBackground(c_blue);
    }
*/
}

void MainWindow::updateStatusBar()
{
    QString message = QString("%1 x %2, seed = %3").arg(Con.getHeight()).arg(Con.getWidth()).arg(Con.getSeed());
    ui->statusbar->showMessage(message);
}

void MainWindow::updateBoardSize()
{
    ui->tableWidget->setRowCount(Con.getHeight());
    ui->tableWidget->setColumnCount(Con.getWidth());

    ui->tableWidget->verticalHeader()->setDefaultSectionSize(Con.getHeight());
    ui->tableWidget->horizontalHeader()->setDefaultSectionSize(Con.getWidth());

    ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    for(int i=0; i < Con.getHeight(); i++)
    {
        for(int j=0; j < Con.getWidth(); j++)
        {
            ui->tableWidget->setItem(i, j, new QTableWidgetItem);
        }
    }
}

void MainWindow::updateBoardContents()
{
    for(int i=0; i < Con.getHeight(); i++)
    {
        for(int j=0; j < Con.getWidth(); j++)
        {
            qInfo()<< "cell:" << i<<","<<j;
            updateSingleCell(i,j);
        }
    }
}

void MainWindow::on_iterateButton_clicked()
{
    Con.iterate();
    updateBoardContents();
}


void MainWindow::on_loadButton_clicked()
{
    Con.loadFromFile();
    updateBoardSize();
    updateBoardContents();
    updateStatusBar();
}


void MainWindow::on_saveButton_clicked()
{
    Con.saveToFile();
}


void MainWindow::on_seedButton_clicked()
{
    Con.seed(ui->seedEdit->text().toInt());
    updateBoardContents();
    updateStatusBar();
}


void MainWindow::on_dimensionsButton_clicked()
{
    Con.changeDimensions(ui->heightEdit->text().toInt(), ui->widthEdit->text().toInt());
    updateBoardSize();
    updateBoardContents();
    updateStatusBar();
}


void MainWindow::on_startSimButton_clicked()
{
    Con.simStart(ui->simIntervalEdit->text().toInt());
}


void MainWindow::on_stopSimButton_clicked()
{
    Con.simStop();
}


void MainWindow::on_resetButton_clicked()
{
    Con.reset(Con.getHeight(), Con.getWidth());
    updateBoardContents();
}


void MainWindow::on_tableWidget_cellClicked(int row, int column)
{
    Con.changeState(row + 1, column + 1);
    updateSingleCell(row, column);
}

