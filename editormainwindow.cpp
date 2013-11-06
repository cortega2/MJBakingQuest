#include "editormainwindow.h"

//test code
#include <iostream>


editWindow::editWindow(QWidget *parent, int BLOCK_SIZE) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    ginny = new engine();

    ui->setupUi(this);

    graphicsView = new GraphicsView();
    graphicsView->setGeometry( QRect(0,ui->menubar->height(),BLOCK_SIZE*30,BLOCK_SIZE*20 + ui->menubar->height()) );

    graphicsScene = new QGraphicsScene( QRect(0,0,BLOCK_SIZE*30,BLOCK_SIZE*20) );
    graphicsView->setScene( graphicsScene );

    ginny->SetScene( graphicsScene );
    ginny->SetParentWindow( this );

    graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}
/* need to clean up stuff when your done! */
editWindow::~editWindow(){
    delete ui;
    delete ginny;
    delete graphicsView;
    delete graphicsScene;
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

void GraphicsView::mousePressEvent(QMouseEvent * event){

    if(event->button() == Qt::LeftButton )
        this->setCursor(QCursor(Qt::ClosedHandCursor));

    if(event->button() == Qt::RightButton){
        QMessageBox* msgBox;
        msgBox = new QMessageBox();
        msgBox->setWindowTitle("Hello");
        msgBox->setText("You Clicked Right Mouse Button");
        msgBox->show();
    }
}
void GraphicsView::mouseReleaseEvent(QMouseEvent * event){
    /*place the object */
    QPointF point =  mapToScene(event->pos());
    //blah blah
    //SnapToBlock()
    //if()
    this->setCursor(QCursor(Qt::OpenHandCursor));
}
void GraphicsView::mouseMoveEvent(QMouseEvent * event){
    double rad = 10;
    QPointF pt = mapToScene(event->pos());
    scene()->addEllipse( pt.x()-rad, pt.y()-rad, rad, rad, QPen(), QBrush(Qt::SolidPattern));
}
