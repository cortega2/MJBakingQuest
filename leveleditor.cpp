#include <QtCore>
#include <QObject>

#include "engine.h"
#include "editormainwindow.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    engine *gameEngine = new engine();
    MainWindow *mainWindow = new MainWindow(0 , gameEngine);

    gameEngine->Setup(mainWindow);

    mainWindow->setWindowIcon(QIcon("sprites/MJ_left.png"));
    mainWindow->setWindowTitle(QString("Mary Jane's Baking Quest"));
    mainWindow->showMaximized();

    return app.exec();
}
