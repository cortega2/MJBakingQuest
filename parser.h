#ifndef PARSER_H
#define PARSER_H
#include <QtCore>
#include <QtWidgets>
#include <QtGui>

#include "objStructure.h"
#include "definitions.h"

class parser
{
public:
    parser();
    ~parser();
    int readFile(QWidget *parent, objStructure *good, objStructure *enemies,
                 objStructure *blocks, objStructure *other, QString fileName);
    void createFile(QString name, objStructure *goodGuys, objStructure *enemies, objStructure *blocks, objStructure *other);
private:
    objStructure* sprites;
    QFile *file;
    int processFile(QFile *file );
};

#endif // PARSER_H
