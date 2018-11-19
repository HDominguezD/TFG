#-------------------------------------------------
#
# Project created by QtCreator 2018-11-13T18:25:32
#
#-------------------------------------------------
unix:!mac:  APPLICATIONPREFIX = $$(PWD)/../..
unix:!mac: EXECUTABLEPATH = $$APPLICATIONPREFIX/ApplicationPackage
unix:!mac: LIBRARIESPATH  = $$APPLICATIONPREFIX/ApplicationPackage

DEPENDPATH  *= $$PWD/applicationlib
INCLUDEPATH *= $$PWD/applicationlib
DESTDIR = ../../ApplicationPackage

TARGET = applicationlib
TEMPLATE = lib
CONFIG += dynamiclib
unix:CONFIG += plugin
# configures rpath
mac:QMAKE_LFLAGS += -install_name @executable_path/lib"$$LIBNAME".dylib
# import / export directive in win32
win32:DEFINES *= DYNAMIC_$$upper($$LIBNAME)

DEFINES += APPLICATIONLIB_LIBRARY

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
    renderingwindow.cpp \
    core.cpp \
    objectclasses/objobject.cpp \
    objectclasses/tifobject.cpp \
    objectclasses/tifvolumeobject.cpp \
    pluginmanager/pluginmanager.cpp \
    objectclasses/tifstackobject.cpp

HEADERS += \
    renderingwindow.h \
    core.h \
    objectclasses/objobject.h \
    objectclasses/tifobject.h \
    objectclasses/objobject.h \
    objectclasses/tifobject.h \
    objectclasses/tifvolumeobject.h \
    plugins/plugin.h \
    objectclasses/abstractclasses/object.h \
    pluginmanager/pluginmanager.h \
    objectclasses/tifstackobject.h

FORMS += \
    renderingwindow.ui

unix {
    target.path = /usr/lib
    INSTALLS += target
}

LIBS += -L/usr/local/lib/vtk/
INCLUDEPATH += /usr/local/include/vtk-8.1

