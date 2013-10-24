#include "objects.h"

QGraphicsRectWidget::~QGraphicsRectWidget(){
    delete brush;
    delete size;
}

QGraphicsRectWidget::QGraphicsRectWidget(){
    brush = new QBrush(Qt::gray,Qt::SolidPattern);
    size = new QRect();
}

QGraphicsRectWidget::QGraphicsRectWidget(Qt::GlobalColor color, int blockWidth, int blockHeight){
    brush = new QBrush(color,Qt::SolidPattern);
    size = new QRect(0,0, blockWidth, blockHeight);
}

QGraphicsRectWidget::QGraphicsRectWidget(QPixmap pMap, int blockWidth, int blockHeight){
    brush = new QBrush(pMap);
    size = new QRect(0,0, blockWidth, blockHeight);
}

QGraphicsRectWidget::QGraphicsRectWidget(const char* spriteName, int blockWidth, int blockHeight){
    brush= new QBrush( QPixmap(spriteName) );
    size = new QRect(0,0, blockWidth, blockHeight);
}
