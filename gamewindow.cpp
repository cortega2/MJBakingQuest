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

    ginny->loadGame("levels/levelone.txt");

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
    if (event->key() == Qt::Key_A){
           std::cout<<"hello you pressed L key"<<std::endl;
           ginny->moveChar(left, mjHasBlock);
           left=left+2;
       }
       else if(event->key() == Qt::Key_D){
           std::cout<<"hello you pressed R key"<<std::endl;
           ginny->moveChar(right, mjHasBlock);
           right=right-2;
       }
       else if(event->key() == Qt::Key_Space){
           std::cout<<"hello you pressed the SPACE key"<<std::endl;
       }

}

//timer function... maybe
void gamewindow::moveEvent(){
    ginny->moveEnemies();
}

//check to see if 1 mouse click is over a wood block, and 2 if mj is by the wood block to be able to pick it up
void gamewindow::mousePressEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        QPoint point = event->pos();
        int x = point.x()/30;
        int y = 20 - point.y()/30;
        if(ginny->walkable[y-1][x]!= 0 && ginny->walkable[y-1][x]->blockType.compare("MBLOCK") == 0){
            std::cout<< "you clicked wood" << std::endl;
            //check to see if mj is in the surrounding area, if yes then mj picks up block
            int mjX = ginny->mj->x;
            int mjY = ginny->mj->y;
            if((ginny->mj->sprite->collidesWithItem(ginny->walkable[y-1][x]->sprite)) && (x!= mjX || (y-1)!= mjY)){
                std::cout<< "it collides" << std::endl;
                ginny->walkable[y-1][x]->sprite->moveBy((mjX - x) * 30, -(mjY -y+1) * 30);
                ginny->walkable[mjY][mjX] = ginny->walkable[y-1][x];
                ginny->walkable[y-1][x] = 0;
                //might have to update block's location on the node

                mjHasBlock = true;
            }
            /*
            if((mjX+1 == x && mjY + 1 == y) || (mjX+1 == x && mjY == y) || (mjX+1 == x && mjY - 1 == y) ||
            (mjX == x && mjY - 1 == y) || (mjX - 1 == x && mjY - 1 == y) || (mjX - 1 == x && mjY == y) || (mjX -1 == x && mjY +1 == y)){
                std::cout << "pick up" << std::endl;
                ginny->walkable[y-1][x]->sprite->moveBy((mjX - x) * 30, -(mjY -y+1) * 30);
                ginny->walkable[mjY][mjX] = ginny->walkable[y-1][x];
                ginny->walkable[y-1][x] = 0;

            }
            */
        }
    }
}
