include(gtest_dependency.pri)

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG += thread
CONFIG -= qt

QMAKE_CXXFLAGS += -Wall -Wextra
QMAKE_CFLAGS += -Wall -Wextra

# gcov
QMAKE_CXXFLAGS += -fprofile-arcs -ftest-coverage
QMAKE_CFLAGS += -fprofile-arcs -ftest-coverage
LIBS += -lgcov

DEFINES += INPUTDIR=\\\"$$PWD/input/\\\"

HEADERS += tests.h \
        ../lab7/common.h \
        ../lab7/text/text.h \
        ../lab7/text/_text.h

SOURCES += main.cpp \
    ../lab7/move_cursor.c \
    ../lab7/show.c \
    ../lab7/load.c \
    ../lab7/mplb.c \
    ../lab7/prev_paste.c \
    ../lab7/save.c \
    ../lab7/text/process_forward.c \
    ../lab7/text/append_line.c \
    ../lab7/text/create_text.c \
    ../lab7/text/remove_all.c


INCLUDEPATH += ../lab7

#DISTFILES += \
#    input/input.txt
