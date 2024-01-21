#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(QSize(800, 900));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_iterateButton_clicked()
{
    Con.iterate();
}


void MainWindow::on_loadButton_clicked()
{
    Con.loadFromFile();
}


void MainWindow::on_saveButton_clicked()
{
    Con.saveToFile();
}


void MainWindow::on_seedButton_clicked()
{
    Con.seed(ui->seedEdit->text().toInt());
}


void MainWindow::on_dimensionsButton_clicked()
{
    Con.changeDimensions(ui->heightEdit->text().toInt(), ui->widthEdit->text().toInt());
}


void MainWindow::on_startSimButton_clicked()
{
    Con.simStart(ui->simIntervalEdit->text().toInt());
}


void MainWindow::on_stopSimButton_clicked()
{
    Con.simStop();
}

