/*! \abstract gamewindow
 *         This class sets up the window for game play.
 *         This window loads a new game or a saved game.
 *         It also has the keyboard connections set up for the user.
 */

#include "gamewindow.h"
#include <iostream>

/*! \brief gamewindow::gamewindow
 * Loads games depending on if its new or saved. Also sets up timer for music to play
 * in the background. The order of the music is randomly picked.
 */
gamewindow::gamewindow(QWidget *parent, bool newGame, QString sessionName) :
    QMainWindow(parent),
    ui(new Ui::gamewindow)
{
    QString load;
    session = sessionName;
    if(newGame){
        load = "levels/defaultlevel";
    }
    else{
        load = "saved/"+ sessionName;
        //score and other stuff will go here or maybe lets not have a score but life count
    }

    nextLevel = "levels/defaultlevel";

    ui->setupUi(this);
    ginny = new engine();

    //this->setWindowFlags(Qt::FramelessWindowHint);

    graphicsView = new GraphicsView();
    graphicsView->setGeometry( QRect(0, 0, BLOCK_SIZE*30, BLOCK_SIZE*20 ) );

    graphicsScene = new QGraphicsScene( QRect(0,0,BLOCK_SIZE*30,BLOCK_SIZE*20) );
    graphicsView->setScene( graphicsScene );

    ginny->SetScene( graphicsScene );
    ginny->SetParentWindow( this );

    graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ginny->loadGame(load);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(moveEvent()));
    timer->start(500);

    QTimer *mediaTimer = new QTimer(this);
    connect(mediaTimer, SIGNAL(timeout()), this, SLOT(mediaEvent()));
    mediaTimer->start(20);

    //choose random song
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());
    int random = qrand() % (3);
    QString song;
    if(random == 0)
        song = "sounds/aquarium.mp3";
    else if(random == 1)
        song = "sounds/05 - Rafting Starlit Everglades.mp3";
    else
        song = "sounds/Karaoke Bob Marley  Is This Love - Reggae -  www.clubkaraoke.cl.mp3";

    //start playing music from specified file
    player = new QMediaPlayer;
    player->setMedia(QUrl::fromLocalFile(song));
    player->setVolume(50);
    player->play();

    mjHasBlock = false;
}

gamewindow::~gamewindow()
{
    delete ui;
}

QGraphicsView* gamewindow::GetGraphicsView(){
    return graphicsView;
}

/*! \brief gamewindow::keyPressEvent
 * listens to keypresses from the user and does an action
 * based on the key that was pressed
 */
void gamewindow::keyPressEvent(QKeyEvent *event){
    //if it is safe to animate. It is not safe when mj has 0 life and we are reloading the level
    if(ginny->life<=0)
        return;

    //move left
    if (event->key() == Qt::Key_A)
        ginny->moveChar(-1);
    //move right
    else if(event->key() == Qt::Key_D)
        ginny->moveChar(1);
    //reset the current level
    else if(event->key() == Qt::Key_R){
        ginny->startOver();
    }
    //open door or pick up or drop block
    else if(event->key() == Qt::Key_Space){
        if(!(ginny->mjHasBlock))
            ginny->getBlock();
        else
            ginny->dropBlock();

        if(ginny->itemCount <=0){
            //open door and load next leve
            ginny->loadNext();
        }
    }
    //save game
    else if(event->key() == Qt::Key_P){
        if(!ginny->mjHasBlock)
            ginny->saveGame(session);
        else
            std::cout << "Can not save right now, put block down\n";
    }
}

/*! \brief gamewindow::moveEvent
 * sets up timer function for moving enemies
 */
void gamewindow::moveEvent(){
    if(ginny->life<=0)
        return;

    ginny->moveEnemies();
    ginny->moveGood();
}

/*! \brief gamewindow::moveEvent
 * sets up timer function for media player for music played in the background
 */
void gamewindow::mediaEvent(){
    //once song finishes start a new one
    if(player->mediaStatus() == 8 || player->mediaStatus() == 7){
        QTime time = QTime::currentTime();
        qsrand((uint)time.msec());
        int random = qrand() % (3);
        QString song;
        if(random == 0)
            song = "sounds/aquarium.mp3";
        else if(random == 1)
            song = "sounds/05 - Rafting Starlit Everglades.mp3";
        else
            song = "sounds/Karaoke Bob Marley  Is This Love - Reggae -  www.clubkaraoke.cl.mp3";

        player->setMedia(QUrl::fromLocalFile(song));
        player->setVolume(50);
        player->play();
    }

    ginny->checkCollisions();
}
