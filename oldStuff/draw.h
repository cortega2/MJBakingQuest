#ifndef DRAW_H
#define DRAW_H

#include <QGraphicsItem>

//! [0]
class draw : public QGraphicsItem
{
public:
    draw();

    QRectF boundingRect() const;
    //QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);

private:
    qreal speed;
    qreal direction;
    QColor color;
};
//! [0]
#endif // DRAW_H
