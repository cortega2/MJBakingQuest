#include "objStructure.h"
#include <iostream>

Node::Node(QString type, QString location, int x, int y){
    blockType = type;
    this->location = location;
    this->x = x;
    this->y = y;
    this->sprite = NULL;
}

Node::~Node(){
    if(this->sprite != NULL)
        delete this->sprite;
}

objStructure::objStructure(){
    count = 0;
    head = 0;
    tail = 0;
}
void objStructure::add(QString type, QString location, int x, int y, QString goodObj){
    if(count == 0){
        head = new Node(type, location, x, y);
        head->prev = 0;
        head->next = 0;
        tail = head;
        head->goodObj = goodObj;
        count ++;
    }
    else if(count == 1){
        tail = new Node(type, location, x, y);
        tail->goodObj = goodObj;
        head->next = tail;
        tail->prev = head;
        tail->next = 0;
        count++;
    }
    else{
        Node* tmp = new Node(type, location, x, y);
        tmp->goodObj = goodObj;
        tmp->prev = tail;
        tail->next = tmp;
        tail = tmp;
        tail->next = 0;
        count++;
    }
}

void objStructure::add(QString type, QString location, int x, int y){
    if(count == 0){
        head = new Node(type, location, x, y);
        head->prev = 0;
        head->next = 0;
        tail = head;
        count ++;
    }
    else if(count == 1){
        tail = new Node(type, location, x, y);
        head->next = tail;
        tail->prev = head;
        tail->next = 0;
        count++;
    }
    else{
        Node* tmp = new Node(type, location, x, y);
        tmp->prev = tail;
        tail->next = tmp;
        tail = tmp;
        tail->next = 0;
        count++;
    }
}

void objStructure::remove(Node *gone){
    //one node in list
    if(head == gone && tail == gone){
        head = NULL;
        tail = NULL;
        gone->~Node();
    }

    //gone is head
    else if( head == gone){
        head = head->next;
        head->prev = NULL;
        gone->~Node();
    }
    //gone is tail
    else if(tail == gone){
        tail = tail->prev;
        tail->next = NULL;
        gone->~Node();
    }
    //gone is other node
    else{
        gone->prev->next = gone->next;
        gone->next->prev = gone->prev;
        gone->~Node();
    }
    count--;
}

void objStructure::removeAll(){
    while(count>0)
        remove(head);
}

int objStructure::getCount(){
    return count;
}
