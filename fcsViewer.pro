#-------------------------------------------------
#
# Project created by QtCreator 2013-02-27T10:31:46
#
#-------------------------------------------------

QT       += core gui
TARGET = fcsViewer




RESOURCES +=  icons/icons.qrc

SOURCES +=     main.cpp \
    mainwindow.cpp



include(core/core.pri)
include(widgets/widgets.pri)
include(widgets/plots/plots.pri)
include(widgets/property/property.pri)

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui
