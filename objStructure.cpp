#include "objStructure.h"

Node::Node(QString type, QString location, int x, int y){
    blockType = type;
    this->location = location;
    this->x = x;
    this->y = y;
}

objStructure::objStructure(){
    count = 0;
    head = 0;
    tail = 0;
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

int objStructure::getCount(){
    return count;
}
