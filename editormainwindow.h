#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#if QT_VERSION >= 0x050000
    #include <QtWidgets>
#endif

#include "engine.h"
#include "graphicsvieweditor.h"
#include "ui_editormainwindow.h"
#include "definitions.h"


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
    QGraphicsView* GetGraphicsView();
    QGraphicsScene* GetGraphicsScene();

    explicit editWindow(QWidget *parent = 0);
    void InitGraphics(QGraphicsScene *scene);
    ~editWindow();

private slots:
    void on_actionOpen_triggered();
    void on_actionExit_triggered();
    void on_actionClose_triggered();
    void on_actionDraw_Grid_Lines_triggered();

    /* For some reason, these dont all work...
        FIXED IT, centralWidget()->setAttribute(Qt::WA_TransparentForMouseEvents);*/
    //void mousePressEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent * event);
    // void mouseDoubleClickEvent(QMouseEvent * e);
    //void mouseMoveEvent(QMouseEvent * event);

    void on_actionUsage_triggered();

    void on_actionSnap_Now_triggered();

    void on_actionCredits_triggered();

private:
    Ui::MainWindow *ui;
    engine *ginny;
    QGraphicsScene *graphicsScene;
    GraphicsViewEditor *graphicsView;
};


#endif // MAINWINDOW_H
