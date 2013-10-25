#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "ui_editormainwindow.h"

namespace Ui {
class MainWindow;
}
//this statement avoid circular references "forward declation"
class engine;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0, engine *gin = 0 , QGraphicsScene *uiScene = NULL, int BLOCK_SIZE = 30);
    void MainWindow::InitGraphics(QGraphicsScene *scene);
    ~MainWindow();

private slots:
    void on_actionOpen_triggered();
    void on_actionExit_triggered();
    void on_actionClose_triggered();
    void on_actionDraw_Grid_Lines_triggered();

private:
    Ui::MainWindow *ui;
    engine *ginny;
};


#endif // MAINWINDOW_H
