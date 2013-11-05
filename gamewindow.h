#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QtCore>
#include <QtGui>
#include "engine.h"
#include "ui_gamewindow.h"

namespace Ui {
class gamewindow;
}
//this statement avoid circular references "forward declation"
class engine;
class gamewindow : public QWidget
{
    Q_OBJECT

public:
    explicit gamewindow(QWidget *parent = 0, engine *gin = 0 , QGraphicsScene *uiScene = NULL, int BLOCK_SIZE = 30);
    ~gamewindow();

private:
    Ui::gamewindow *ui;
    engine *ginny;

//this is needed to listen to keys
protected:
    void keyPressEvent(QKeyEvent * event);
};

#endif // GAMEWINDOW_H
