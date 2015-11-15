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
    core/lua/luareference.cpp \
    types/datavalue.cpp \
    format/elements/structure.cpp \
    core/lua/luax.cpp \
    format/elements/field.cpp \
    core/lua/luatable.cpp \
    io/databuffer.cpp \
    core/lua/luastate.cpp \
    format/elements/fieldarray.cpp \
    format/elements/bitfield.cpp \
    exporter/exportercontext.cpp \
    exporter/exporterdefinition.cpp \
    chart/histogramchart.cpp \
    chart/abstractchart.cpp \
    support/math.cpp \
    support/byteelaborator.cpp \
    chart/entropychart.cpp \
    support/bytecolors.cpp \
    map/abstractmap.cpp \
    map/dotplotmap.cpp \
    map/pixelviewmap.cpp \
    map/binarymap.cpp \
    types/buffer.cpp \
    core/containers/cachedmap.cpp \
    format/categorycontext.cpp \
    core/lua/luathread.cpp \
    support/algorithm.cpp \
    support/pointer.cpp \

HEADERS += \
    prefcontext.h \
    format/formattree.h \
    format/formatcontext.h \
    format/elements/formatelement.h \
    format/elements/fieldelement.h \
    types/datatype.h \
    types/endianness.h \
    format/formatdefinition.h \
    core/lua/luareference.h \
    types/datavalue.h \
    format/elements/structure.h \
    core/lua/luax.h \
    format/elements/field.h \
    core/lua/luatable.h \
    preflib.h \
    io/databuffer.h \
    core/lua/luastate.h \
    format/elements/fieldarray.h \
    format/elements/bitfield.h \
    exporter/exportercontext.h \
    exporter/exporterdefinition.h \
    chart/histogramchart.h \
    chart/abstractchart.h \
    support/math.h \
    support/byteelaborator.h \
    chart/entropychart.h \
    support/bytecolors.h \
    map/abstractmap.h \
    map/dotplotmap.h \
    map/pixelviewmap.h \
    map/binarymap.h \
    types/buffer.h \
    core/containers/cachedmap.h \
    format/categorycontext.h \
    core/lua/luathread.h \
    support/algorithm.h \
    support/pointer.h \

INCLUDEPATH += $$PWD/include/lua

