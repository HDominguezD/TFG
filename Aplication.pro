#-------------------------------------------------
#
# Project created by QtCreator 2018-08-06T17:45:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Aplication
TEMPLATE = app

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
        main.cpp \
    mainmenu.cpp \
    renderingwindow.cpp \
    core.cpp \
    loaddata.cpp \
    objreader.cpp \
    ObjectClasses/object3d.cpp \
    ObjectClasses/objobject.cpp

HEADERS += \
    mainmenu.h \
    renderingwindow.h \
    core.h \
    loaddata.h \
    objreader.h \
    ObjectClasses/object3d.h \
    ObjectClasses/objobject.h

FORMS += \
    mainmenu.ui \
    renderingwindow.ui \
    loaddata.ui

   INCLUDEPATH += /usr/local/include/vtk-8.1
DEPENDPATH += /usr/local/include/vtk-8.1
LIBS += -L/usr/local/lib/vtk/
    unix: LIBS += -lvtkCommonCore-8.1
    unix: LIBS += -lvtkCommonExecutionModel-8.1
    unix: LIBS += -lvtksys-8.1
    unix: LIBS += -lQVTKWidgetPlugin
    unix: LIBS += -lvtkChartsCore-8.1
    unix: LIBS += -lvtkViewsQt-8.1
    unix: LIBS += -lvtkInteractionWidgets-8.1
    unix: LIBS += -lvtkInteractionStyle-8.1
    unix: LIBS += -lvtkInfovisCore-8.1
    unix: LIBS += -lvtkRenderingCore-8.1
    unix: LIBS += -lvtkRenderingOpenGL2-8.1
    unix: LIBS += -lvtkImagingCore-8.1
    unix: LIBS += -lvtkIOCore-8.1 -lvtkIOGeometry-8.1 -lvtkIOImage-8.1 -lvtkIOPLY-8.1
    unix: LIBS += -lvtkFiltersCore-8.1 \
      -lvtkFiltersExtraction-8.1 -lvtkFiltersGeneral-8.1 -lvtkFiltersGeometry-8.1 -lvtkFiltersHybrid-8.1 \
      -lvtkFiltersSources-8.1 -lvtkFiltersStatistics-8.1
    unix: LIBS += -lvtklibxml2-8.1
    unix: LIBS += -lvtkDICOMParser-8.1
    unix: LIBS += -lvtkpng-8.1
    unix: LIBS += -lvtktiff-8.1
    unix: LIBS += -lvtkzlib-8.1
    unix: LIBS += -lvtkjpeg-8.1
    unix: LIBS += -lvtkalglib-8.1
    unix: LIBS += -lvtkexpat-8.1
    unix: LIBS += -lvtkverdict-8.1
    unix: LIBS += -lvtkmetaio-8.1
    unix: LIBS += -lvtkNetCDF-8.1
    unix: LIBS += -lvtksqlite-8.1
    unix: LIBS += -lvtkexoIIc-8.1
    unix: LIBS += -lvtkfreetype-8.1
    unix: LIBS += -lvtkFiltersSources-8.1
    unix: LIBS += -lvtkGUISupportQt-8.1
    unix: LIBS += -lvtkCommonDataModel-8.1

DISTFILES +=
