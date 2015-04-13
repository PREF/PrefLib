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
    disassembler/disassemblercontext.cpp \
    disassembler/disassemblerdefinition.cpp \
    disassembler/disassemblerlisting.cpp \
    disassembler/blocks/block.cpp \
    disassembler/blocks/segment.cpp \
    core/lua/luacontainer.cpp \
    core/capstone/luacapstone.cpp \
    core/capstone/metadata.cpp \
    core/capstone/arch/arm.cpp \
    core/capstone/arch/arm64.cpp \
    core/capstone/arch/mips.cpp \
    core/capstone/arch/ppc.cpp \
    core/capstone/arch/sparc.cpp \
    core/capstone/arch/sysz.cpp \
    core/capstone/arch/x86.cpp \
    core/capstone/arch/xcore.cpp \
    core/capstone/tables/arm_const.cpp \
    core/capstone/tables/arm64_const.cpp \
    core/capstone/tables/capstone_const.cpp \
    core/capstone/tables/mips_const.cpp \
    core/capstone/tables/ppc_const.cpp \
    core/capstone/tables/sparc_const.cpp \
    core/capstone/tables/sysz_const.cpp \
    core/capstone/tables/x86_const.cpp \
    core/capstone/tables/xcore_const.cpp \
    disassembler/blocks/function.cpp \
    disassembler/blocks/instruction.cpp \
    types/buffer.cpp \
    disassembler/blocks/capstoneinstruction.cpp \
    disassembler/disassemblerengine.cpp \
    disassembler/listingprinter.cpp \
    disassembler/database/disassemblerdatabase.cpp \
    core/containers/cachedmap.cpp

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
    disassembler/disassemblercontext.h \
    disassembler/disassemblerdefinition.h \
    disassembler/disassemblerlisting.h \
    disassembler/blocks/block.h \
    disassembler/blocks/segment.h \
    core/lua/luacontainer.h \
    core/capstone/luacapstone.h \
    core/capstone/luacapstonemacros.h \
    core/capstone/metadata.h \
    core/capstone/reflection.h \
    core/capstone/arch/arm.h \
    core/capstone/arch/arm64.h \
    core/capstone/arch/mips.h \
    core/capstone/arch/ppc.h \
    core/capstone/arch/sparc.h \
    core/capstone/arch/sysz.h \
    core/capstone/arch/x86.h \
    core/capstone/arch/xcore.h \
    core/capstone/tables/arm_const.h \
    core/capstone/tables/arm64_const.h \
    core/capstone/tables/capstone_const.h \
    core/capstone/tables/mips_const.h \
    core/capstone/tables/ppc_const.h \
    core/capstone/tables/sparc_const.h \
    core/capstone/tables/sysz_const.h \
    core/capstone/tables/x86_const.h \
    core/capstone/tables/xcore_const.h \
    disassembler/blocks/function.h \
    disassembler/blocks/instruction.h \
    types/buffer.h \
    disassembler/blocks/capstoneinstruction.h \
    disassembler/disassemblerengine.h \
    disassembler/listingprinter.h \
    disassembler/database/disassemblerdatabase.h \
    core/containers/cachedmap.h

INCLUDEPATH += $$PWD/include/capstone \
               $$PWD/include/lua

