#ifndef OBJSTRUCTURE_H
#define OBJSTRUCTURE_H
#include <QtCore>
#include "objects.h"
#include "definitions.h"

class Node{
public:
    QGraphicsRectWidget *sprite;
    QString blockType;
    QString location;
    QString goodObj;
    int x;
    int y;
    int movement;
    bool hasObj;
    Node *next;
    Node *prev;
    Node();
    ~Node();
    Node(QString type, QString location, int x, int y);
};

class objStructure
{
public:
    objStructure();
    //~objStructure();
    void add(QString type, QString location,int x, int y);
    void add(QString type, QString location, int x, int y, QString goodObj);
    void remove(QString type, int x, int y);
    void remove(Node *gone);
    void removeAll();
    int getCount();
    Node *head;
    Node *tail;

private:
    int count;
};

#endif // OBJSTRUCTURE_H
