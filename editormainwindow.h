#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "ui_editormainwindow.h"

namespace Ui {
class MainWindow;
}

class engine;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0, engine *gin = 0 );
    void MainWindow::InitGraphics(QGraphicsScene *scene);
    ~MainWindow();

    Ui::MainWindow *ui;

    engine *ginny;

private slots:
    void on_actionOpen_triggered();
    void on_actionExit_triggered();
    void on_actionClose_triggered();
    void on_actionDraw_Grid_Lines_triggered();
};


#endif // MAINWINDOW_H
