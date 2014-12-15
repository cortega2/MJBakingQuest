#include "start.h"

int main(int argc, char *argv[]){
    QApplication app(argc, argv);
    start*  window = new start();
    window->show();
    return app.exec();
}
