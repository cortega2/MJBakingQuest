QT += widgets
QT += core gui
QT += multimedia


SOURCES = \
    objects.cpp \
    engine.cpp \
    objStructure.cpp \
    parser.cpp \
    editormainwindow.cpp \
    edit_main.cpp \
    gamewindow.cpp \
    graphicsvieweditor.cpp

HEADERS += \
    objects.h \
    engine.h \
    objStructure.h \
    parser.h \
    editormainwindow.h \
    gamewindow.h \
    graphicsvieweditor.h \
    definitions.h

TARGET = MixMaster

FORMS += \
    editormainwindow.ui \
	
	RC_FILE = bakingquest.rc
