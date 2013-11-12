/*
 * engine.cpp
 * Originally Authored by Joseph Burnitz
 * renders the game
 *
 * TODO: as of 10/24/2013
 * *Remove the need of mainwindow.h
 * *Seperate out the file reading part
 * *Make a real, robust level parser; possibly put into own class
 *   *Make datastructure class for keeeping track of the objects generated
*/

#include "engine.h"

//test code
#include <iostream>

#define BLOCK_SIZE ( 30 )

engine::engine(){
    spritesAndStuff = new objStructure();
    parsley = new parser();
}

engine::engine( QGraphicsScene *scene ){
    uiScene = scene;
}

engine::~engine(){
    delete sSize;
    delete uiScene;
    delete spritesAndStuff;
    delete parsley;
}

/* returns a pointer to the current graphics scene */
QGraphicsScene* engine::GetScene(){
    return uiScene;
}
void engine::SetScene(QGraphicsScene *scene){
    uiScene = scene;
}

void engine::AddSprite(const char* spriteFName, int xLoc, int yLoc ){
    QGraphicsRectWidget *tmp = new QGraphicsRectWidget( spriteFName, BLOCK_SIZE, BLOCK_SIZE );
    tmp->setFlag(QGraphicsItem::ItemIsMovable, true);
    MoveBlock(tmp, uiScene, xLoc, yLoc );
    uiScene->addItem(tmp);
}

void engine::SetParentWindow( QWidget *pWindow ){
    parentWindow = pWindow;
}

/* Moves a block by offset of their size
 * 0,0 is in the lower left, e.g. Quadrant 1 */
void engine::MoveBlock(QGraphicsWidget *box, QGraphicsScene *scene, int x, int yOffset){
    box->moveBy(BLOCK_SIZE*x,scene->height()-BLOCK_SIZE*yOffset);
}

/* Draws a grid lines through the
 * scene for line up/snap to purposes */
void engine::DrawGrid(QGraphicsScene *scene){
    int gridWidth = (scene->width())/BLOCK_SIZE;
    int gridHeight = (scene->height())/BLOCK_SIZE;

    for(int x=1; x<=gridWidth; x++){
        scene->addLine(BLOCK_SIZE*x, 0, BLOCK_SIZE*x, BLOCK_SIZE*gridHeight,QPen(Qt::red));
    }
    for(int y=gridHeight; y>=0; y--){
        scene->addLine(0, BLOCK_SIZE*y, BLOCK_SIZE*gridWidth, BLOCK_SIZE*y,QPen(Qt::red));
    }
}

/* Loads a map into the Graphics Scene
 * Open a file chooser dialog */
int engine::LoadMap(QGraphicsScene *scene){
    parsley->readFile( parentWindow, spritesAndStuff, NULL );

    Node *tmp = spritesAndStuff->head;
    while(tmp != 0){
        if(tmp->blockType.compare( QString("BACKGROUND")) == 0)
            scene->setBackgroundBrush(QBrush(Qt::black, QPixmap(tmp->location)));
        else{
            tmp->sprite = new QGraphicsRectWidget(QPixmap(tmp->location), BLOCK_SIZE, BLOCK_SIZE);
            MoveBlock(tmp->sprite, scene, tmp->x, tmp->y);
            scene->addItem(tmp->sprite);


        }
        tmp = tmp->next;
    }
    return 1;
}

/* Loads the level file specified by the fileName
 * Useful for autoloading the next level upon winning
 * it's almost identical to the one above it */
int engine::LoadMap(QGraphicsScene *scene, QString fileName){
    parsley->readFile(parentWindow, spritesAndStuff, fileName );

    Node *tmp = spritesAndStuff->head;
    while(tmp != 0){
        if(tmp->blockType.compare( QString("BACKGROUND")) == 0)
            scene->setBackgroundBrush(QBrush(Qt::black, QPixmap(tmp->location)));
        else{
            tmp->sprite = new QGraphicsRectWidget(QPixmap(tmp->location), BLOCK_SIZE, BLOCK_SIZE);
            MoveBlock(tmp->sprite, scene, tmp->x, tmp->y);
            scene->addItem(tmp->sprite);

            //test code
            if(tmp->location.compare(QString("sprites/MJ_left.png")) == 0){
                mj = tmp;
                //mj = tmp->sprite;
            }
            //end test code
        }
        tmp = tmp->next;
    }
    return 1;
}

//loads level without the file chooser, for now default level
void engine::loadGame(QString level){
    LoadMap(uiScene, level);
}

/* Opens the file chooser dialog and loads the map */
void engine::ClickedOpenMap(void){
    LoadMap(uiScene);
}

/* Clears out the scene */
void engine::CloseMap(void){
    //AskToSave...
    qDeleteAll( uiScene->items() );
    uiScene->setBackgroundBrush(QBrush(Qt::white));
}

void engine::ClickedDrawGridLines(void){
    DrawGrid( uiScene );
}

// test code //
void engine::moveChar(int direction){
    if(direction == 0){
        std::cout << "move left" << std::endl;
        mj->sprite->moveBy(-30,0);
        mj->x = mj->x - 1;
    }
    else if(direction == 1){
        std::cout << "move right" << std::endl;
        mj->sprite->moveBy(30,0);
        mj->x = mj->x + 1;
    }
}
