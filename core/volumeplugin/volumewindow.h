#ifndef VOLUMEWINDOW_H
#define VOLUMEWINDOW_H

#include <QDockWidget>
#include <QVector>
#include "core.h"
#include "QSlider"
#include "vtkCamera.h"
#include "QVector"
#include "volumewindow.h"
#include "renderingwindow.h"
#include "Pairs/objectpropertiespair.h"
#include "Pairs/camerapropertiespair.h"
#include "objectclasses/tifvolumeobject.h"
#include "objectclasses/objobject.h"

class VolumeWindow : public QDockWidget
{
    Q_OBJECT
public:
    explicit VolumeWindow(QWidget *parent = nullptr);
    bool initialize();

    void setCore(Core *value);

    RenderingWindow *getRenderingWindow() const;
    void setRenderingWindow(RenderingWindow *value);

private:
    void initializeSlider(QSlider *slider);
    ObjectPropertiesPair *createVolumePropertiesPanel(TifVolumeObject *vol);
    ObjectPropertiesPair *createObjectPropertiesPanel(ObjObject *obj);
    CameraPropertiesPair *createCameraPropertiesPanel(vtkCamera *camera);
    void initializeHierarchyPanel();
    void addObjectToHierarchyPanel(ObjectPropertiesPair * objectPropertiesPair);

    QVTKWidget *vtkWidget;
    CameraPropertiesPair *cameraPropertiesPair;
    Core *core;
    RenderingWindow *renderingWindow;
    QVector<ObjectPropertiesPair *>* objectPropertiesPairs;
    QDockWidget *hierarchy;
    QMainWindow *window;

signals:

public slots:

private slots:
    void changeObjScale(int value);
    void openObjFile();
    void openTifVolume();
    void captureImage();
    void changeFocusedToCamera(CameraPropertiesPair *cameraPropertiesPair);
    void changeFocusedToObject(ObjectPropertiesPair *objectPropertiesPair);
    void updateWidget();
};

#endif // VOLUMEWINDOW_H
