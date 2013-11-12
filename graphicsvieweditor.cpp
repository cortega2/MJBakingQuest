#include "graphicsvieweditor.h"


void GraphicsViewEditor::cellDoubleClicked(int row, int column){
    ginny->AddSprite(rightClickMenu->item(row,column)->text().toStdString().c_str(), (int)floor(rightClickMenu->x()/BLOCK_SIZE), (int)floor( (ginny->GetScene()->height()-(rightClickMenu->y()))/BLOCK_SIZE) );
    rightClickMenu->hide();
}

GraphicsViewEditor::GraphicsViewEditor(engine *gin){
    ginny = gin;
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
            item->setText(QString("sprites/"+spritesList.at(k)));
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
        rightClickMenu->show();
    }
}
void GraphicsViewEditor::mouseReleaseEvent(QMouseEvent * event){
    if(event->button() == Qt::LeftButton ){
        this->setCursor(QCursor(Qt::ArrowCursor));
    }
    if(event->button() == Qt::MiddleButton ){
        //QGraphicsItem *item;
        QList<QGraphicsItem*> list = this->items();
        foreach( QGraphicsItem *item, list ){
            if(item != NULL ){
                while( ((int)item->x() % BLOCK_SIZE) != 0){
                    if( ((int)item->x() % BLOCK_SIZE) <= BLOCK_SIZE/2 )
                        item->moveBy(-1,0);
                    else
                        item->moveBy(1,0);
                }
                while( ((int)item->y() % BLOCK_SIZE) != 0){
                    if( ((int)item->y() % BLOCK_SIZE) <= BLOCK_SIZE/2 )
                        item->moveBy(0,-1);
                    else
                        item->moveBy(0,1);
                }
            }
        }
    }
}