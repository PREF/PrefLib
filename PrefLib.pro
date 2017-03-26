#-------------------------------------------------
#
# Project created by QtCreator 2015-03-28T14:19:33
#
#-------------------------------------------------

QT       -= core gui

TARGET = PrefLib
TEMPLATE = lib
CONFIG += staticlib c++11

include(BT.pri)

SOURCES += \
    io/databuffer.cpp \
    chart/histogramchart.cpp \
    chart/abstractchart.cpp \
    support/byteelaborator.cpp \
    chart/entropychart.cpp \
    support/bytecolors.cpp \
    map/abstractmap.cpp \
    map/dotplotmap.cpp \
    map/pixelviewmap.cpp \
    map/binarymap.cpp \
    support/algorithm.cpp

HEADERS += \
    preflib.h \
    io/databuffer.h \
    chart/histogramchart.h \
    chart/abstractchart.h \
    support/byteelaborator.h \
    chart/entropychart.h \
    support/bytecolors.h \
    map/abstractmap.h \
    map/dotplotmap.h \
    map/pixelviewmap.h \
    map/binarymap.h \
    support/algorithm.h \
    support/datainspector.h
