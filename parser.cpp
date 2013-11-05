#include "parser.h"

//test code
#include <iostream>

parser::parser(){
}

//reads a file, either one specified by user though the file diolog or
//opens the name specified
//add sprites to the objStructure
int parser::readFile(objStructure *objs, QString fileName, bool readSpecific){
    sprites = objs;

    //Opens a file chooser Dialog box
    if(!readSpecific){
        QFile file(QFileDialog::getOpenFileName(0, "Open Level", "", "Files (*.*)"));

        //if the file can't be opened, then load the default map
        if(!file.open(QIODevice::ReadOnly)){
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

            if(fields.at(0).compare( QString("BLOCK") ) == 0 )
                sprites->add(fields.at(0), spriteName, fields.at(2).toInt(), fields.at(3).toInt());
            else if(fields.at(0).compare( QString("BACKGROUND") ) == 0)
                sprites->add(fields.at(0), spriteName, -1, -1);
        }
        file.close();
    }

    //loads level specified in filename
    else{

        //test code
        /*
        std::cout << (QDir::absolutePath()).toStdString() << std::endl;

        if(!QDir::setCurrent("/levels"))
            std::cout<<"couldnt changed dir"<<std::endl;

        std::cout<< fileName.toStdString() << std::endl;
        */

        QFile file(fileName);
        if(!file.open(QIODevice::ReadOnly))
            return -1;

        QTextStream in(&file);
        //process each line of the file and take appropiate actions
        while(!in.atEnd()) {
            QString line = in.readLine();
            QStringList fields = line.split(",");

            QString spriteName("sprites/");
            spriteName.append(fields.at(1).trimmed());
            spriteName.append(".png");

            if(fields.at(0).compare( QString("BLOCK") ) == 0 )
                sprites->add(fields.at(0), spriteName, fields.at(2).toInt(), fields.at(3).toInt());
            else if(fields.at(0).compare( QString("BACKGROUND") ) == 0)
                sprites->add(fields.at(0), spriteName, -1, -1);
        }
        file.close();
    }


    return 0;
}
