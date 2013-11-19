#include "parser.h"

//test code
#include <iostream>

parser::parser(){
}
parser::~parser(){
    delete sprites;
}

//reads a file, either one specified by user though the file diolog or
//opens the name specified
//add sprites to the objStructure
int parser::readFile( QWidget *parent, objStructure *good, objStructure *enemies,
                      objStructure *blocks, objStructure *other, QString fileName){

    //Opens a file chooser Dialog box
    if( fileName.isNull() ){
        /* Without putting a parentwindow reference, the dialogBox will background everything */
        QFile file(QFileDialog::getOpenFileName( parent , "Open Level", "", "Files (*.*)"));

        //if the file can't be opened, then load the default map
        if(!file.open(QIODevice::ReadOnly)){
            QMessageBox::information( parent, "Error!",file.fileName()+" : "+ file.errorString()+"\nLoading Default");
            file.setFileName("levels/defaultlevel");
            file.open(QIODevice::ReadOnly);
        }

        QTextStream in(&file);
        //process each line of the file and take appropiate actions

        while(!in.atEnd()) {
            QString line = in.readLine();
            //a comment is encountered
            if(line.contains('#'))
                continue;

            QStringList fields = line.split(",");

            QString spriteName("sprites/");
            spriteName.append(fields.at(1).trimmed());
            spriteName.append(".png");

            /*
            if(fields.at(0).compare( QString("BLOCK") ) == 0 )
                sprites->add(fields.at(0), spriteName, fields.at(2).toInt(), fields.at(3).toInt());
            else if(fields.at(0).compare( QString("BACKGROUND") ) == 0)
                sprites->add(fields.at(0), spriteName, -1, -1);
            */


            if(fields.at(0).compare( QString("MJ")) == 0 || fields.at(0).compare( QString("MX")) == 0)
                good->add(fields.at(0), spriteName, fields.at(2).toInt(), fields.at(3).toInt());
            else if(fields.at(0).compare( QString("ENEMY")) == 0 ){
                enemies->add(fields.at(0), spriteName, fields.at(2).toInt(), fields.at(3).toInt());
            }
            else if(fields.at(0).compare( QString("BLOCK")) == 0 || fields.at(0).compare( QString("MBLOCK")) == 0 ){
                 blocks->add(fields.at(0), spriteName, fields.at(2).toInt(), fields.at(3).toInt());
            }
            else{

                if(fields.at(0).compare( QString("BACKGROUND")) == 0 )
                    other->add(fields.at(0), spriteName, -1, -1);
                else{
                    std::cout << fields.at(2).toInt() << std::endl;
                    other->add(fields.at(0), spriteName, fields.at(2).toInt(), fields.at(3).toInt());
                }
            }

        }
        file.close();
        return 1;
    }

    //loads level specified in filename
    else{
        QFile file( fileName );
        if(!file.open(QIODevice::ReadOnly))
            return -1;

        QTextStream in(&file);
        //process each line of the file and take appropiate actions
        while(!in.atEnd()) {
            QString line = in.readLine();
            //a comment is encountered
            if(line.contains('#'))
                continue;

            QStringList fields = line.split(",");

            QString spriteName("sprites/");
            spriteName.append(fields.at(1).trimmed());
            spriteName.append(".png");

            /*
            if(fields.at(0).compare( QString("BACKGROUND") ) == 0)
                objs->add(fields.at(0), spriteName, -1, -1);
            else
                objs->add(fields.at(0), spriteName, fields.at(2).toInt(), fields.at(3).toInt());
            */

            if(fields.at(0).compare( QString("MJ")) == 0 || fields.at(0).compare( QString("MX")) == 0)
                good->add(fields.at(0), spriteName, fields.at(2).toInt(), fields.at(3).toInt());
            else if(fields.at(0).compare( QString("ENEMY")) == 0 ){
                enemies->add(fields.at(0), spriteName, fields.at(2).toInt(), fields.at(3).toInt());
            }
            else if(fields.at(0).compare( QString("BLOCK")) == 0 || fields.at(0).compare( QString("MBLOCK")) == 0 ){
                 blocks->add(fields.at(0), spriteName, fields.at(2).toInt(), fields.at(3).toInt());
            }
            else{
                if(fields.at(0).compare( QString("BACKGROUND")) == 0 )
                    other->add(fields.at(0), spriteName, -1, -1);
                else{
                    other->add(fields.at(0), spriteName, fields.at(2).toInt(), fields.at(3).toInt());
                }
           }
        }
        file.close();
        return 1;
    }

    //something broke if it gets down here
    return 0;
}

void parser::createFile(QString name,  objStructure *goodGuys, objStructure *enemies,
                        objStructure *blocks, objStructure *other){
    QFile file("out.txt");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    out << "#This file is generated by Qt\n";

    Node *tmp = goodGuys->head;
    while(tmp != 0){
        out << tmp->blockType << ", " << tmp->location << ", " << tmp->x << ", " << tmp->y <<"\n";
        tmp = tmp->next;
    }

    tmp = enemies->head;
    while(tmp != 0){
        out << tmp->blockType << ", " << tmp->location << ", " << tmp->x << ", " << tmp->y <<"\n";
        tmp = tmp->next;
    }

    tmp = blocks->head;
    while(tmp != 0){
        out << tmp->blockType << ", " << tmp->location << ", " << tmp->x << ", " << tmp->y <<"\n";
        tmp = tmp->next;
    }

    tmp = other->head;
    while(tmp != 0){
        if(tmp->blockType.compare( QString("BACKGROUND")) == 0)
            std::cout << "booo background here\n";
        else{
            out << tmp->blockType << ", " << tmp->location << ", " << tmp->x << ", " << tmp->y <<"\n";
        }
        tmp = tmp->next;
    }

    file.close();
}
