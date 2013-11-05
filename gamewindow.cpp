#include "gamewindow.h"

//testcode
#include <iostream>

gamewindow::gamewindow(QWidget *parent, engine *gin, QGraphicsScene *uiScene, int BLOCK_SIZE) :
    QWidget(parent),
    ui(new Ui::gamewindow)
{
    ui->setupUi(this);
    ginny = gin;

    ui->graphicsView->setGeometry( QRect(4,4,BLOCK_SIZE*30,BLOCK_SIZE*20) );
    ui->graphicsView->setScene( uiScene );
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ginny->loadGame("levels/defaultlevel");
}

gamewindow::~gamewindow()
{
    delete ui;
}

//listens to keypresses from the user and does an action based on the key that was pressed
void gamewindow::keyPressEvent(QKeyEvent *event){
   if (event->key() == Qt::Key_A){
       std::cout<<"hello you pressed L key"<<std::endl;
       ginny->moveChar(0);
   }
   else if(event->key() == Qt::Key_D){
       std::cout<<"hello you pressed R key"<<std::endl;
       ginny->moveChar(1);
   }
   else if(event->key() == Qt::Key_Space){
       std::cout<<"hello you pressed the SPACE key"<<std::endl;
   }

}
