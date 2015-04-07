#-------------------------------------------------
#
# Project created by QtCreator 2015-03-28T14:19:33
#
#-------------------------------------------------

QT       -= core gui

TARGET = PrefLib
TEMPLATE = lib
CONFIG += staticlib c++11

SOURCES += \
    prefcontext.cpp \
    format/formattree.cpp \
    format/formatcontext.cpp \
    format/elements/formatelement.cpp \
    format/elements/fieldelement.cpp \
    types/datatype.cpp \
    types/endianness.cpp \
    format/formatdefinition.cpp \
    core/luareference.cpp \
    types/datavalue.cpp \
    format/elements/structure.cpp \
    core/luax.cpp \
    format/elements/field.cpp \
    core/luatable.cpp \
    io/databuffer.cpp \
    core/luastate.cpp \
    format/elements/fieldarray.cpp \
    format/elements/bitfield.cpp \
    exporter/exportercontext.cpp \
    exporter/exporterdefinition.cpp \
    chart/histogramchart.cpp \
    chart/abstractchart.cpp \
    support/math.cpp \
    support/byteelaborator.cpp

HEADERS += \
    prefcontext.h \
    format/formattree.h \
    format/formatcontext.h \
    format/elements/formatelement.h \
    format/elements/fieldelement.h \
    types/datatype.h \
    types/endianness.h \
    format/formatdefinition.h \
    core/luareference.h \
    types/datavalue.h \
    format/elements/structure.h \
    core/luax.h \
    format/elements/field.h \
    core/luatable.h \
    preflib.h \
    io/databuffer.h \
    core/luastate.h \
    format/elements/fieldarray.h \
    format/elements/bitfield.h \
    exporter/exportercontext.h \
    exporter/exporterdefinition.h \
    chart/histogramchart.h \
    chart/abstractchart.h \
    support/math.h \
    support/byteelaborator.h

INCLUDEPATH += $$PWD/include/capstone \
               $$PWD/include/lua

