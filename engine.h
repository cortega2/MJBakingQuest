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
    void loadGame(QString level);
    void saveGame(QString name);
    void ClickedOpenMap(void);
    void CloseMap(void);
    void ClickedDrawGridLines(void);
    void moveChar(int direction);
    void moveEnemies();

private:
    const QRect *sSize;

    objStructure *goodGuys;
    objStructure *enemies;
    objStructure *blocks;
    objStructure *other;
    parser *parsley;
    Node *walkable[20][30];

    QGraphicsScene *uiScene;
    QWidget *parentWindow;

    void DrawGrid(QGraphicsScene *scene);
    void MoveBlock(QGraphicsWidget *box, QGraphicsScene *scene, int x, int y);

    int LoadMap(QGraphicsScene *scene);
    int LoadMap(QGraphicsScene *scene, QString fileName);

    //QGraphicsRectWidget *mj;
    Node *mj;

};

#endif // ENGINE_H
