/*! \abstract objects
 *    The objects class creates the brushes that paint all of the objects (characters, movable items, and scenery) in the game window.
 */

#include "objects.h"

QGraphicsRectWidget::~QGraphicsRectWidget(){
    delete brush;
    delete size;
}

QGraphicsRectWidget::QGraphicsRectWidget(){
    brush = new QBrush(Qt::gray,Qt::SolidPattern);
    size = new QRect();
}

QGraphicsRectWidget::QGraphicsRectWidget(Qt::GlobalColor color, int blockWidth, int blockHeight){
    brush = new QBrush(color,Qt::SolidPattern);
    size = new QRect(0,0, blockWidth, blockHeight);
}

QGraphicsRectWidget::QGraphicsRectWidget(QPixmap pMap, int blockWidth, int blockHeight){
    brush = new QBrush(pMap);
    size = new QRect(0,0, blockWidth, blockHeight);
}

QGraphicsRectWidget::QGraphicsRectWidget(const char* spriteName, int blockWidth, int blockHeight){
    brush= new QBrush( QPixmap(spriteName) );
    size = new QRect(0,0, blockWidth, blockHeight);
}

/************************Not Used Right now****************************************************
void BlockArray::AddBlock(unsigned int xLocation, unsigned int yLocation, BlockObject *block ){
    board[xLocation][yLocation] = block;

    if ( block->isStandable ){
        standableBlocks << block;
    }

}

BlockArray::BlockArray(int width, int height){

    board = new BlockObject**[width];

    for (int i = 0; i < width; ++i) {
      board[i] = new BlockObject*[height];
    }

    for (int i = 0; i < width; ++i) {   // for each row
      for (int j = 0; j < height; ++j) { // for each column
        board[i][j] = NULL;
      }
    }
}

BlockObject::BlockObject( QGraphicsWidget *block, bool isStandable, bool isPickupable, bool isPowerUp, bool isNPC ){
    this->block = block;

    this->isStandable = isStandable;
    this->isPickupable = isPickupable;
    this->isNPC = isNPC;
    this->isPowerUp = isPowerUp;
}

BlockObject::~BlockObject(){
    delete block;
}
*/
