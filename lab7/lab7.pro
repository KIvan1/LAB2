TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += editor.c \
    move_cursor.c \
    load.c \
    save.c \
    show.c \
    append_line.c \
    create_text.c \
    process_forward.c \
    remove_all.c \
    mplb.c \
    prev_paste.c


HEADERS += \
    common.h \
    _text.h \
    text.h


QMAKE_CFLAGS += -Wall -Wextra #-Werror

# gcov
QMAKE_CFLAGS += -fprofile-arcs -ftest-coverage
LIBS += -lgcov
