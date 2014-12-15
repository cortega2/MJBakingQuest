#include "editorwindow.h"

editorWindow::editorWindow(QWidget *parent, engine *gin, QGraphicsScene *uiScene, int BLOCK_SIZE) :
    QMainWindow(parent), ui(new Ui::editorWindow)
{
    ui->setupUi(this);
}

editorWindow::~editorWindow()
{
    delete ui;
}
