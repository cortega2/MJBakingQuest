QT += widgets
QT += core gui

SOURCES = main.cpp \
    mainwindow.cpp \
    objects.cpp

HEADERS += mainwindow.h \
    objects.h

INSTALLS += target

FORMS += \
    mainwindow.ui

OTHER_FILES += \
    level1

RESOURCES += \
    resources.qrc

