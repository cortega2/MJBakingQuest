#ifndef OBJSTRUCTURE_H
#define OBJSTRUCTURE_H
#include <QtCore>
#include "objects.h"

class Node{
public:
    QString blockType;
    QString location;
    int x;
    int y;
    Node *next;
    Node *prev;
    QGraphicsRectWidget *sprite;
    Node();
    Node(QString type, QString location, int x, int y);
};

class objStructure
{
public:
    objStructure();
    void add(QString type, QString location,int x, int y);
    void remove(QString type, int x, int y);
    int getCount();
    Node* head;
    Node* tail;

private:
    int count;
};

#endif // OBJSTRUCTURE_H
