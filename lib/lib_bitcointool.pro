#
# Project file for QT & qmake to build bitcoint-tool command-line app as static library
#

# display all warnings
WARNINGS += -Wall

# keep the generated files separated from the source files.
UI_DIR = uics
MOC_DIR = mocs
OBJECTS_DIR = objs

TEMPLATE = lib
QT -= qt
QT -= gui 
QT -= core
QT -= app_bundle

CONFIG += c++14 staticlib thread create_prl

TARGET = $$OUT_PWD/bitcointool
DEFINES += LIB_BITCOINTOOL

SOURCES += \
    lib_bitcointool.cc \
    $$PWD/../applog.c \
    $$PWD/../base58.c \
    $$PWD/../combination.c \
    $$PWD/../hash.c \
    $$PWD/../keys.c \
    $$PWD/../main.c \
    $$PWD/../prefix.c \
    $$PWD/../result.c \
    $$PWD/../sha256.c \
    $$PWD/../utility.c

HEADERS += \
    lib_bitcointool.h \
    $$PWD/../applog.h \
    $$PWD/../base58.h \
    $$PWD/../combination.h \
    $$PWD/../hash.h \
    $$PWD/../keys.h \
    $$PWD/../prefix.h \
    $$PWD/../result.h \
    $$PWD/../sha256.h \
    $$PWD/../utility.h

message($$OUT_PWD)