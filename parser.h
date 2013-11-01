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
    int readFile(objStructure *objs, QString fileName, bool readSpecific);
    void createFile(QString name);
private:
    objStructure* sprites;
};

#endif // PARSER_H
