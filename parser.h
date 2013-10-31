#ifndef PARSER_H
#define PARSER_H
#include <QtCore>
#include <QtWidgets>
#include <QtGui>

class parser
{
public:
    parser();
    void readFile(QGraphicsScene *scene);
    void createFile(QString name);

};

#endif // PARSER_H
