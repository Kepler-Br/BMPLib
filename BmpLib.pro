QT       -= core gui

TARGET = libbmp
TEMPLATE = lib
CONFIG += staticlib
CONFIG += console c++11

SOURCES += \
    image.cpp \
    bmploader.cpp \
    bmpwriter.cpp

HEADERS += \
    image.h \
    bmploader.h \
    bmpwriter.h
