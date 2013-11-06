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
     engine *gameEngine = new engine();
     gamewindow *mainWindow = new gamewindow(0 , gameEngine, gameEngine->GetScene(), BLOCK_SIZE);
     gameEngine->SetParentWindow(mainWindow);

     mainWindow->setWindowIcon(QIcon("sprites/MJ_left.png"));
     mainWindow->setWindowTitle(QString("Mary Jane's Baking Quest"));
     mainWindow->showMaximized();

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
    mainWindow->setCentralWidget( mainWindow->graphicsView );
    mainWindow->resize(mainWindow->centralWidget()->width(), mainWindow->centralWidget()->height()+10);
    mainWindow->show();

    hide();

}
