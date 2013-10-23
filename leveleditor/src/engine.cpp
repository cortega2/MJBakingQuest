#include <QtCore>
#include <QtWidgets>

#include "mainwindow.h"
#include "objects.h"

#include "engine.h"

#define BLOCK_SIZE (50)
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
    QFile file(QFileDialog::getOpenFileName(parentWindow, "Open Level", "", "Files (*.*)"));
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "Error!",file.fileName()+" : "+ file.errorString()+"\nLoading Default");
        file.setFileName(":levels/defaultlevel");
        file.open(QIODevice::ReadOnly);
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
            QGraphicsRectWidget *block = new QGraphicsRectWidget(QPixmap(spriteName));
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
 * Useful for autoloading the next level upon winning */
int engine::LoadMap(QGraphicsScene *scene, QString fileName){

    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "Error!",file.fileName()+" : "+ file.errorString()+"\nLoading Default");
        //return 0;
        file.setFileName(":levels/defaultlevel");
        file.open(QIODevice::ReadOnly);
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
            QGraphicsRectWidget *block = new QGraphicsRectWidget(QPixmap(spriteName));
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
