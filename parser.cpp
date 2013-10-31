#include "parser.h"

//test code
#include <iostream>

parser::parser(){
}

//might not need to pass scene to readFile
void parser::readFile(QGraphicsScene *scene){
    //Opens a file chooser Dialog box
    QFile file(QFileDialog::getOpenFileName(0, "Open Level", "", "Files (*.*)"));

    //if the file can't be opened, then load the default map
    //which is compiled in as a resource
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "Error!",file.fileName()+" : "+ file.errorString()+"\nLoading Default");
        file.setFileName("levels/defaultlevel");
        file.open(QIODevice::ReadOnly);
    }
    QTextStream in(&file);

    //process each line of the file and take appropiate actions
    while(!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(",");

        QString spriteName("sprites/");
        spriteName.append(fields.at(1).trimmed());
        spriteName.append(".png");
        std::cout<<spriteName.toStdString()<<std::endl;
        /*
        if(fields.at(0).compare( QString("BLOCK") ) == 0 )
        {
            QGraphicsRectWidget *block = new QGraphicsRectWidget(QPixmap(spriteName), BLOCK_SIZE, BLOCK_SIZE);
            MoveBlock(block, scene, fields.at(2).toInt(), fields.at(3).toInt() );
            scene->addItem(block);

        }else if(fields.at(0).compare( QString("BACKGROUND") ) == 0){

            scene->setBackgroundBrush(QBrush(Qt::black,QPixmap(spriteName)));
        }*/
    }
    file.close();
}
