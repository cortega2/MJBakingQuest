#ifndef OBJECTS_H
#define OBJECTS_H

#include <QtCore>
#include <QtWidgets>

class QGraphicsRectWidget : public QGraphicsWidget{

    QBrush *brush;
public:
    QGraphicsRectWidget::QGraphicsRectWidget(Qt::GlobalColor color);
    QGraphicsRectWidget::QGraphicsRectWidget(QPixmap pMap);
    QGraphicsRectWidget::QGraphicsRectWidget();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
    {
        painter->fillRect(rect(), *brush);
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
