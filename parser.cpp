#include "parser.h"

//test code
#include <iostream>

parser::parser(){
    //default case
    lives = 3;
    curLevel = "levels/defaultlevel";
    nextLevel = "levels/defaultlevel";
}
parser::~parser(){
    delete sprites;
}

//reads a file, either one specified by user though the file diolog or
//opens the name specified
//add sprites to the objStructure
int parser::readFile( QWidget *parent, objStructure *good, objStructure *enemies,
                      objStructure *blocks, objStructure *doors, objStructure *other, QString fileName){
    //the default value
    lives = 3;
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

            QString spriteName("");
            spriteName.append(fields.at(1).trimmed());

            if(fields.at(0).compare( QString("MJ")) == 0){
                good->add(fields.at(0), spriteName, fields.at(2).toInt(), fields.at(3).toInt());
            }
            else if(fields.at(0).compare( QString("GOOD")) == 0){
                good->add(fields.at(0), spriteName, fields.at(2).toInt(), fields.at(3).toInt(), fields.at(4).trimmed());
            }
            else if(fields.at(0).compare( QString("ENEMY")) == 0 ){
                enemies->add(fields.at(0), spriteName, fields.at(2).toInt(), fields.at(3).toInt());
            }
            else if(fields.at(0).compare( QString("BLOCK")) == 0 || fields.at(0).compare( QString("MBLOCK")) == 0 ){
                 blocks->add(fields.at(0), spriteName, fields.at(2).toInt(), fields.at(3).toInt());
            }
            else if(fields.at(0).compare( QString("DOOR")) == 0){
                 doors->add(fields.at(0), spriteName, fields.at(2).toInt(), fields.at(3).toInt());
            }
            else if(fields.at(0).compare( QString("NEXT")) == 0){
                nextLevel = fields.at(1).trimmed();
            }
            else if(fields.at(0).compare( QString("LIVES")) == 0){
                lives = fields.at(1).trimmed().toInt();
            }
            else if(fields.at(0).compare( QString("CURRENT")) == 0){
                curLevel = fields.at(1).trimmed();
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
        return 0;
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

            QString spriteName("");
            spriteName.append(fields.at(1).trimmed());

            if(fields.at(0).compare( QString("MJ")) == 0){
                good->add(fields.at(0), spriteName, fields.at(2).toInt(), fields.at(3).toInt());
            }
            else if(fields.at(0).compare( QString("GOOD")) == 0){
                good->add(fields.at(0), spriteName, fields.at(2).toInt(), fields.at(3).toInt(), fields.at(4).trimmed());

                if(fields.at(5).trimmed().toInt() == 0)
                    good->tail->hasObj = false;
                else if(fields.at(5).trimmed().toInt() == 1)
                    good->tail->hasObj = true;
            }
            else if(fields.at(0).compare( QString("ENEMY")) == 0 ){
                enemies->add(fields.at(0), spriteName, fields.at(2).toInt(), fields.at(3).toInt());
            }
            else if(fields.at(0).compare( QString("BLOCK")) == 0 || fields.at(0).compare( QString("MBLOCK")) == 0 ){
                 blocks->add(fields.at(0), spriteName, fields.at(2).toInt(), fields.at(3).toInt());
            }
            else if(fields.at(0).compare( QString("DOOR")) == 0){
                 doors->add(fields.at(0), spriteName, fields.at(2).toInt(), fields.at(3).toInt());
            }
            else if(fields.at(0).compare( QString("NEXT")) == 0){
                nextLevel = fields.at(1).trimmed();
            }
            else if(fields.at(0).compare( QString("LIVES")) == 0){
                lives = fields.at(1).trimmed().toInt();
            }
            else if(fields.at(0).compare( QString("CURRENT")) == 0){
                curLevel = fields.at(1).trimmed();
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
        return 0;
    }

    //something broke if it gets down here
    return 1;
}

void parser::createFile(const QString name,  objStructure *goodGuys, objStructure *enemies,
                        objStructure *blocks, objStructure *doors, objStructure *other){

    if(!QDir().exists("saved"))
        QDir().mkdir("saved");

    QFile file("saved/" + name);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);

    out << "#This file is generated by Qt\n";
    out << "#Player Stats\n";
    out << "LIVES, " << lives << "\n";
    out << "NEXT, " << nextLevel << "\n";
    out << "CURRENT, " << curLevel << "\n";
    out <<"#Level atributes\n";

    Node *tmp = goodGuys->head;
    while(tmp != 0){
        out << tmp->blockType << ", " << tmp->location << ", " << tmp->x << ", " << tmp->y;
        if(tmp->blockType.compare(QString("MJ")) != 0)
            out << ", " << tmp->goodObj << ", " << tmp->hasObj;
        out << "\n";
        tmp = tmp->next;
    }

    tmp = enemies->head;
    while(tmp != 0){
        out << tmp->blockType << ", " << tmp->location << ", " << tmp->x << ", " << tmp->y <<"\n";
        tmp = tmp->next;
    }

    tmp = doors->head;
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
            out << tmp->blockType << ", " << tmp->location <<"\n";
        else{
            out << tmp->blockType << ", " << tmp->location << ", " << tmp->x << ", " << tmp->y <<"\n";
        }
        tmp = tmp->next;
    }

    file.close();
}
