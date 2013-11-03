QT += widgets
QT += core gui

SOURCES = \
    objects.cpp \
    engine.cpp \
    objStructure.cpp \
    parser.cpp \
    editormainwindow.cpp \
    main.cpp \
    start.cpp

HEADERS += \
    objects.h \
    engine.h \
    objStructure.h \
    parser.h \
    editormainwindow.h \
    start.h

TARGET = bakingquest

FORMS += \
    editormainwindow.ui \
    start.ui
