QT += widgets
QT += core gui
QT += multimedia

TEMPLATE = app

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
    graphicsvieweditor.h \
    definitions.h

TARGET = baking_game

FORMS += \
    editormainwindow.ui \
    start.ui \
    gamewindow.ui
	
RC_FILE = bakingquest.rc
