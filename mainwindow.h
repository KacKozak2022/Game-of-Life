#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "control.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    Control Con;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void updateBoardSize();
    void updateStatusBar();
    void updateSingleCell(int row, int column);

public slots:
    void updateBoardContents();

private slots:
    void on_iterateButton_clicked();

    void on_loadButton_clicked();

    void on_saveButton_clicked();

    void on_seedButton_clicked();

    void on_dimensionsButton_clicked();

    void on_startSimButton_clicked();

    void on_stopSimButton_clicked();

    void on_resetButton_clicked();

    void on_tableWidget_cellClicked(int row, int column);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