unix: LIBS += -lQVTKWidgetPlugin
unix: LIBS += -lvtkalglib-8.1
unix: LIBS += -lvtkalglib-8.1
unix: LIBS += -lvtkChartsCore-8.1
unix: LIBS += -lvtkChartsCore-8.1
unix: LIBS += -lvtkCommonColor-8.1
unix: LIBS += -lvtkCommonColor-8.1
unix: LIBS += -lvtkCommonComputationalGeometry-8.1
unix: LIBS += -lvtkCommonComputationalGeometry-8.1
unix: LIBS += -lvtkCommonCore-8.1
unix: LIBS += -lvtkCommonCore-8.1
unix: LIBS += -lvtkCommonDataModel-8.1
unix: LIBS += -lvtkCommonDataModel-8.1
unix: LIBS += -lvtkCommonExecutionModel-8.1
unix: LIBS += -lvtkCommonExecutionModel-8.1
unix: LIBS += -lvtkCommonMath-8.1
unix: LIBS += -lvtkCommonMath-8.1
unix: LIBS += -lvtkCommonMisc-8.1
unix: LIBS += -lvtkCommonMisc-8.1
unix: LIBS += -lvtkCommonSystem-8.1
unix: LIBS += -lvtkCommonSystem-8.1
unix: LIBS += -lvtkCommonTransforms-8.1
unix: LIBS += -lvtkCommonTransforms-8.1
unix: LIBS += -lvtkDICOMParser-8.1
unix: LIBS += -lvtkDICOMParser-8.1
unix: LIBS += -lvtkDomainsChemistry-8.1
unix: LIBS += -lvtkDomainsChemistry-8.1
unix: LIBS += -lvtkDomainsChemistryOpenGL2-8.1
unix: LIBS += -lvtkDomainsChemistryOpenGL2-8.1
unix: LIBS += -lvtkexoIIc-8.1
unix: LIBS += -lvtkexoIIc-8.1
unix: LIBS += -lvtkexpat-8.1
unix: LIBS += -lvtkexpat-8.1
unix: LIBS += -lvtkFiltersAMR-8.1
unix: LIBS += -lvtkFiltersAMR-8.1
unix: LIBS += -lvtkFiltersCore-8.1
unix: LIBS += -lvtkFiltersCore-8.1
unix: LIBS += -lvtkFiltersExtraction-8.1
unix: LIBS += -lvtkFiltersExtraction-8.1
unix: LIBS += -lvtkFiltersFlowPaths-8.1
unix: LIBS += -lvtkFiltersFlowPaths-8.1
unix: LIBS += -lvtkFiltersGeneral-8.1
unix: LIBS += -lvtkFiltersGeneral-8.1
unix: LIBS += -lvtkFiltersGeneric-8.1
unix: LIBS += -lvtkFiltersGeneric-8.1
unix: LIBS += -lvtkFiltersGeometry-8.1
unix: LIBS += -lvtkFiltersGeometry-8.1
unix: LIBS += -lvtkFiltersHybrid-8.1
unix: LIBS += -lvtkFiltersHybrid-8.1
unix: LIBS += -lvtkFiltersHyperTree-8.1
unix: LIBS += -lvtkFiltersHyperTree-8.1
unix: LIBS += -lvtkFiltersImaging-8.1
unix: LIBS += -lvtkFiltersImaging-8.1
unix: LIBS += -lvtkFiltersModeling-8.1
unix: LIBS += -lvtkFiltersModeling-8.1
unix: LIBS += -lvtkFiltersParallel-8.1
unix: LIBS += -lvtkFiltersParallel-8.1
unix: LIBS += -lvtkFiltersParallelImaging-8.1
unix: LIBS += -lvtkFiltersParallelImaging-8.1
unix: LIBS += -lvtkFiltersPoints-8.1
unix: LIBS += -lvtkFiltersPoints-8.1
unix: LIBS += -lvtkFiltersProgrammable-8.1
unix: LIBS += -lvtkFiltersProgrammable-8.1
unix: LIBS += -lvtkFiltersSelection-8.1
unix: LIBS += -lvtkFiltersSelection-8.1
unix: LIBS += -lvtkFiltersSMP-8.1
unix: LIBS += -lvtkFiltersSMP-8.1
unix: LIBS += -lvtkFiltersSources-8.1
unix: LIBS += -lvtkFiltersSources-8.1
unix: LIBS += -lvtkFiltersStatistics-8.1
unix: LIBS += -lvtkFiltersStatistics-8.1
unix: LIBS += -lvtkFiltersTexture-8.1
unix: LIBS += -lvtkFiltersTexture-8.1
unix: LIBS += -lvtkFiltersTopology-8.1
unix: LIBS += -lvtkFiltersTopology-8.1
unix: LIBS += -lvtkFiltersVerdict-8.1
unix: LIBS += -lvtkFiltersVerdict-8.1
unix: LIBS += -lvtkfreetype-8.1
unix: LIBS += -lvtkfreetype-8.1
unix: LIBS += -lvtkGeovisCore-8.1
unix: LIBS += -lvtkGeovisCore-8.1
unix: LIBS += -lvtkgl2ps-8.1
unix: LIBS += -lvtkgl2ps-8.1
unix: LIBS += -lvtkglew-8.1
unix: LIBS += -lvtkglew-8.1
unix: LIBS += -lvtkGUISupportQt-8.1
unix: LIBS += -lvtkGUISupportQt-8.1
unix: LIBS += -lvtkGUISupportQtOpenGL-8.1
unix: LIBS += -lvtkGUISupportQtOpenGL-8.1
unix: LIBS += -lvtkGUISupportQtSQL-8.1
unix: LIBS += -lvtkGUISupportQtSQL-8.1
unix: LIBS += -lvtkhdf5-8.1
unix: LIBS += -lvtkhdf5-8.1
unix: LIBS += -lvtkhdf5_hl-8.1
unix: LIBS += -lvtkhdf5_hl-8.1
unix: LIBS += -lvtkImagingColor-8.1
unix: LIBS += -lvtkImagingColor-8.1
unix: LIBS += -lvtkImagingCore-8.1
unix: LIBS += -lvtkImagingCore-8.1
unix: LIBS += -lvtkImagingFourier-8.1
unix: LIBS += -lvtkImagingFourier-8.1
unix: LIBS += -lvtkImagingGeneral-8.1
unix: LIBS += -lvtkImagingGeneral-8.1
unix: LIBS += -lvtkImagingHybrid-8.1
unix: LIBS += -lvtkImagingHybrid-8.1
unix: LIBS += -lvtkImagingMath-8.1
unix: LIBS += -lvtkImagingMath-8.1
unix: LIBS += -lvtkImagingMorphological-8.1
unix: LIBS += -lvtkImagingMorphological-8.1
unix: LIBS += -lvtkImagingSources-8.1
unix: LIBS += -lvtkImagingSources-8.1
unix: LIBS += -lvtkImagingStatistics-8.1
unix: LIBS += -lvtkImagingStatistics-8.1
unix: LIBS += -lvtkImagingStencil-8.1
unix: LIBS += -lvtkImagingStencil-8.1
unix: LIBS += -lvtkInfovisCore-8.1
unix: LIBS += -lvtkInfovisCore-8.1
unix: LIBS += -lvtkInfovisLayout-8.1
unix: LIBS += -lvtkInfovisLayout-8.1
unix: LIBS += -lvtkInteractionImage-8.1
unix: LIBS += -lvtkInteractionImage-8.1
unix: LIBS += -lvtkInteractionStyle-8.1
unix: LIBS += -lvtkInteractionStyle-8.1
unix: LIBS += -lvtkInteractionWidgets-8.1
unix: LIBS += -lvtkInteractionWidgets-8.1
unix: LIBS += -lvtkIOAMR-8.1
unix: LIBS += -lvtkIOAMR-8.1
unix: LIBS += -lvtkIOCore-8.1
unix: LIBS += -lvtkIOCore-8.1
unix: LIBS += -lvtkIOEnSight-8.1
unix: LIBS += -lvtkIOEnSight-8.1
unix: LIBS += -lvtkIOExodus-8.1
unix: LIBS += -lvtkIOExodus-8.1
unix: LIBS += -lvtkIOExport-8.1
unix: LIBS += -lvtkIOExport-8.1
unix: LIBS += -lvtkIOExportOpenGL2-8.1
unix: LIBS += -lvtkIOExportOpenGL2-8.1
unix: LIBS += -lvtkIOGeometry-8.1
unix: LIBS += -lvtkIOGeometry-8.1
unix: LIBS += -lvtkIOImage-8.1
unix: LIBS += -lvtkIOImage-8.1
unix: LIBS += -lvtkIOImport-8.1
unix: LIBS += -lvtkIOImport-8.1
unix: LIBS += -lvtkIOInfovis-8.1
unix: LIBS += -lvtkIOInfovis-8.1
unix: LIBS += -lvtkIOLegacy-8.1
unix: LIBS += -lvtkIOLegacy-8.1
unix: LIBS += -lvtkIOLSDyna-8.1
unix: LIBS += -lvtkIOLSDyna-8.1
unix: LIBS += -lvtkIOMINC-8.1
unix: LIBS += -lvtkIOMINC-8.1
unix: LIBS += -lvtkIOMovie-8.1
unix: LIBS += -lvtkIOMovie-8.1
unix: LIBS += -lvtkIONetCDF-8.1
unix: LIBS += -lvtkIONetCDF-8.1
unix: LIBS += -lvtkIOParallel-8.1
unix: LIBS += -lvtkIOParallel-8.1
unix: LIBS += -lvtkIOParallelXML-8.1
unix: LIBS += -lvtkIOParallelXML-8.1
unix: LIBS += -lvtkIOPLY-8.1
unix: LIBS += -lvtkIOPLY-8.1
unix: LIBS += -lvtkIOSQL-8.1
unix: LIBS += -lvtkIOSQL-8.1
unix: LIBS += -lvtkIOTecplotTable-8.1
unix: LIBS += -lvtkIOTecplotTable-8.1
unix: LIBS += -lvtkIOVideo-8.1
unix: LIBS += -lvtkIOVideo-8.1
unix: LIBS += -lvtkIOXML-8.1
unix: LIBS += -lvtkIOXML-8.1
unix: LIBS += -lvtkIOXMLParser-8.1
unix: LIBS += -lvtkIOXMLParser-8.1
unix: LIBS += -lvtkjpeg-8.1
unix: LIBS += -lvtkjpeg-8.1
unix: LIBS += -lvtkjsoncpp-8.1
unix: LIBS += -lvtkjsoncpp-8.1
unix: LIBS += -lvtklibharu-8.1
unix: LIBS += -lvtklibharu-8.1
unix: LIBS += -lvtklibxml2-8.1
unix: LIBS += -lvtklibxml2-8.1
unix: LIBS += -lvtklz4-8.1
unix: LIBS += -lvtklz4-8.1
unix: LIBS += -lvtkmetaio-8.1
unix: LIBS += -lvtkmetaio-8.1
unix: LIBS += -lvtkNetCDF-8.1
unix: LIBS += -lvtkNetCDF-8.1
unix: LIBS += -lvtknetcdfcpp-8.1
unix: LIBS += -lvtknetcdfcpp-8.1
unix: LIBS += -lvtkoggtheora-8.1
unix: LIBS += -lvtkoggtheora-8.1
unix: LIBS += -lvtkParallelCore-8.1
unix: LIBS += -lvtkParallelCore-8.1
unix: LIBS += -lvtkpng-8.1
unix: LIBS += -lvtkpng-8.1
unix: LIBS += -lvtkproj4-8.1
unix: LIBS += -lvtkproj4-8.1
unix: LIBS += -lvtkRenderingAnnotation-8.1
unix: LIBS += -lvtkRenderingAnnotation-8.1
unix: LIBS += -lvtkRenderingContext2D-8.1
unix: LIBS += -lvtkRenderingContext2D-8.1
unix: LIBS += -lvtkRenderingContextOpenGL2-8.1
unix: LIBS += -lvtkRenderingContextOpenGL2-8.1
unix: LIBS += -lvtkRenderingCore-8.1
unix: LIBS += -lvtkRenderingCore-8.1
unix: LIBS += -lvtkRenderingFreeType-8.1
unix: LIBS += -lvtkRenderingFreeType-8.1
unix: LIBS += -lvtkRenderingGL2PSOpenGL2-8.1
unix: LIBS += -lvtkRenderingGL2PSOpenGL2-8.1
unix: LIBS += -lvtkRenderingImage-8.1
unix: LIBS += -lvtkRenderingImage-8.1
unix: LIBS += -lvtkRenderingLabel-8.1
unix: LIBS += -lvtkRenderingLabel-8.1
unix: LIBS += -lvtkRenderingLOD-8.1
unix: LIBS += -lvtkRenderingLOD-8.1
unix: LIBS += -lvtkRenderingOpenGL2-8.1
unix: LIBS += -lvtkRenderingOpenGL2-8.1
unix: LIBS += -lvtkRenderingQt-8.1
unix: LIBS += -lvtkRenderingQt-8.1
unix: LIBS += -lvtkRenderingVolume-8.1
unix: LIBS += -lvtkRenderingVolume-8.1
unix: LIBS += -lvtkRenderingVolumeOpenGL2-8.1
unix: LIBS += -lvtkRenderingVolumeOpenGL2-8.1
unix: LIBS += -lvtksqlite-8.1
unix: LIBS += -lvtksqlite-8.1
unix: LIBS += -lvtksys-8.1
unix: LIBS += -lvtksys-8.1
unix: LIBS += -lvtktiff-8.1
unix: LIBS += -lvtktiff-8.1
unix: LIBS += -lvtkverdict-8.1
unix: LIBS += -lvtkverdict-8.1
unix: LIBS += -lvtkViewsContext2D-8.1
unix: LIBS += -lvtkViewsContext2D-8.1
unix: LIBS += -lvtkViewsCore-8.1
unix: LIBS += -lvtkViewsCore-8.1
unix: LIBS += -lvtkViewsInfovis-8.1
unix: LIBS += -lvtkViewsInfovis-8.1
unix: LIBS += -lvtkViewsQt-8.1
unix: LIBS += -lvtkViewsQt-8.1
unix: LIBS += -lvtkzlib-8.1
unix: LIBS += -lvtkzlib-8.1

 QT += widgets
