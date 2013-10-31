#ifndef OBJSTRUCTURE_H
#define OBJSTRUCTURE_H
#include <QtCore>

class Node{
public:
    QString blockType;
    int x;
    int y;
    Node *next;
    Node *prev;
    //add field for object, either that or a QGraphicsRectWidget
    Node();
    Node(QString type, int x, int y);
};

class objStructure
{
public:
    objStructure();
    void add(QString type, int x, int y);
    void remove(QString type, int x, int y);
    int getCount();
private:
    Node* head;
    Node* tail;
    int count;
};

#endif // OBJSTRUCTURE_H
