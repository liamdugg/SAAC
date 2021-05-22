#-------------------------------------------------
#
# Project created by QtCreator 2020-08-21T16:02:02
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia
QT       += widgets printsupport
CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Editor
TEMPLATE = app


SOURCES += main.cpp\
        sac.cpp \
    ../SAACEditor.cpp \
    ../SAACWidget.cpp \
    ventana.cpp \
    seleccion.cpp \
    cambio.cpp \
    printscreen.cpp

HEADERS  += sac.h \
    ../SAACEditor.h \
    ../SAACWidget.h \
    ventana.h \
    seleccion.h \
    cambio.h \
    printscreen.h

FORMS    += sac.ui \
    ventana.ui \
    seleccion.ui \
    cambio.ui \
    printscren.ui

RESOURCES += \
    resources.qrc

