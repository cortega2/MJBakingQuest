QT += widgets
QT += core gui

SOURCES = \
    objects.cpp \
    engine.cpp \
    objStructure.cpp \
    parser.cpp \
    editormainwindow.cpp \
    main.cpp \
    start.cpp \
    gamewindow.cpp \
    graphicsvieweditor.cpp

HEADERS += \
    objects.h \
    engine.h \
    objStructure.h \
    parser.h \
    editormainwindow.h \
    start.h \
    gamewindow.h \
    graphicsvieweditor.h

TARGET = bakingquest

FORMS += \
    editormainwindow.ui \
    start.ui \
    gamewindow.ui
