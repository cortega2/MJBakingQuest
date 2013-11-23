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
    goodGuys = new objStructure();
    enemies = new objStructure();
    blocks = new objStructure();
    other = new objStructure();
    parsley = new parser();
    facing = 0;
    prevFacing = 0;
    mjHasBlock = false;

    //initialize array that holds politers to walkable blocks
    //useful for moving
    for(int y = 0; y< 20; y++){
        for(int x = 0; x<30; x++)
            walkable[y][x] = 0;
    }

}

engine::engine( QGraphicsScene *scene ){
    uiScene = scene;
}

engine::~engine(){
    delete sSize;
    delete uiScene;
    delete goodGuys;
    delete enemies;
    delete blocks;
    delete other;
    delete walkable;
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
    //tmp->setFlag(QGraphicsItem::ItemIsSelectable, true);
    MoveBlock(tmp, uiScene, xLoc, yLoc );
    tmp->setCursor(Qt::OpenHandCursor);
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
    parsley->readFile( parentWindow, goodGuys, enemies, blocks, other, NULL );

    Node *tmp = goodGuys->head;
    while(tmp != 0){
        QString spriteName("sprites/");
        spriteName.append(tmp->location.trimmed());
        spriteName.append(".png");

        tmp->sprite = new QGraphicsRectWidget(QPixmap(spriteName), BLOCK_SIZE, BLOCK_SIZE);
        MoveBlock(tmp->sprite, scene, tmp->x, tmp->y);
        //std::cout<< tmp->x<< std::endl << tmp->y << std::endl;
        scene->addItem(tmp->sprite);
        //asign node to MJ
        if(tmp->blockType.compare(QString("MJ")) == 0){
            mj = tmp;
        }
        tmp = tmp->next;
    }

    tmp = enemies->head;
    while(tmp != 0){
        QString spriteName("sprites/");
        spriteName.append(tmp->location.trimmed());
        spriteName.append(".png");

        tmp->sprite = new QGraphicsRectWidget(QPixmap(spriteName), BLOCK_SIZE, BLOCK_SIZE);
        MoveBlock(tmp->sprite, scene, tmp->x, tmp->y);
        scene->addItem(tmp->sprite);
        tmp = tmp->next;
    }

    tmp = blocks->head;
    while(tmp != 0){
        QString spriteName("sprites/");
        spriteName.append(tmp->location.trimmed());
        spriteName.append(".png");

        tmp->sprite = new QGraphicsRectWidget(QPixmap(spriteName), BLOCK_SIZE, BLOCK_SIZE);
        MoveBlock(tmp->sprite, scene, tmp->x, tmp->y);
        scene->addItem(tmp->sprite);
        //walkable[tmp->x][tmp->y-1] = tmp; Might no be needed here... Not sure
        tmp = tmp->next;
    }

    tmp = other->head;
    while(tmp != 0){

        QString spriteName("sprites/");
        spriteName.append(tmp->location.trimmed());
        spriteName.append(".png");

        if(tmp->blockType.compare( QString("BACKGROUND")) == 0)
            scene->setBackgroundBrush(QBrush(Qt::black, QPixmap(spriteName)));
        else{
            tmp->sprite = new QGraphicsRectWidget(QPixmap(spriteName), BLOCK_SIZE, BLOCK_SIZE);
            MoveBlock(tmp->sprite, scene, tmp->x, tmp->y);
            scene->addItem(tmp->sprite);
            tmp->sprite->setZValue(-1);
        }
        tmp = tmp->next;
    }

    return 1;
}

/* Loads the level file specified by the fileName
 * Useful for autoloading the next level upon winning
 * it's almost identical to the one above it */
