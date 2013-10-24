#ifndef ENGINE_H
#define ENGINE_H

#include "mainwindow.h"

class engine
{

public:
    engine();
    ~engine();
    void Setup(MainWindow *ParentWindow );
    void ClickedOpenMap(void);
    void CloseMap(void);
    void ClickedDrawGridLines(void);

private:
    const QRect *sSize;
    const QRect *wSize;

    QGraphicsScene *uiScene;
    QWidget *parentWindow;

    void DrawGrid(QGraphicsScene *scene);
    void MoveBlock(QGraphicsWidget *box, int x, int y);

    int LoadMap(QGraphicsScene *scene);
    int LoadMap(QGraphicsScene *scene, QString fileName);
};

#endif // ENGINE_H
