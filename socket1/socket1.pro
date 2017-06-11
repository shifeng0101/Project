TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11

SOURCES += main.cpp

#LIBS += libws32.a
WIN32{
LIBS += -lWs2_32
}

unix:!macx {
LIBS += -pthread
}

include(deployment.pri)
qtcAddDeployment()

