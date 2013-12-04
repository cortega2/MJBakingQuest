#include "start.h"
//test
#include <iostream>



start::start(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::start)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    player = new QMediaPlayer;
    player->setMedia(QUrl::fromLocalFile("sounds/Instrumentals - Afroman - Because I Got High  (Download).mp3"));
    player->setVolume(50);
    player->play();
}

start::~start(){
    delete ui;
}

void start::on_pushButton_clicked(){

    bool ok;
    QString session = QInputDialog::getText(this, tr("New session"),tr("Session Name:"), QLineEdit::Normal,"", &ok);

    if(ok){
        gamewindow *mainWindow = new gamewindow(0, true, session);

        mainWindow->setWindowIcon(QIcon("sprites/MJ_left.png"));
        mainWindow->setWindowTitle(QString("Mary Jane's Baking Quest"));

        mainWindow->setCentralWidget( mainWindow->GetGraphicsView() );
        mainWindow->resize( mainWindow->centralWidget()->width(), mainWindow->centralWidget()->height() );
        mainWindow->show();
        player->stop();
        hide();
    }
}

void start::on_pushButton_2_clicked(){
    bool ok;
    QString session = QInputDialog::getText(this, tr("Continue Session"),tr("Enter Session:"), QLineEdit::Normal,"", &ok);

    if(ok){
        //should check to see if file exists
        //or better yet use a file chooser dialog
        gamewindow *mainWindow = new gamewindow(0, false, session);

        mainWindow->setWindowIcon(QIcon("sprites/MJ_left.png"));
        mainWindow->setWindowTitle(QString("Mary Jane's Baking Quest"));

        mainWindow->setCentralWidget( mainWindow->GetGraphicsView() );
        mainWindow->resize( mainWindow->centralWidget()->width(), mainWindow->centralWidget()->height() );
        mainWindow->show();

        player->stop();
        hide();
    }
}

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

void start::on_pushButton_4_clicked(){

    MyMessageBox msgBox;
    msgBox.setBaseSize(500,500);
    msgBox.setText("Press the 'D' key to move Mary Jane Forward.\n"
                   "Press the 'A' key to move Mary Jane Backward.\n"
                   "Press the space bar to pick up or drop blocks.\n"
                   "Also press space bar when in front of a door to go through it.");
    msgBox.exec();

}

void start::on_pushButton_6_clicked()
{
    qApp->exit();
}
