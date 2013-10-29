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

    ui->tabWidget->setGeometry(ui->graphicsView->width()+5,5,350,300);
    /*mexican_man = new QPushButton(QIcon(QString("sprites/mexican_man.png")),QString(""),ui->characters);
    mexican_man->setCursor(QCursor(Qt::OpenHandCursor));
    mexican_man->setFixedSize(30,30);*/

    charscene = new QGraphicsScene();
    charview = new QGraphicsView(charscene, ui->characters);
    charscene->setParent(charview);

    charview->setGeometry(4,4,ui->tabWidget->width()-12, ui->tabWidget->height()-12);
    charscene->setSceneRect(0,0,ui->tabWidget->width()-16, ui->tabWidget->height()-16);

    charview->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    charscene->addItem(new QGraphicsRectWidget("sprites/MJ_right.png", 30, 30));
    charscene->addItem(new QGraphicsRectWidget(Qt::red, 30,30));
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

void MainWindow::on_mexican_man_pressed()
{

}
