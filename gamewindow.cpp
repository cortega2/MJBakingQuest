#include "gamewindow.h"

//testcode
#include <iostream>

gamewindow::gamewindow(QWidget *parent, bool newGame, QString sessionName) :
    QMainWindow(parent),
    ui(new Ui::gamewindow)
{
    QString load;
    session = sessionName;
    if(newGame){
        load = "levels/defaultlevel";
    }
    else{
        load = "saved/"+ sessionName;
        //score and other stuff will go here or maybe lets not have a score but life count
    }

    nextLevel = "levels/defaultlevel";

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

    ginny->loadGame(load);

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
    //if it is safe to animate. It is not safe when mj has 0 life and we are reloading the level
    if(ginny->life<=0)
        return;

    //move left
    if (event->key() == Qt::Key_A)
           ginny->moveChar(-1);
    //move right
    else if(event->key() == Qt::Key_D)
           ginny->moveChar(1);
    //open door or pick up or drop block
    else if(event->key() == Qt::Key_Space){
        if(!(ginny->mjHasBlock))
            ginny->getBlock();
        else
            ginny->dropBlock();

        if(ginny->itemCount <=0){
            //open door and load next leve
            ginny->loadNext();
        }
    }
    //save game
    else if(event->key() == Qt::Key_P){
        if(!ginny->mjHasBlock)
            ginny->saveGame(session);
        else
            std::cout << "Can not save right now, put block down\n";
    }
}

//timer function... maybe
void gamewindow::moveEvent(){
    if(ginny->life<=0)
        return;

    ginny->moveEnemies();
    ginny->moveGood();
}
