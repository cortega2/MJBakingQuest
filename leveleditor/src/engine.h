#ifndef ENGINE_H
#define ENGINE_H

#include "mainwindow.h"

class engine
{
public:
    engine();
    ~engine();
    void begin( MainWindow *mainWindow );

private:
    const QRect *sSize;
    const QRect *wSize;

    QGraphicsScene *uiScene;

    void DrawGrid(QGraphicsScene *scene);
    void MoveBlock(QGraphicsWidget *box, int x, int y);

    int LoadMap(QGraphicsScene *scene);
    int LoadMap(QGraphicsScene *scene, QString fileName);
};

#endif // ENGINE_H
