QT += widgets
QT += core gui

SOURCES = main.cpp \
    mainwindow.cpp \
    objects.cpp \
    engine.cpp

HEADERS += mainwindow.h \
    objects.h \
    engine.h

TARGET = leveleditor

INSTALLS += target

FORMS += \
    mainwindow.ui

OTHER_FILES +=

RESOURCES += \
    defaults.qrc

