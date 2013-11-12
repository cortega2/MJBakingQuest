#include "objects.h"
#define BLOCK_SIZE (30)

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
GraphicsViewEditor::GraphicsViewEditor(){
    rightClickMenu = new QTableWidget(this);
    //rightClickMenu->setFixedWidth(BLOCK_SIZE+10);
    rightClickMenu->hide();

    //finds just the pngs in the sprites incase of accidents
    QStringList nameFilter("*.png");
    QDir directory(QString("sprites/"));
    QStringList spritesList = directory.entryList(nameFilter);

    //Sets up the rightclick menu
    rightClickMenu->setIconSize(QSize(BLOCK_SIZE,BLOCK_SIZE));
    rightClickMenu->setColumnCount( 5 );
    rightClickMenu->setRowCount( static_cast<int>(ceil(spritesList.size()/5)) );
    for(int i=0; i<rightClickMenu->columnCount(); i++)
        rightClickMenu->setColumnWidth( i, BLOCK_SIZE );
    rightClickMenu->setShowGrid(false);
    rightClickMenu->setMaximumWidth(rightClickMenu->columnCount()*BLOCK_SIZE + rightClickMenu->columnCount() );
    rightClickMenu->setMaximumHeight(rightClickMenu->rowCount()*BLOCK_SIZE + rightClickMenu->rowCount() );
    rightClickMenu->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    rightClickMenu->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    rightClickMenu->verticalHeader()->setVisible(false);
    rightClickMenu->horizontalHeader()->setVisible(false);
    rightClickMenu->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QTableWidgetItem *item;
    QIcon *ico;

    //fills the table with the sprites
    int k=0;
    for(int i=0; i<rightClickMenu->columnCount(); i++){
        for(int j=0; j<rightClickMenu->rowCount(); j++){
            item = new QTableWidgetItem();
            ico = new QIcon("sprites/"+spritesList.at(k));

            item->setIcon( *ico );
            item->setSizeHint(QSize(item->sizeHint().width(), BLOCK_SIZE ));

            rightClickMenu->setItem( i,j, item );
            k++;
        }
    }

    rightClickMenu->setCursor(Qt::ArrowCursor);
}

void GraphicsViewEditor::mousePressEvent(QMouseEvent * event){
    if(event->button() == Qt::LeftButton ){
        this->setCursor(QCursor(Qt::ClosedHandCursor));
        rightClickMenu->hide();
    }

    if(event->button() == Qt::RightButton ){
        rightClickMenu->move(event->pos());
        //rightClickMenu->
        rightClickMenu->show();
    }
}
void GraphicsViewEditor::mouseReleaseEvent(QMouseEvent * event){
    if(event->button() == Qt::LeftButton ){
        this->setCursor(QCursor(Qt::OpenHandCursor));
    }

    if(event->button() == Qt::RightButton ){
        //rightClickMenu->hide();
    }
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
