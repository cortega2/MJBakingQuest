/*! \abstract start
 *         This is the start up screen. This class creates a start up window, that links to the game window or the level editor window. The window also
 *         includes a help button with instructions for playing the game.
 */

#include "start.h"
#include <iostream>

/*! \abstract start::start
 *   Opens start window and plays start up music
 */
start::start(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::start)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    player = new QMediaPlayer;

    player->setMedia(QUrl::fromLocalFile(QFileInfo("sounds/afroman_because_i_got_high_instrumental.mp3").absoluteFilePath() ));
    player->setVolume(50);
    player->play();
}

start::~start(){
    delete ui;
    delete player;
}

/*! \abstract start::on_pushButton_clicked
 *   Opens a new game
 */
void start::on_pushButton_clicked(){
    bool ok;
    QString session;

    while(true){
        session = QInputDialog::getText(this, tr("New session"),tr("Session Name:"), QLineEdit::Normal,"", &ok);
        if(ok){
            if(QFile().exists("saved/" + session)){
                MyMessageBox::StandardButton overwrite;
                overwrite = MyMessageBox::question(this, "Warning", "This file exist already.\n Do you want to overwrite it?",
                                                   MyMessageBox::Yes|MyMessageBox::No);
                if(overwrite == MyMessageBox::Yes)
                    break;
            }
            else
                break;
        }
        else
            return;
    }

    gamewindow *mainWindow = new gamewindow(0, true, session);
    mainWindow->setWindowIcon(QIcon("sprites/MJ_left.png"));
    mainWindow->setWindowTitle(QString("Mary Jane's Baking Quest"));

    mainWindow->setCentralWidget( mainWindow->GetGraphicsView() );
    mainWindow->resize( mainWindow->centralWidget()->width(), mainWindow->centralWidget()->height() );
    mainWindow->show();
    player->stop();
    hide();
}

/*! \abstract start::on_pushButton_2_clicked
 *   Opens a saved game
 */
void start::on_pushButton_2_clicked(){
    QString session;
    while(true){
        bool ok;
        session = QInputDialog::getText(this, tr("Continue Session"),tr("Enter Session:"), QLineEdit::Normal,"", &ok);

        if(ok){
            if(QFile().exists("saved/" + session) && session.length() != 0)
                break;
            else{
                MyMessageBox msgBox;
                msgBox.setBaseSize(0,0);
                msgBox.setText("That file does not exist");
                msgBox.exec();
            }
        }
        else
            return;
    }

    gamewindow *mainWindow = new gamewindow(0, false, session);

    mainWindow->setWindowIcon(QIcon("sprites/MJ_left.png"));
    mainWindow->setWindowTitle(QString("Mary Jane's Baking Quest"));

    mainWindow->setCentralWidget( mainWindow->GetGraphicsView() );
    mainWindow->resize( mainWindow->centralWidget()->width(), mainWindow->centralWidget()->height() );
    mainWindow->show();

    player->stop();
    hide();

}

/*! \abstract start::on_pushButton_3_clicked
 *   Opens the level editor
 */
void start::on_pushButton_3_clicked(){
    editWindow *mainWindow = new editWindow;

    mainWindow->setWindowIcon(QIcon("sprites/mexican_man.png"));
    mainWindow->setWindowTitle(QString("MJBQ Editor"));

    mainWindow->setCentralWidget( mainWindow->GetGraphicsView() );
    //mainWindow->centralWidget()->setAttribute(Qt::WA_TransparentForMouseEvents);
    mainWindow->resize(mainWindow->centralWidget()->width(), mainWindow->centralWidget()->height()+10);
    mainWindow->show();
    player->stop();
    hide();

}

/*! \abstract start::on_pushButton_4_clicked
 *   Opens help window
 */
void start::on_pushButton_4_clicked(){

    MyMessageBox msgBox;
    msgBox.setBaseSize(500,500);
    msgBox.setText("Press the 'D' key to move Mary Jane Forward.\n"
                   "Press the 'A' key to move Mary Jane Backward.\n"
                   "Press the space bar to pick up or drop blocks.\n"
                   "Also press space bar when in front of a door to go through it.\n\n"
                   "P.S If you get stuck, the 'R' key will reset the level");
    msgBox.exec();

}

/*! \abstract start::on_pushButton_6_clicked
 *   Exits game
 */
void start::on_pushButton_6_clicked(){
    qApp->exit();
}
