#include <QtCore>
#include <QtWidgets>

#include "mainwindow.h"
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
