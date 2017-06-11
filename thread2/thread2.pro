TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

CONFIG += c++11
SOURCES += \
    #main_condition_variable.cpp \
    main.cpp
    #main_mutex.cpp \

include(deployment.pri)
qtcAddDeployment()

