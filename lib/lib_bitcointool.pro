#-------------------------------------------------
#
# Project created by QtCreator 2017-12-04T14:26:35
#
#-------------------------------------------------

QT       -= gui core

TARGET = bitcointool
TEMPLATE = lib

CONFIG += c++14 staticlib

DEFINES += LIB_BITCOINTOOL

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        lib_bitcointool.cc \
    ../applog.c \
    ../base58.c \
    ../combination.c \
    ../hash.c \
    ../keys.c \
    ../main.c \
    ../prefix.c \
    ../result.c \
    ../sha256.c \
    ../utility.c

HEADERS += \
        lib_bitcointool.h \
    ../applog.h \
    ../base58.h \
    ../combination.h \
    ../hash.h \
    ../keys.h \
    ../prefix.h \
    ../result.h \
    ../sha256.h \
    ../utility.h
