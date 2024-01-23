#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //this->setFixedSize(QSize(800, 900));
    //ui->horizontalLayout_2->SetMaximumSize(QLayout::sizeConstraint());
    updateBoardSize();
    updateBoardContents();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateBoardSize()
{
    ui->tableWidget->setRowCount(Con.getHeight());
    ui->tableWidget->setColumnCount(Con.getWidth());

    ui->tableWidget->verticalHeader()->setDefaultSectionSize(Con.getHeight());
    ui->tableWidget->horizontalHeader()->setDefaultSectionSize(Con.getWidth());

    ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void MainWindow::updateBoardContents()
{
    for(int i=1; i < Con.getHeight() + 1; i++)
    {
        for(int j=1; j < Con.getWidth() + 1; j++)
        {
            ui->tableWidget->setItem(i - 1, j - 1, new QTableWidgetItem);

            if((*Con.getGridCurrent())[i][j] == '0')
            {
                ui->tableWidget->item(i - 1, j - 1)->setBackground(Qt::white);
            }
            else if((*Con.getGridCurrent())[i][j] <= '5')
            {
                ui->tableWidget->item(i - 1, j - 1)->setBackground(Qt::black);
            }
            else
            {
                ui->tableWidget->item(i - 1, j - 1)->setBackground(Qt::darkYellow);
            }
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
}


void MainWindow::on_saveButton_clicked()
{
    Con.saveToFile();
}


void MainWindow::on_seedButton_clicked()
{
    Con.seed(ui->seedEdit->text().toInt());
    updateBoardContents();
}


void MainWindow::on_dimensionsButton_clicked()
{
    Con.changeDimensions(ui->heightEdit->text().toInt(), ui->widthEdit->text().toInt());
    updateBoardSize();
    updateBoardContents();
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

