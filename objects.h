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
#endif // OBJECTS_H
