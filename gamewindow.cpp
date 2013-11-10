#include "gamewindow.h"

//testcode
#include <iostream>

gamewindow::gamewindow(QWidget *parent, int BLOCK_SIZE) :
    QMainWindow(parent),
    ui(new Ui::gamewindow)
{
    ui->setupUi(this);
    ginny = new engine();

    graphicsView = new GraphicsView();
    graphicsView->setGeometry( QRect(0, 0, BLOCK_SIZE*30, BLOCK_SIZE*20 ) );

    graphicsScene = new QGraphicsScene( QRect(0,0,BLOCK_SIZE*30,BLOCK_SIZE*20) );
    graphicsView->setScene( graphicsScene );

    ginny->SetScene( graphicsScene );
    ginny->SetParentWindow( this );

    graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ginny->loadGame("levels/defaultlevel");

    //not sure if this is the best place to place the timer
    QTimer timer;
    QObject::connect(&timer, SIGNAL(timeout()), this, SLOT(update()));
    timer.start(500);
}

gamewindow::~gamewindow()
{
    delete ui;
}

QGraphicsView* gamewindow::GetGraphicsView(){
    return graphicsView;
}

//listens to keypresses from the user and does an action based on the key that was pressed
void gamewindow::keyPressEvent(QKeyEvent *event){
   if (event->key() == Qt::Key_A){
       std::cout<<"you pressed L key"<<std::endl;
       ginny->moveChar(0);
   }
   else if(event->key() == Qt::Key_D){
       std::cout<<"you pressed R key"<<std::endl;
       ginny->moveChar(1);
   }
   else if(event->key() == Qt::Key_Space){
       std::cout<<"you pressed the SPACE key"<<std::endl;
   }

}

//timer function... maybe
void gamewindow::moveEvent(QMoveEvent *event){
    std::cout << "hello" << std::endl;
}