int engine::LoadMap(QGraphicsScene *scene, QString fileName){

    parsley->readFile(parentWindow, goodGuys, enemies, blocks, other, fileName );

    Node *tmp = goodGuys->head;
    while(tmp != 0){
        QString spriteName("sprites/");
        spriteName.append(tmp->location.trimmed());
        spriteName.append(".png");

        tmp->sprite = new QGraphicsRectWidget(QPixmap(spriteName), BLOCK_SIZE, BLOCK_SIZE);
        MoveBlock(tmp->sprite, scene, tmp->x, tmp->y);
        //std::cout<< tmp->x<< std::endl << tmp->y << std::endl;
        scene->addItem(tmp->sprite);
        //asign node to MJ
        if(tmp->blockType.compare(QString("MJ")) == 0){
            mj = tmp;
        }

        else{
            //set movement to either left or right
            QTime time = QTime::currentTime();
            qsrand((uint)time.msec());
            tmp->movement = qrand() %(2);
        }
        tmp = tmp->next;
    }

    tmp = enemies->head;
    while(tmp != 0){
        QString spriteName("sprites/");
        spriteName.append(tmp->location.trimmed());
        spriteName.append(".png");

        tmp->sprite = new QGraphicsRectWidget(QPixmap(spriteName), BLOCK_SIZE, BLOCK_SIZE);
        MoveBlock(tmp->sprite, scene, tmp->x, tmp->y);
        scene->addItem(tmp->sprite);

        //set movement to either left or right
        QTime time = QTime::currentTime();
        qsrand((uint)time.msec());
        tmp->movement = qrand() %(2);

        tmp = tmp->next;
    }

    tmp = blocks->head;
    while(tmp != 0){
        QString spriteName("sprites/");
        spriteName.append(tmp->location.trimmed());
        spriteName.append(".png");

        tmp->sprite = new QGraphicsRectWidget(QPixmap(spriteName), BLOCK_SIZE, BLOCK_SIZE);
        MoveBlock(tmp->sprite, scene, tmp->x, tmp->y);
        scene->addItem(tmp->sprite);
        walkable[tmp->y-1][tmp->x] = tmp;
        tmp = tmp->next;
    }

    tmp = other->head;
    while(tmp != 0){

        QString spriteName("sprites/");
        spriteName.append(tmp->location.trimmed());
        spriteName.append(".png");

        if(tmp->blockType.compare( QString("BACKGROUND")) == 0)
            scene->setBackgroundBrush(QBrush(Qt::black, QPixmap(spriteName)));
        else{
            tmp->sprite = new QGraphicsRectWidget(QPixmap(spriteName), BLOCK_SIZE, BLOCK_SIZE);
            MoveBlock(tmp->sprite, scene, tmp->x, tmp->y);
            scene->addItem(tmp->sprite);
            tmp->sprite->setZValue(-1);
        }
        tmp = tmp->next;
    }
    return 1;
}

