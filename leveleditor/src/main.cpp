#include <QtCore>
//#include <QtWidgets>

#include "engine.h"

#include "mainwindow.h"

#ifdef Q_OS_WIN
#include <windows.h> // for Sleep
#endif
void qSleep(int ms)
{
#ifdef Q_OS_WIN
    Sleep(uint(ms));
#else
    struct timespec ts = { ms / 1000, (ms % 1000) * 1000 * 1000 };
    nanosleep(&ts, NULL);
#endif
}

/*
void moveBlock(QGraphicsWidget *box, int x, int y){
    box->moveBy(BLOCK_SIZE*x,wSize->height()-BLOCK_SIZE*y);
}
void DrawGrid(QGraphicsScene *scene){
    int gridWidth = floor(wSize->width()/BLOCK_SIZE);
    int gridHeight = floor(wSize->height()/BLOCK_SIZE);

    for(int x=1; x<gridWidth; x++){
        scene->addLine(BLOCK_SIZE*x, 0, BLOCK_SIZE*x, BLOCK_SIZE*gridHeight,QPen(Qt::red));
    }
    for(int y=1; y<gridHeight; y++){
        scene->addLine(0, BLOCK_SIZE*y, BLOCK_SIZE*gridWidth, BLOCK_SIZE*y,QPen(Qt::red));
    }
}

int LoadMap(QGraphicsScene *scene){
    QFile file(QFileDialog::getOpenFileName(0,"Open Level","","Files (*.*)"));
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
            moveBlock(block,fields.at(2).toInt(), fields.at(3).toInt() );
            scene->addItem(block);
        }else if(fields.at(0).compare( QString("BACKGROUND") ) == 0){

            scene->setBackgroundBrush(QBrush(Qt::black,QPixmap(spriteName)));
        }
    }
    file.close();
    return 1;
}
*/

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    MainWindow *mainWindow = new MainWindow();

    engine *gameEngine = new engine();

    gameEngine->begin(mainWindow);

    mainWindow->setWindowIcon(QIcon("sprites/MJ_left.png"));
    mainWindow->setWindowTitle(QString("Mary Jane's Baking Quest"));
    mainWindow->showMaximized();

    return app.exec();
}
//#include "main.moc"
