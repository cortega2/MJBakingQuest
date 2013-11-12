#include "editormainwindow.h"

//test code
#include <iostream>


editWindow::editWindow(QWidget *parent, int BLOCK_SIZE) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    ginny = new engine();

    ui->setupUi(this);

    graphicsView = new GraphicsViewEditor();
    graphicsView->setGeometry( QRect(0,ui->menubar->height(),BLOCK_SIZE*30,BLOCK_SIZE*20 + ui->menubar->height()) );

    graphicsScene = new QGraphicsScene( QRect(0,0,BLOCK_SIZE*30,BLOCK_SIZE*20) );
    graphicsView->setScene( graphicsScene );

    ginny->SetScene( graphicsScene );
    ginny->SetParentWindow( this );

    graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    setMouseTracking(true);
}
/* need to clean up stuff when your done! */
editWindow::~editWindow(){
    delete ui;
    delete ginny;
    delete graphicsView;
    delete graphicsScene;
}

QGraphicsView* editWindow::GetGraphicsView(){
    return graphicsView;
}

QGraphicsScene* editWindow::GetGraphicsScene(){
    return graphicsScene;
}

void editWindow::on_actionOpen_triggered(){
    ginny->ClickedOpenMap();
}

void editWindow::on_actionExit_triggered(){
    qApp->exit();
}

void editWindow::on_actionClose_triggered(){
    ginny->CloseMap();
}

void editWindow::on_actionDraw_Grid_Lines_triggered(){
    ginny->ClickedDrawGridLines();
}
/*
void editWindow::mousePressEvent(QMouseEvent * event){

    if(event->button() == Qt::LeftButton ){
        graphicsView->setCursor(QCursor(Qt::ClosedHandCursor));
    }
}
*/
/*
void editWindow::mouseReleaseEvent(QMouseEvent * event){
    graphicsView->setCursor(QCursor(Qt::OpenHandCursor));
}
*/
/*
void editWindow::mouseMoveEvent(QMouseEvent * event){
    if( event->buttons() == Qt::LeftButton ){
        double rad = 10;
        QPointF pt = graphicsView->mapToScene(event->pos());
        graphicsScene->addEllipse( pt.x()-rad, pt.y()-rad, rad, rad, QPen(), QBrush(Qt::blue, Qt::SolidPattern));
    }
    else if( event->buttons() == Qt::RightButton ){
        double rad = 10;
        QPointF pt = graphicsView->mapToScene(event->pos());
        graphicsScene->addEllipse( pt.x()-rad, pt.y()-rad, rad, rad, QPen(), QBrush(Qt::red, Qt::SolidPattern));
    }
}
*/
