TEMPLATE = app
QT_CONFIG -= no-pkg-config
CONFIG += console c++11
CONFIG += link_pkgconfig
PKGCONFIG +=opencv
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp

