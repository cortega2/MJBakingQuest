#include "start.h"
//test
#include <iostream>



start::start(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::start)
{
    ui->setupUi(this);
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

        hide();
    }

}

void start::on_pushButton_3_clicked(){
    editWindow *mainWindow = new editWindow;

    mainWindow->setWindowIcon(QIcon("sprites/mexican_man.png"));
    mainWindow->setWindowTitle(QString("Mexican Editor v1.0"));

    mainWindow->setCentralWidget( mainWindow->GetGraphicsView() );
    //mainWindow->centralWidget()->setAttribute(Qt::WA_TransparentForMouseEvents);
    mainWindow->resize(mainWindow->centralWidget()->width(), mainWindow->centralWidget()->height()+10);
    mainWindow->show();

    hide();

}
