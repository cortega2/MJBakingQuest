#include "start.h"

start::start(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::start)
{
    ui->setupUi(this);
}

start::~start()
{
    delete ui;
}

void start::on_pushButton_clicked()
{
     gamewindow *mainWindow = new gamewindow( 0, BLOCK_SIZE);

     mainWindow->setWindowIcon(QIcon("sprites/MJ_left.png"));
     mainWindow->setWindowTitle(QString("Mary Jane's Baking Quest"));

     mainWindow->setCentralWidget( mainWindow->GetGraphicsView() );
     mainWindow->resize( mainWindow->centralWidget()->width(), mainWindow->centralWidget()->height() );
     mainWindow->show();

     hide();
}

void start::on_pushButton_2_clicked()
{

}

void start::on_pushButton_3_clicked()
{
    editWindow *mainWindow = new editWindow(0 , BLOCK_SIZE);

    mainWindow->setWindowIcon(QIcon("sprites/mexican_man.png"));
    mainWindow->setWindowTitle(QString("Mexican Editor v1.0"));

    mainWindow->setCentralWidget( mainWindow->GetGraphicsView() );
    //mainWindow->centralWidget()->setAttribute(Qt::WA_TransparentForMouseEvents);
    mainWindow->resize(mainWindow->centralWidget()->width(), mainWindow->centralWidget()->height()+10);
    mainWindow->show();

    hide();

}
