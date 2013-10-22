#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void MainWindow::InitGraphics(QGraphicsScene *scene);
    ~MainWindow();

//private:
    Ui::MainWindow *ui;
};


#endif // MAINWINDOW_H
