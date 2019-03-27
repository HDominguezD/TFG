#ifndef CAMERATREEWIDGETITEM_H
#define CAMERATREEWIDGETITEM_H

#include "QTreeWidgetItem"
#include "Pairs/camerapropertiespair.h"

class CameraTreeWidgetItem : public QTreeWidgetItem
{
public:
    CameraTreeWidgetItem(CameraPropertiesPair *cameraPropertiesPair, QString name);
    CameraPropertiesPair *getCameraPropertiesPair() const;

private:
    CameraPropertiesPair *cameraPropertiesPair;
};

#endif // CAMERATREEWIDGETITEM_H
