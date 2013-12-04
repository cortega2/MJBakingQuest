/*! \abstract editwindow::editWindow
 *         This class sets up the window of the level editor.
 *         This window includes menus for help, tools to build a level and a file menu.
 */

#include "editormainwindow.h"
#include <iostream>

/*! \brief editwindow::editWindow
 *         Uses GraphicsView to display level editor window. Calls engine to generate items for window.
 */
editWindow::editWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    ginny = new engine();

    ui->setupUi(this);

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

/*! \brief editWindow::~editWindow
 *         To clean up stuff when your done!
 */
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

void editWindow::mouseReleaseEvent(QMouseEvent *event){

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
}
