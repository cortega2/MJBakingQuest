QT += widgets
QT += core gui

SOURCES = \
    objects.cpp \
    engine.cpp \
    leveleditor.cpp \
    editormainwindow.cpp

HEADERS += \
    objects.h \
    engine.h \
    editormainwindow.h

TARGET = leveleditor

INSTALLS += target

FORMS += \
    editormainwindow.ui

OTHER_FILES +=

RESOURCES += \
    resources.qrc