void engine::saveGame(QString name){
    //dummy for now
    parsley->createFile(name, goodGuys, enemies, blocks, other);
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

void engine::setBrush(){
    brush = new QBrush( QPixmap(newName) );
}

void engine::setNewName (QString subName){
    newName = "sprites/";
    newName.append(subName);
    newName.append(".png");
}

/*method that is used to move mj
 *THINGS TO DO: when mj moves up and is carrying a block, check to make sure the block fits in the space
 *ie, make sure blocks dont go through each other
 */
void engine::moveChar(int direction){

    int mjPrevX = mj->x;
    int mjPrevY = mj->y;
    if(facing == -direction || facing == 0)
        facing = facing + direction;

    //face left
    if (facing == -1){
        if (mjHasBlock)
            setNewName("MJ_move_left_up");
        else
            setNewName("MJ_move_left");
    }
    //face right
    else if (facing == 1){
        if (mjHasBlock){
            setNewName("MJ_move_right_up");
        }
        else
            setNewName("MJ_move");
    }
    //face foward
    else if (facing == 0){
        if (mjHasBlock)
            setNewName("MJ_left_up");
        else
        setNewName("MJ_left");
    }
    mj->sprite->brush=new QBrush( QPixmap(newName) );
    mj->sprite->update();

    //move left
    if(direction < 0 && prevFacing == facing){

        //going down
        if(walkable[mj->y-1][mj->x-1] == NULL && walkable[mj->y-2][mj->x-1] == NULL && walkable[mj->y-3][mj->x-1] != NULL){
            mj->sprite->moveBy(-BLOCK_SIZE, BLOCK_SIZE);
            mj->x =mj->x - 1;
            mj->y = mj->y - 1;

            //move block and update block on array
            if(mjHasBlock){
                walkable[mjPrevY][mjPrevX]->sprite->moveBy(-BLOCK_SIZE, BLOCK_SIZE);
                walkable[mj->y][mj->x] =  walkable[mjPrevY][mjPrevX];
                walkable[mjPrevY][mjPrevX] = NULL;

            }
        }
        //going up
        else if(walkable[mj->y-1][mj->x-1] != NULL && walkable[mj->y][mj->x-1] == NULL){
            //move block and update block on array
            if(mjHasBlock && walkable[mj->y+1][mj->x-1] == NULL){
                mj->sprite->moveBy(-BLOCK_SIZE, -BLOCK_SIZE);
                mj->x =mj->x - 1;
                mj->y = mj->y + 1;

                walkable[mjPrevY][mjPrevX]->sprite->moveBy(-BLOCK_SIZE, -BLOCK_SIZE);
                walkable[mj->y][mj->x] =  walkable[mjPrevY][mjPrevX];
                walkable[mjPrevY][mjPrevX] = NULL;
            }
            else if(!mjHasBlock){
                mj->sprite->moveBy(-BLOCK_SIZE, -BLOCK_SIZE);
                mj->x =mj->x - 1;
                mj->y = mj->y + 1;
            }
        }
        else if( mj->x != 0 && walkable[mj->y-2][mj->x-1] != NULL && walkable[mj->y-1][mj->x-1] == NULL){

             //move block and update block on array
            if(mjHasBlock && walkable[mj->y][mj->x - 1] == NULL){
                mj->sprite->moveBy(-BLOCK_SIZE,0);
                mj->x = mj->x - 1;

                walkable[mjPrevY][mjPrevX]->sprite->moveBy(-BLOCK_SIZE, 0);
                walkable[mj->y][mj->x] =  walkable[mjPrevY][mjPrevX];
                walkable[mjPrevY][mjPrevX] = NULL;
            }
            else if(!mjHasBlock){
                mj->sprite->moveBy(-BLOCK_SIZE,0);
                mj->x = mj->x - 1;
            }
        }
    }
    //right
    else if(direction > 0 && prevFacing == facing){
        //going up
        if(walkable[mj->y-1][mj->x+1] != NULL && walkable[mj->y][mj->x+1] == NULL){

            if(mjHasBlock && walkable[mj->y+1][mj->x+1] == NULL){
                mj->sprite->moveBy(BLOCK_SIZE, -BLOCK_SIZE);
                mj->x = mj->x + 1;
                mj->y = mj->y + 1;

                walkable[mjPrevY][mjPrevX]->sprite->moveBy(BLOCK_SIZE, -BLOCK_SIZE);
                walkable[mj->y][mj->x] =  walkable[mjPrevY][mjPrevX];
                walkable[mjPrevY][mjPrevX] = NULL;
            }
            //move block and update block on array
            else if(!mjHasBlock){
                mj->sprite->moveBy(BLOCK_SIZE, -BLOCK_SIZE);
                mj->x = mj->x + 1;
                mj->y = mj->y + 1;
            }
        }
        //going down
        else if(walkable[mj->y-1][mj->x+1] == NULL && walkable[mj->y-2][mj->x+1] == NULL && walkable[mj->y-3][mj->x+1] != NULL){
            mj->sprite->moveBy(BLOCK_SIZE, BLOCK_SIZE);
            mj->x = mj->x + 1;
            mj->y = mj->y - 1;

            //move block and update block on array
            if(mjHasBlock){
                walkable[mjPrevY][mjPrevX]->sprite->moveBy(BLOCK_SIZE, BLOCK_SIZE);
                walkable[mj->y][mj->x] =  walkable[mjPrevY][mjPrevX];
                walkable[mjPrevY][mjPrevX] = NULL;

            }
        }
        else if(mj->x != 29 && walkable[mj->y-2][mj->x+1] != NULL && walkable[mj->y-1][mj->x+1] == NULL){
            //move block and update block on array
            if(mjHasBlock && walkable[mj->y][mj->x+1] == NULL){
                mj->sprite->moveBy(BLOCK_SIZE,0);
                mj->x = mj->x + 1;

                walkable[mjPrevY][mjPrevX]->sprite->moveBy(BLOCK_SIZE, 0);
                walkable[mj->y][mj->x] =  walkable[mjPrevY][mjPrevX];
                walkable[mjPrevY][mjPrevX] = NULL;
            }
            else if(!mjHasBlock){
                mj->sprite->moveBy(BLOCK_SIZE,0);
                mj->x = mj->x + 1;
            }
        }
    }

    prevFacing = facing;
}

//moves the good characters
void engine::moveGood(){
    Node *tmp = goodGuys->head;
    while(tmp != 0){
        int direction = tmp->movement;
        //left
        if(direction == 0){
            if( tmp->x != 0 && walkable[tmp->y-2][tmp->x-1] != NULL && walkable[tmp->y-1][tmp->x-1] == NULL){
                tmp->sprite->moveBy(-BLOCK_SIZE,0);
                tmp->x = tmp->x - 1;
            }
            //at edge, turn right
            else if(tmp->x != 29 && walkable[tmp->y-2][tmp->x+1] != NULL){

                /*tmp->sprite->moveBy(BLOCK_SIZE,0);
                tmp->x = tmp->x + 1;
                */
                //animate sprite here
                tmp->movement = 1;
            }
        }
        //right
        else if(direction == 1){
            if(tmp->x != 29 && walkable[tmp->y-2][tmp->x+1] != NULL && walkable[tmp->y-1][tmp->x+1] == NULL){
                tmp->sprite->moveBy(BLOCK_SIZE,0);
                tmp->x = tmp->x + 1;
            }
            //at edge turn left
            else if( tmp->x != 0 && walkable[tmp->y-2][tmp->x-1] != NULL ){
                /*
                tmp->sprite->moveBy(-BLOCK_SIZE,0);
                tmp->x = tmp->x - 1;
                */

                //animate sprite here
                tmp->movement = 0;
            }
        }
        tmp = tmp->next;
    }
}

//moves the enemies
void engine::moveEnemies(){
    Node *tmp = enemies->head;
    while(tmp != 0){
        int direction = tmp->movement;
        //left
        if(direction == 0){
            if( tmp->x != 0 && walkable[tmp->y-2][tmp->x-1] != NULL && walkable[tmp->y-1][tmp->x-1] == NULL){
                tmp->sprite->moveBy(-BLOCK_SIZE,0);
                tmp->x = tmp->x - 1;
            }
            //at edge, turn right
            else if(tmp->x != 29 && walkable[tmp->y-2][tmp->x+1] != NULL){

                /*tmp->sprite->moveBy(BLOCK_SIZE,0);
                tmp->x = tmp->x + 1;
                */
                //animate sprite here
                tmp->movement = 1;
            }
        }
        //right
        else if(direction == 1){
            if(tmp->x != 29 && walkable[tmp->y-2][tmp->x+1] != NULL && walkable[tmp->y-1][tmp->x+1] == NULL){
                tmp->sprite->moveBy(BLOCK_SIZE,0);
                tmp->x = tmp->x + 1;
            }
            //at edge turn left
            else if( tmp->x != 0 && walkable[tmp->y-2][tmp->x-1] != NULL ){
                /*
                tmp->sprite->moveBy(-BLOCK_SIZE,0);
                tmp->x = tmp->x - 1;
                */

                //animate sprite here
                tmp->movement = 0;
            }
        }
        tmp = tmp->next;
    }
}

/*Still needs improvement
 *right now if mj picks a block under her feet she is moves down,
 *but she still needs to be able to pick up blocks that are diagnal from her
 */
void engine::getBlock(){
    int y = mj->y;
    int x = mj->x + facing;
    if(facing ==0)
        y = y - 1;

    //needs to be updated
    //checks to see if the block that mj is facing is of type MBLOCK
    if(walkable[y-1][x]!= 0 && walkable[y-1][x]->blockType.compare("MBLOCK") == 0){
        int mjX = mj->x;
        int mjY = mj->y;

        if(facing == 0){
            walkable[y-1][x]->sprite->moveBy(0, -BLOCK_SIZE);
            walkable[mjY-1][mjX] = walkable[y-1][x];
            walkable[y-1][x] = 0;

            mj->sprite->moveBy(0, BLOCK_SIZE);
            mj->y = mj->y-1;

            //might have to update block's location on the node
        }
        else{
            walkable[y-1][x]->sprite->moveBy((mjX - x) * 30, -(mjY -y+1) * 30);
            walkable[mjY][mjX] = walkable[y-1][x];
            walkable[y-1][x] = 0;

            //might have to update block's location on the node
        }
        mjHasBlock = true;
    }
}

//using mj's position we find the position of the block she is carrying and check to see if the place where
//the player wants to drop it is a legal place, ie there is no block there.
//NEEDS CLEAN UP!
void engine::dropBlock(){

    //has to face left or right
    if(facing == 0)
        return;

    //get x y for block to be used in the walkable array
    int blockY = mj->y;
    int blockX = mj->x;

    //place block
    Node *ptr;
    if(walkable[blockY][blockX + facing] == NULL){
        walkable[blockY][blockX]->sprite->moveBy(facing * 30, 0);
        walkable[blockY][blockX]->x = blockX + facing;
        walkable[blockY][blockX]->y = blockY + 1;

        walkable[blockY][blockX + facing] = walkable[blockY][blockX];
        walkable[blockY][blockX] = NULL;
        ptr = walkable[blockY][blockX + facing];

        //move block down if possible
        Node *tmp = walkable[blockY - 1][blockX + facing];
        int count = 0;
        while(tmp == NULL){
            walkable[blockY - count][blockX + facing]->sprite->moveBy(0, BLOCK_SIZE);
            walkable[blockY - count][blockX + facing]->y = walkable[blockY - count][blockX + facing]->y - 1;

            walkable[blockY - count - 1][blockX + facing] = walkable[blockY - count][blockX + facing];
            walkable[blockY - count][blockX + facing] = NULL;


            ptr = walkable[blockY - count - 1][blockX + facing];

            count ++;
            tmp = walkable[blockY - 1 - count][blockX + facing];
        }

        //check to see if enemy got crushed
        tmp = enemies->head;
        while(tmp != 0){
            if((ptr->x == tmp->x) && (ptr->y == tmp->y)){
                std::cout << "enemy got crushed!\n";

                //BAD FIX THIS ASAP!!!

                tmp->sprite->hide();
                enemies->remove(tmp);
            }
            tmp = tmp->next;
        }
        //update mj block status
        mjHasBlock = false;
    }

}
