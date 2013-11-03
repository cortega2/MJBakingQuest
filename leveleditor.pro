QT += widgets
QT += core gui

SOURCES = \
    objects.cpp \
    engine.cpp \
    leveleditor.cpp \
    objStructure.cpp \
    parser.cpp \
    editormainwindow.cpp

HEADERS += \
    objects.h \
    engine.h \
    objStructure.h \
    parser.h \
    editormainwindow.h

TARGET = leveleditor

INSTALLS += target

FORMS += \
    editormainwindow.ui

OTHER_FILES +=

RESOURCES += \
    resources.qrc

