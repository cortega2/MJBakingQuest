#ifndef ENGINE_H
#define ENGINE_H

#include <QtCore>
#include <QtGui>

#if QT_VERSION >= 0x050000
    #include <QtWidgets>
#endif

#include "objects.h"
#include "parser.h"
#include "objStructure.h"

class engine
{

public:
    engine();
    engine( QGraphicsScene *scene );
    ~engine();

    QGraphicsScene* GetScene();
    void SetScene( QGraphicsScene *scene );
    void SetParentWindow(QWidget *pWindow );
    void ClickedOpenMap(void);
    void CloseMap(void);
    void ClickedDrawGridLines(void);

private:
    const QRect *sSize;

    objStructure *spritesAndStuff;
    parser *parsley;

    QGraphicsScene *uiScene;
    QWidget *parentWindow;

    void DrawGrid(QGraphicsScene *scene);
    void MoveBlock(QGraphicsWidget *box, QGraphicsScene *scene, int x, int y);

    int LoadMap(QGraphicsScene *scene);
    int LoadMap(QGraphicsScene *scene, QString fileName);

};

#endif // ENGINE_H
