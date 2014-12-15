/*! \abstract Graphicsvieweditor
 *         The GraphicsViewEditor is the class that sets up the level editor tool. The class creates a grid menu that displays all of the available sprites
 *         for the user tocreate their level. It also defines how the user uses the tool through the mouse.
 */

#include "graphicsvieweditor.h"

/*! \abstract GraphicsViewEditor::cellDoubleClicked
 * opens menu of sprites when the leveleditor is right clicked. if
 * a sprite is right clicked the sprite alone is added to the
 * screen.
 */
void GraphicsViewEditor::cellDoubleClicked(int row, int column){
    ginny->AddSprite(rightClickMenu->item(row,column)->text().toStdString().c_str(),
                     (int)floor(rightClickMenu->x()/BLOCK_SIZE),
                     (int)floor( (ginny->GetScene()->height()-(rightClickMenu->y()))/BLOCK_SIZE) );

    QString type;

    if( this->mBlockChecked )
        type.append("MBLOCK");
    else
        type.append("BLOCK");

    //this adds blocks to the thing inputting a stripped file name
    ginny->blocks->add( type,
                        rightClickMenu->item(row,column)->text().section(".",0,0).mid(8),
                       (int)floor(rightClickMenu->x()/BLOCK_SIZE),
                       (int)floor( (ginny->GetScene()->height()-(rightClickMenu->y()))/BLOCK_SIZE) );

    rightClickMenu->hide();
}

/*! \abstract GraphicsViewEditor::GraphicsViewEditor
 * Connects right click to the double right click which is the action desired
 * for adding sprites to the screen. It also connects the picture to the action
 * so that the sprite alone shows on the screen. And it sets up the table for
 * the sprite menu.
 */
GraphicsViewEditor::GraphicsViewEditor(engine *gin){
    //gives us a local reference to the engine
    ginny = gin;

    mBlockChecked = true;

    rightClickMenu = new QTableWidget( this );

    //connecting the doubleClick signal in the right click menu to the action
    connect(rightClickMenu, SIGNAL(cellDoubleClicked(int, int)), this, SLOT(cellDoubleClicked(int,int)));

    //this makes sure it isn't shown until it is ready to be shown
    rightClickMenu->hide();

    //finds just the pngs in the sprites incase of accidents
    QStringList nameFilter("*.png");
    QDir directory(QString("sprites/"));
    QStringList spritesList = directory.entryList(nameFilter);

    //Sets up the rightclick menu
    //making enough room to hold all sprites
    rightClickMenu->setIconSize(QSize(BLOCK_SIZE,BLOCK_SIZE));
    rightClickMenu->setColumnCount( 5 );
    rightClickMenu->setRowCount( static_cast<int>(ceil(spritesList.size()/5)) );
    for(int i=0; i<rightClickMenu->columnCount(); i++)
        rightClickMenu->setColumnWidth( i, BLOCK_SIZE+2 );
    for(int i=0; i<rightClickMenu->rowCount(); i++)
        rightClickMenu->setRowHeight( i, BLOCK_SIZE+2 );

    rightClickMenu->setShowGrid(false);

    //ensures the container for the sprites menu is exactly fitting
    rightClickMenu->setMaximumWidth(rightClickMenu->columnWidth(0) * rightClickMenu->columnCount() );
    rightClickMenu->setMinimumWidth(rightClickMenu->columnWidth(0) * rightClickMenu->columnCount() );
    rightClickMenu->setMaximumHeight( rightClickMenu->rowHeight(0) * rightClickMenu->rowCount() );
    rightClickMenu->setMinimumHeight( rightClickMenu->rowHeight(0) * rightClickMenu->rowCount() );

    //I didn't want the scrollbars, etc showing up when a user right clicks
    //this makes it be just the sprites
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
            //item->setText(QString("sprites/"+spritesList.at(k)));
            item->setText(QString("sprites/"+spritesList.at(k)));
            item->setSizeHint(QSize(item->sizeHint().width(), BLOCK_SIZE ));

            rightClickMenu->setItem( j,i, item );
            k++;
        }
    }


    rightClickMenu->setCursor(Qt::ArrowCursor);
}

/*! \abstract GraphicsViewEditor::mousePressEvent
 * Connects mouse press signals for clicking the sprite menu and holding the
 * selected sprites
 */
void GraphicsViewEditor::mousePressEvent(QMouseEvent * event){
    if(event->button() == Qt::LeftButton ){
        this->setCursor(QCursor(Qt::ClosedHandCursor));
        rightClickMenu->hide();
    }

    if(event->button() == Qt::RightButton ){
        rightClickMenu->move(event->pos());
        rightClickMenu->show();
    }
}

/*! \abstract GraphicsViewEditor::SnapToGrid()
 * Sets up snap to grid so that when sprites are dragged into a position on
 * screen it locks in to the square coordinate position
 */
void GraphicsViewEditor::SnapToGrid(){
    QList<QGraphicsItem*> list = this->items();

    foreach( QGraphicsItem *item, list ){
        if(item != NULL ){
            if( ((int)item->x() % BLOCK_SIZE) <= BLOCK_SIZE/2 ){
                while( ((int)item->x() % BLOCK_SIZE) != 0){
                    item->moveBy(-1,0);
                }
            }else{
                while( ((int)item->x() % BLOCK_SIZE) != 0){
                    item->moveBy(1,0);
                }
            }
            if( ((int)item->y() % BLOCK_SIZE) <= BLOCK_SIZE/2 ){
                while( ((int)item->y() % BLOCK_SIZE) != 0){
                    item->moveBy(0,-1);
                }
            }else{
                while( ((int)item->y() % BLOCK_SIZE) != 0){
                    item->moveBy(0,1);
                }
            }
        }
    }
}

/*! \abstract GraphicsViewEditor::mouseReleaseEvent()
 * Allows for dragging the sprite around to position it using the mouse release
 * and it snaps to the grid
 */
void GraphicsViewEditor::mouseReleaseEvent(QMouseEvent * event){
    if(event->button() == Qt::LeftButton ){
        this->setCursor(QCursor(Qt::ArrowCursor));
    }if(this->AutoSnap){
        this->SnapToGrid();

        //I should have subclasses how the graphicsscene holds items and redid this whole thing,
        //that would have made everything wayyyyyy easier. ohwell
        if ( ginny->blocks->tail && this->itemAt(event->pos()) ){
            ginny->blocks->tail->x = (int)floor( this->itemAt(event->pos())->x()/BLOCK_SIZE);
            ginny->blocks->tail->y = (int)floor( (ginny->GetScene()->height()-( this->itemAt( event->pos())->y())) / BLOCK_SIZE);
            qDebug() << ginny->blocks->tail->y;
            qDebug() << ginny->blocks->tail->x;
        }
    }
}
