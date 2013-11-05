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
    gamewindow.cpp

HEADERS += \
    objects.h \
    engine.h \
    objStructure.h \
    parser.h \
    editormainwindow.h \
    start.h \
    gamewindow.h

TARGET = bakingquest

FORMS += \
    editormainwindow.ui \
    start.ui \
    gamewindow.ui
