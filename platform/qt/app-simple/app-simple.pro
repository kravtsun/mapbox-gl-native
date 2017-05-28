TEMPLATE = app
CONFIG += console c++11
#CONFIG -= app_bundle
CONFIG += qt
QT += gui core

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET = QtWidgets

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += main.cpp \
    mapwindow.cpp

HEADERS += \
    ../include/QMapbox \
    ../include/QMapboxGL \
    ../include/QQuickMapboxGL \
    ../include/QQuickMapboxGLMapParameter \
    ../include/qmapbox.hpp \
    ../include/qmapboxgl.hpp \
    mapwindow.h

unix:!macx: LIBS += -L$$PWD/../../../build/qt-linux-x86_64/Debug/ -lmbgl-core -lqmapboxgl

INCLUDEPATH += $$PWD/../../../build/qt-linux-x86_64/Debug/platform/qt/include
DEPENDPATH += $$PWD/../../../build/qt-linux-x86_64/Debug/platform/qt/include

unix:!macx: PRE_TARGETDEPS += $$PWD/../../../build/qt-linux-x86_64/Debug/libmbgl-core.a
