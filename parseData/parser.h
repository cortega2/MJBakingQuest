#ifndef PARSER_H
#define PARSER_H
#define BLOCK 0
#define BACKGROUND 1
#define PROTAG 2
#define ANTAG 3

class Node{
public:
    int blockType;
    int x;
    int y;
    Node *next = 0;
    Node *prev = 0;
    //add field for object, either that or a QGraphicsRectWidget
    Node();
    Node(int type, int x, int y);

};

class doublyLL{
public:
    doublyLL();
    void add(int type, int x, int y);
    void remove(int type, int x, int y);
private:
    Node* head;
    Node* tail;
    int count;

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
    doublyLL Block;
    doublyLL Background;
    doublyLL Protag;
    doublyLL Antag;
};

#endif // PARSER_H
