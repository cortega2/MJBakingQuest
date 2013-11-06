#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#if QT_VERSION >= 0x050000
    #include <QtWidgets>
#endif
#include "engine.h"
#include "ui_editormainwindow.h"


//test code for key presses
#include <QKeyEvent>


namespace Ui {
class editWindow;
}
//this statement avoid circular references "forward declation"
class engine;
class editWindow : public QMainWindow
{
    Q_OBJECT

public:
    QGraphicsScene *graphicsScene;
    QGraphicsView *graphicsView;

    explicit editWindow(QWidget *parent = 0, int BLOCK_SIZE = 30);
    void editWindow::InitGraphics(QGraphicsScene *scene);
    ~editWindow();

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
