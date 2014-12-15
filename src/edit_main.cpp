int main(int argc, char *argv[]){
    QApplication app(argc, argv);

    editWindow *mainWindow = new editWindow;

    mainWindow->setWindowIcon(QIcon("sprites/mexican_man.png"));
    mainWindow->setWindowTitle(QString("MJBQ Editor"));

    mainWindow->setCentralWidget( mainWindow->GetGraphicsView() );
    mainWindow->resize(mainWindow->centralWidget()->width(), mainWindow->centralWidget()->height()+10);
    mainWindow->show();

    return app.exec();
}
