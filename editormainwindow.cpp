#include "editormainwindow.h"

MainWindow::MainWindow(QWidget *parent, engine *gin, QGraphicsScene *uiScene, int BLOCK_SIZE) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    ginny = gin;
    ui->setupUi(this);

    ui->graphicsView->setGeometry( QRect(4,4,BLOCK_SIZE*30,BLOCK_SIZE*20) );
    ui->graphicsView->setScene( uiScene );
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui->tabWidget->setGeometry(ui->graphicsView->width()+5,5,150,300);
    mexican = new QPushButton(QIcon(QString("sprites/mexican_man.png")),QString(""),ui->characters);
    mexican->setFixedSize(30,30);
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
