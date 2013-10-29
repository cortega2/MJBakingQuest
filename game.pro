QT += widgets
QT += core gui

SOURCES = \
    objects.cpp \
    engine.cpp \
    game.cpp \
    gamemainwindow.cpp

HEADERS += \
    objects.h \
    engine.h \
    gamemainwindow.h

TARGET = bakingquest

INSTALLS += target

FORMS += \
    gamemainwindow.ui
