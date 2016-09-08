#-------------------------------------------------
#
# Project created by QtCreator 2015-12-18T23:45:27
#
#-------------------------------------------------

QT       += core gui opengl
QT       += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RoboWalk
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    urdfparser.cpp \
    model/joint.cpp \
    model/origin.cpp \
    model/parent.cpp \
    model/child.cpp \
    model/axis.cpp \
    model/calibration.cpp \
    model/dynamics.cpp \
    model/limit.cpp \
    model/mimic.cpp \
    model/safetycontroller.cpp \
    model/link.cpp \
    model/visual.cpp \
    model/collision.cpp \
    model/inertial.cpp \
    model/mass.cpp \
    model/inertia.cpp \
    model/box.cpp \
    model/cylinder.cpp \
    model/sphere.cpp \
    model/mesh.cpp \
    model/material.cpp \
    model/color.cpp \
    model/texture.cpp \
    model/geometry.cpp \
    model/sensor.cpp \
    model/camera.cpp \
    model/image.cpp \
    model/ray.cpp \
    model/horizontalray.cpp \
    model/verticalray.cpp \
    model/transmission.cpp \
    model/transmissiontype.cpp \
    model/transmissionjoint.cpp \
    model/hardwareinterface.cpp \
    model/transimissionactuator.cpp \
    model/mechanicalreduction.cpp \
    model/actuator.cpp \
    model/modelstate.cpp \
    model/jointstate.cpp \
    simulator/myglwidget.cpp \
    model/robotmodel.cpp \
    simulator/drawbox.cpp \
    simulator/drawcylinder.cpp \
    simulator/drawsphere.cpp \
    simulator/cuboid.cpp \
    simulator/world.cpp \
    model/abstractobject.cpp \
    simulator/myobject.cpp \
    simulator/objectode.cpp \
    simulator/robotdemo.cpp \
    ann/ann.cpp \
    ann/neuron.cpp \
    simulator/myannwidget.cpp \
    ann/connection.cpp \
    simulator/anndemo.cpp \
    ann/neatann.cpp \
    ann/experiment.cpp

HEADERS  += mainwindow.h \
    urdfparser.h \
    model/joint.h \
    model/origin.h \
    model/parent.h \
    model/child.h \
    model/axis.h \
    model/calibration.h \
    model/dynamics.h \
    model/limit.h \
    model/mimic.h \
    model/safetycontroller.h \
    model/link.h \
    model/visual.h \
    model/collision.h \
    model/inertial.h \
    model/mass.h \
    model/inertia.h \
    model/box.h \
    model/cylinder.h \
    model/sphere.h \
    model/mesh.h \
    model/material.h \
    model/color.h \
    model/texture.h \
    model/geometry.h \
    model/sensor.h \
    model/camera.h \
    model/image.h \
    model/ray.h \
    model/horizontalray.h \
    model/verticalray.h \
    model/transmission.h \
    model/transmissiontype.h \
    model/transmissionjoint.h \
    model/hardwareinterface.h \
    model/transimissionactuator.h \
    model/mechanicalreduction.h \
    model/actuator.h \
    model/modelstate.h \
    model/jointstate.h \
    simulator/myglwidget.h \
    model/robotmodel.h \
    simulator/drawbox.h \
    simulator/drawcylinder.h \
    simulator/drawsphere.h \
    simulator/cuboid.h \
    simulator/world.h \
    model/abstractobject.h \
    simulator/myobject.h \
    simulator/objectode.h \
    simulator/robotdemo.h \
    ann/ann.h \
    ann/neuron.h \
    simulator/myannwidget.h \
    ann/connection.h \
    simulator/timer.h \
    simulator/anndemo.h \
    ann/neatann.h \
    ann/experiment.h




FORMS    += mainwindow.ui

LIBS     += -lglut -lGL -lGLU -L/usr/local/lib/ode/ -lode

QMAKE_CXXFLAGS += -std=c++11 -dDOUBLE


unix:!macx: LIBS += -L$$PWD/../../ -lNeat

INCLUDEPATH += $$PWD/../../
DEPENDPATH += $$PWD/../../

unix:!macx: PRE_TARGETDEPS += $$PWD/../../libNeat.a
