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
    engine *gameEngine = new engine();
    editWindow *mainWindow = new editWindow(0 , gameEngine, gameEngine->GetScene(), BLOCK_SIZE);

    gameEngine->SetParentWindow(mainWindow);

    mainWindow->setWindowIcon(QIcon("sprites/MJ_left.png"));
    mainWindow->setWindowTitle(QString("Mary Jane's Baking Quest"));
    mainWindow->showMaximized();

    hide();

}
