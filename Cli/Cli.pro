QT -= core gui
SOURCES += cli.cpp
INCLUDEPATH += . ../CorsairLinkLib
LIBS += -L.. -lCorsairLink -lhidapi-hidraw

DESTDIR = ..
TARGET = OpenCorsairLinkCli
