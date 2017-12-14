#-------------------------------------------------
#
# Project created by QtCreator 2017-11-07T17:44:26
#
#-------------------------------------------------

QT       += core gui


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QT       += opengl

TARGET = myPhotoShop
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

win32:LIBS += -lOpengl32 \
                -lglu32 \
                -lglut

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    myglwidget.cpp \
    line.cpp \
    circle.cpp \
    oval.cpp \
    rect.cpp \
    movegraph.cpp \
    zoomgraph.cpp \
    Constant.cpp \
    rotategraph.cpp \
    mypolygon.cpp \
    fillgraph.cpp

HEADERS += \
        mainwindow.h \
    myglwidget.h \
    Graph2D.h \
    Constant.h \
    line.h \
    circle.h \
    oval.h \
    rect.h \
    movegraph.h \
    zoomgraph.h \
    rotategraph.h \
    mypolygon.h \
    fillgraph.h

FORMS += \
        mainwindow.ui

RESOURCES += \
    toolbaricon.qrc
