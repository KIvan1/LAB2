TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += editor.c \
    move_cursor.c \
    load.c \
    save.c \
    show.c \
    text/append_line.c \
    text/create_text.c \
    text/process_forward.c \
    text/remove_all.c \
    mplb.c \
    prev_paste.c


HEADERS += \
    common.h \
    text/_text.h \
    text/text.h


QMAKE_CFLAGS += -Wall -Wextra #-Werror

# gcov
QMAKE_CFLAGS += -fprofile-arcs -ftest-coverage
LIBS += -lgcov

DISTFILES += \
    input/input.txt
