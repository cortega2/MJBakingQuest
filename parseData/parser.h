#ifndef PARSER_H
#define PARSER_H
class Node{
public:
    int blockType;
    int x;
    int y;
    Node *next = 0;
    Node *prev = 0;
    //add field for object, either that or a QGraphicsRectWidget
};

class doublyLL{
public:
    doublyLL();
    void add();
    void remove();


};

class parser
{
public: 
    parser();
    int readFile();
    void add(int type, int x, int y);
    bool remove(int type, int x, int y);
    void createFile();

private:
    Node *Block;
    Node *Background;
    Node *Protag;
    Node *Antag;
};

#endif // PARSER_H
