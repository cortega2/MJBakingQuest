#include <QtCore>
#include <QtGui>
#if QT_VERSION >= 0x050000
    #include <QtWidgets>
#endif

#include "editormainwindow.h"
#include "engine.h"

MainWindow::MainWindow(QWidget *parent, engine *gin) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    ginny = gin;
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
    ginny->ClickedOpenMap();
}

void MainWindow::on_actionExit_triggered()
{
    qApp->exit();
}

void MainWindow::on_actionClose_triggered()
{
    ginny->CloseMap();
}

void MainWindow::on_actionDraw_Grid_Lines_triggered()
{
    ginny->ClickedDrawGridLines();
}
