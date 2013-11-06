#ifndef PARSER_H
#define PARSER_H
#include <QtCore>
#include <QtWidgets>
#include <QtGui>

#include "objStructure.h"

class parser
{
public:
    parser();
    ~parser();
    int readFile(QWidget *parent, objStructure *objs, QString fileName);
    void createFile(QString name);
private:
    objStructure* sprites;
    QFile *file;
    int processFile(QFile *file );
};

#endif // PARSER_H
