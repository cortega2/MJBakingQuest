#include "parser.h"
#include <iostream>

Node::Node(int type, int x, int y){
    blockType = type;
    this->x = x;
    this->y = y;
}

doublyLL::doublyLL(){
    count = 0;
    head = 0;
    tail = 0;
}
void doublyLL::add(int type, int x, int y){
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

parser::parser(){
}
void parser::add(int type, int x, int y){
    if(type == BLOCK){
        Block.add(type, x, y);
    }
    else if(type == BACKGROUND){
        Background.add(type, x, y);
    }
    else if(type == PROTAG){
        Protag.add(type, x, y);
    }
    else if(type == ANTAG){
        Antag.add(type, x, y);
    }
    else{
        std::cout<<"Unsupported type"<<std::endl;
    }
}
