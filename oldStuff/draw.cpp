#include "draw.h"
#include <QPainter>
#include <QGraphicsScene>
#include <QStyleOption>

//! [0]
draw::draw() : speed(0), direction(0), color(250, 100, 50){

}
//! [0]

//! [1]
QRectF draw :: boundingRect() const{
    qreal adjust = .5;
    return QRectF(-18 - adjust, -22 - adjust,
                  36 + adjust, 60 + adjust);
}
//! [1]

//! [2]
void draw :: paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    // Body
    painter->setBrush(color);
    painter->drawEllipse(-10, -20, 20, 40);
}
//! [2]
