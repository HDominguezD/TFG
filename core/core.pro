#-------------------------------------------------
#
# Project created by QtCreator 2018-11-12T19:17:25
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = subdirs
CONFIG += ordered

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++11

FORMS += \
    renderingwindow.ui

SUBDIRS += \
    applicationlib \
    application \
    surfaceplugin \
    volumeplugin \
    imageplugin
