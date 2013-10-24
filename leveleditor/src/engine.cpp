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

#include <QtCore>
#include <QtWidgets>

#include "mainwindow.h"
#include "objects.h"

#include "engine.h"

#define BLOCK_SIZE ( 30 )

engine::engine(){
    sSize = new QRect(0,0,1000,600);
    wSize = new QRect(0,0,1010,700);

    uiScene = new QGraphicsScene( *sSize );
}

engine::~engine(){
    delete sSize;
    delete wSize;
    delete uiScene;
}

void engine::Setup( MainWindow *mainWindow )
{
    mainWindow->ui->graphicsView->setGeometry( *wSize );
    mainWindow->ui->graphicsView->setScene( uiScene );
    parentWindow = mainWindow;
}

/* Moves a block by offset of their size
 * 0,0 is in the lower left, e.g. Quadrant 1 */
void engine::MoveBlock(QGraphicsWidget *box, int x, int y){
    box->moveBy(BLOCK_SIZE*x,wSize->height()-BLOCK_SIZE*y);
}

/* Draws a grid lines through the
 * scene for line up/snap to purposes */
void engine::DrawGrid(QGraphicsScene *scene){
    int gridWidth = floor(wSize->width()/BLOCK_SIZE);
    int gridHeight = floor(wSize->height()/BLOCK_SIZE);

    for(int x=1; x<gridWidth; x++){
        scene->addLine(BLOCK_SIZE*x, 0, BLOCK_SIZE*x, BLOCK_SIZE*gridHeight,QPen(Qt::red));
    }
    for(int y=1; y<gridHeight; y++){
        scene->addLine(0, BLOCK_SIZE*y, BLOCK_SIZE*gridWidth, BLOCK_SIZE*y,QPen(Qt::red));
    }
}

/* Loads a map into the Graphics Scene
 * Open a file chooser dialog */
int engine::LoadMap(QGraphicsScene *scene){
    //Opens a file chooser Dialog box
    QFile file(QFileDialog::getOpenFileName(parentWindow, "Open Level", "", "Files (*.*)"));
    //if the file can't be opened, then load the default map
    //which is compiled in as a resource
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "Error!",file.fileName()+" : "+ file.errorString()+"\nLoading Default");
        file.setFileName(":levels/defaultlevel");
        file.open(QIODevice::ReadOnly);
    }
    QTextStream in(&file);

    //process each line of the file and take appropiate actions
    while(!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(",");

        QString spriteName("sprites/");
        spriteName.append(fields.at(1).trimmed());
        spriteName.append(".png");

        if(fields.at(0).compare( QString("BLOCK") ) == 0 )
        {
            QGraphicsRectWidget *block = new QGraphicsRectWidget(QPixmap(spriteName), BLOCK_SIZE, BLOCK_SIZE);
            MoveBlock(block,fields.at(2).toInt(), fields.at(3).toInt() );
            scene->addItem(block);
        }else if(fields.at(0).compare( QString("BACKGROUND") ) == 0){

            scene->setBackgroundBrush(QBrush(Qt::black,QPixmap(spriteName)));
        }
    }
    file.close();
    return 1;
}

/* Loads the level file specified by the fileName
 * Useful for autoloading the next level upon winning
 * it's almost identical to the one above it */
int engine::LoadMap(QGraphicsScene *scene, QString fileName){

    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly)) {
        return -1;
    }

    QTextStream in(&file);

    while(!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(",");

        QString spriteName("sprites/");
        spriteName.append(fields.at(1).trimmed());
        spriteName.append(".png");

        if(fields.at(0).compare( QString("BLOCK") ) == 0 )
        {
            QGraphicsRectWidget *block = new QGraphicsRectWidget(QPixmap(spriteName), BLOCK_SIZE, BLOCK_SIZE);
            MoveBlock(block,fields.at(2).toInt(), fields.at(3).toInt() );
            scene->addItem(block);
        }else if(fields.at(0).compare( QString("BACKGROUND") ) == 0){

            scene->setBackgroundBrush(QBrush(Qt::black,QPixmap(spriteName)));
        }
    }
    file.close();
    return 1;
}

/* Opens the file chooser dialog and loads the map */
void engine::ClickedOpenMap(void){
    LoadMap(uiScene);
}

void engine::CloseMap(void){
    //AskToSave...
    qDeleteAll( uiScene->items());
    uiScene->setBackgroundBrush(QBrush(Qt::white));
}

void engine::ClickedDrawGridLines(void){
    DrawGrid( uiScene );
}
