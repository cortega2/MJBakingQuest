#include "objStructure.h"

Node::Node(QString type, int x, int y){
    blockType = type;
    this->x = x;
    this->y = y;
}

objStructure::objStructure(){
    count = 0;
    head = 0;
    tail = 0;
}
void objStructure::add(QString type, int x, int y){
    if(count == 0){
        head = new Node(type, x, y);
        tail = head;
        count ++;
    }
    else if(count == 1){
        tail = new Node(type, x, y);
        head->next = tail;
        tail->prev = head;
        count++;
    }
    else{
        Node* tmp = new Node(type, x, y);
        tmp->next = tail;
        tail->next = tmp;
        tail = tmp;
        count++;
    }
}

int objStructure::getCount(){
    return count;
}
