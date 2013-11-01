#ifndef OBJECTS_H
#define OBJECTS_H

#include <QtCore>
#include <QtGui>
#if QT_VERSION >= 0x050000
    #include <QtWidgets>
#endif

class QGraphicsRectWidget : public QGraphicsWidget{

    QBrush *brush;
    QRect *size;
public:
    QGraphicsRectWidget();
    ~QGraphicsRectWidget();
    QGraphicsRectWidget(Qt::GlobalColor color, int blockWidth, int blockHeight);
    QGraphicsRectWidget(QPixmap pMap, int blockWidth, int blockHeight);
    QGraphicsRectWidget(const char* spriteName, int blockWidth, int blockHeight);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){
        painter->fillRect(*size, *brush);
    }
};

class GraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    GraphicsView(QGraphicsScene *scene, QWidget *parent = NULL) : QGraphicsView(scene, parent)
    {
    }

protected:
    virtual void resizeEvent(QResizeEvent *event)
    {
        fitInView(scene()->sceneRect());
        QGraphicsView::resizeEvent(event);
    }
};


/***********NOT Used right now************************************************************
//A BlockObject holds the block itself and modifiers
class BlockObject{

public:
    BlockObject( QGraphicsWidget *block, bool isStandable, bool isPickupable, bool isPowerUp, bool isNPC );
    ~BlockObject();

    QGraphicsWidget *block;

    //block modifiers
    bool isStandable;
    bool isPickupable;
    bool isPowerUp;
    //npc is Non Player Character
    bool isNPC;

};

// The BlockArray is the master container of blocks on the field
class BlockArray {

public:
    BlockArray( int width, int height );
    ~BlockArray();
    void AddBlock( unsigned int xLocation, unsigned int yLocation, BlockObject *block );

private:
    BlockObject*** board;
    QLinkedList<BlockObject*> standableBlocks;

};
*/
#endif // OBJECTS_H
