
SOURCES +=  bt/bt_lexer.cpp \
            bt/bt_parser.cpp \
            bt/btvm/btvm.cpp \
            bt/btvm/vm/vm.cpp \
            bt/btvm/vm/vm_functions.cpp \
            bt/btvm/vm/vmvalue.cpp \
            bt/btvm/vm/ast.cpp \
            bt/btvm/btvm_types.cpp \
    $$PWD/bt/btvm/btvmio.cpp

HEADERS +=  bt/bt_parser.h \
            bt/bt_lexer.h \
            bt/btvm/btvm.h \
            bt/btvm/vm/vmvalue.h \
            bt/btvm/vm/vm.h \
            bt/btvm/vm/vm_functions.h \
            bt/btvm/format/btentry.h \
            bt/btvm/vm/ast.h \
            bt/btvm/btvm_types.h \
    $$PWD/bt/btvm/btvmio.h

