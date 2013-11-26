#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QtCore>
#include <QtGui>
#include "engine.h"
#include "ui_gamewindow.h"
#include "definitions.h"

namespace Ui {
class gamewindow;
}
//this statement avoid circular references "forward declation"
class engine;
class gamewindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit gamewindow(QWidget *parent = 0, bool newGame = true, QString sessionName = NULL);
    ~gamewindow();
    int left;
    int right;
    QGraphicsView* GetGraphicsView();
    bool mjHasBlock;
    QString nextLevel;


public slots:
    void moveEvent();

private:
    Ui::gamewindow *ui;
    engine *ginny;

    QGraphicsScene *graphicsScene;
    QGraphicsView *graphicsView;

    QString session;

//this is needed to listen to keys
protected:
    void keyPressEvent(QKeyEvent *event);
};

#endif // GAMEWINDOW_H
