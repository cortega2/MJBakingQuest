#include "gamewindow.h"

//testcode
#include <iostream>

gamewindow::gamewindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::gamewindow)
{
    left = 2;
    right = -2;

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
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(moveEvent()));
    timer->start(500);

    mjHasBlock = false;


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
    //move left
    if (event->key() == Qt::Key_A)
           ginny->moveChar(-1);
    //move right
    else if(event->key() == Qt::Key_D)
           ginny->moveChar(1);
    //pick up or drop block
    else if(event->key() == Qt::Key_Space){
        if(!(ginny->mjHasBlock))
            ginny->getBlock();
        else
            ginny->dropBlock();
    }
    //save game
    else if(event->key() == Qt::Key_S){
        //dummy for now
        ginny->saveGame(" ");
    }

}

//timer function... maybe
void gamewindow::moveEvent(){
    ginny->moveEnemies();
}
