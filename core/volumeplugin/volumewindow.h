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
#include "QTreeWidgetItem"
#include "TreeWidgetItems/objecttreewidgetitem.h"
#include "TreeWidgetItems/cameratreewidgetitem.h"
#include "Editors/objecteditor.h"
#include "graphicwindow.h"

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
//    void initializeSlider(QSlider *slider);
    ObjectPropertiesPair *createVolumePropertiesPanel(TifVolumeObject *vol);
    ObjectPropertiesPair *createObjectPropertiesPanel(ObjObject *obj);
    CameraPropertiesPair *createCameraPropertiesPanel(vtkCamera *camera);
    void initializeHierarchyPanel();
    void addObjectToHierarchyPanel(ObjectPropertiesPair * objectPropertiesPair);
    void changeFocusedToCamera(CameraPropertiesPair *cameraPropertiesPair);
    void changeFocusedToObject(ObjectPropertiesPair *objectPropertiesPair);
    void removeHierarchyObject(ObjectTreeWidgetItem *item, QTreeWidget* tree);

    GraphicWindow *vtkWidget;
    CameraPropertiesPair *cameraPropertiesPair;
    CameraTreeWidgetItem *cameraTreeWidget;
    Core *core;
    RenderingWindow *renderingWindow;
    QVector<ObjectTreeWidgetItem*>* objectTreeWidgets;
    QVector<ObjectPropertiesPair *>* objectPropertiesPairs;
    QDockWidget *hierarchy;
    QMainWindow *window;

signals:

private slots:
//    void changeObjScale(int value);
    void openObjFile();
    void openTifVolume();
    void captureImage();
    void treeWidgetItemClicked(QTreeWidgetItem*,int);
    void removeContextMenu(const QPoint &pos);
    void removeHierarchyObjects();
    void updateWidget();
    void changeName(ObjectEditor *editor, QString name);
    void createMesh(TifVolumeObject *vol);
    void createSegmentation(TifVolumeObject *vol);
    void openMesh();
};

#endif // VOLUMEWINDOW_H
