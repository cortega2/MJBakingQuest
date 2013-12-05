#include "editormainwindow.h"

//test code
#include <iostream>


editWindow::editWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    ginny = new engine();

    ui->setupUi(this);

    ui->radioButtonMBLOCK->setParent(ui->menubar);
    ui->radioButtonNonMovableBlock->setParent(ui->menubar);

    ui->radioButtonMBLOCK->setChecked(true);

    ui->radioButtonMBLOCK->move(500,1);
    ui->radioButtonNonMovableBlock->move(ui->radioButtonMBLOCK->x()+ui->radioButtonMBLOCK->width(),1);

    graphicsView = new GraphicsViewEditor( ginny );
    graphicsView->setGeometry( QRect(0,ui->menubar->height(),BLOCK_SIZE*30,BLOCK_SIZE*20 + ui->menubar->height()) );

    graphicsScene = new QGraphicsScene( QRect(0,0,BLOCK_SIZE*30,BLOCK_SIZE*20) );
    graphicsView->setScene( graphicsScene );

    ginny->SetScene( graphicsScene );
    ginny->SetParentWindow( this );

    graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //borderless doesn't look good
    //this->setWindowFlags(Qt::FramelessWindowHint);

    //this extra computation doesn't really aid anything
    //graphicsView->setMouseTracking(true);
    //setMouseTracking(true);
}
/* need to clean up stuff when your done! */
editWindow::~editWindow(){
    delete ui;
    delete ginny;
    delete graphicsView;
    delete graphicsScene;
}

QGraphicsView* editWindow::GetGraphicsView(){
    return graphicsView;
}

QGraphicsScene* editWindow::GetGraphicsScene(){
    return graphicsScene;
}

void editWindow::on_actionOpen_triggered(){
    ginny->ClickedOpenMap();
}

void editWindow::on_actionExit_triggered(){
    qApp->exit();
}

void editWindow::on_actionClose_triggered(){
    ginny->CloseMap();
}

void editWindow::on_actionDraw_Grid_Lines_triggered(){
    ginny->ClickedDrawGridLines();
}

void editWindow::on_actionUsage_triggered()
{
    QMessageBox box;
    box.setText(QString("Right click to open menu\nDouble Click on sprite to add\nDouble Click and drag to move sprite around\nMiddle click to snap to grid."));
    box.exec();
}

void editWindow::on_actionSnap_Now_triggered()
{
    graphicsView->SnapToGrid();
}

void editWindow::on_actionCredits_triggered()
{
    QMessageBox box;
    box.setText(QString("Editor by Joseph Burnitz\n"));
    box.exec();
}

void editWindow::on_actionAutomatic_Snapping_changed()
{
    graphicsView->AutoSnap = this->ui->actionAutomatic_Snapping->isChecked();
}

void editWindow::on_actionSave_triggered()
{
    ginny->ClickedSaveMap();
    //ginny->saveGame( QString("poop") );
}

void editWindow::on_radioButtonMBLOCK_clicked()
{
    graphicsView->mBlockChecked = this->ui->radioButtonMBLOCK->isChecked();
}

void editWindow::on_radioButtonNonMovableBlock_clicked()
{
    graphicsView->mBlockChecked = this->ui->radioButtonMBLOCK->isChecked();
}
