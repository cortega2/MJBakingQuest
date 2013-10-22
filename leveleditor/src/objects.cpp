#include "objects.h"

QGraphicsRectWidget::QGraphicsRectWidget(Qt::GlobalColor newColor){
    brush = new QBrush(newColor,Qt::SolidPattern);
}
QGraphicsRectWidget::QGraphicsRectWidget(QPixmap pMap){
    brush = new QBrush(pMap);
}

//default
QGraphicsRectWidget::QGraphicsRectWidget(){
    brush= new QBrush(QPixmap("concrete.png"));
}
