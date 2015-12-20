#-------------------------------------------------
#
# Project created by QtCreator 2015-12-18T23:45:27
#
#-------------------------------------------------

QT       += core gui
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
    model/abstractobject.cpp

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
    model/abstractobject.h

FORMS    += mainwindow.ui
