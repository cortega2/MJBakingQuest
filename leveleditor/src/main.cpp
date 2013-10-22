/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtCore module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtCore>
#include <QtWidgets>
#include "mainwindow.h"
#include "objects.h"

#define BLOCK_SIZE (50)

//int offset = 50;
const QRect *sSize = new QRect(0,0,1000,600);
const QRect *wSize = new QRect(0,0,1010,700);

void moveBlock(QGraphicsWidget *box, int x, int y){
    box->moveBy(BLOCK_SIZE*x,wSize->height()-BLOCK_SIZE*y);
}

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    MainWindow mainWindow;

    mainWindow.ui->graphicsView->setGeometry(*wSize);

    QGraphicsScene uiScene(*sSize);

    QGraphicsRectWidget *redBox = new QGraphicsRectWidget(Qt::red);
    QGraphicsRectWidget *yellowBox = new QGraphicsRectWidget(Qt::yellow);

    moveBlock(redBox,1,2);
    moveBlock(yellowBox,0,2);

    uiScene.addItem(redBox);
    uiScene.addItem(yellowBox);

    int gridWidth = floor(wSize->width()/BLOCK_SIZE);
    int gridHeight = floor(wSize->height()/BLOCK_SIZE);

    for(int x=1; x<gridWidth; x++){
        uiScene.addLine(BLOCK_SIZE*x, 0, BLOCK_SIZE*x, BLOCK_SIZE*gridHeight,QPen());
    }
    for(int y=1; y<gridHeight; y++){
        uiScene.addLine(0, BLOCK_SIZE*y, BLOCK_SIZE*gridWidth, BLOCK_SIZE*y,QPen());
    }


    uiScene.setBackgroundBrush(Qt::black);
    uiScene.setBackgroundBrush(QBrush(Qt::black,QPixmap("sprites/starrynight.png")));

    QGraphicsRectWidget *cBlock = new QGraphicsRectWidget(QPixmap("sprites/concrete.png"));

    moveBlock(cBlock,10,10);
    uiScene.addItem(cBlock);



    //QFile file("C:/Users/jburni2.AD/Documents/program/moveblocks/level1");
    QFile file("level1");
    //QString fileName = QFileDialog::getOpenFileName(0,"Open File","","Files (*.*)");

    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", file.errorString());
    }

    QTextStream in(&file);

    while(!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(",");

        if(fields.at(0).compare( QString("BLOCK") ) ==0 )
        {
            QGraphicsRectWidget *block = new QGraphicsRectWidget(Qt::blue);
            moveBlock(block,fields.at(1).toInt(), fields.at(2).toInt() );
            uiScene.addItem(block);
        }
    }

    file.close();


    mainWindow.ui->graphicsView->setScene(&uiScene);
    mainWindow.showMaximized();
    mainWindow.setWindowIcon(QIcon("sprites/MJ_left.png"));

    return app.exec();
}

//#include "main.moc"
