#include "cameratreewidgetitem.h"

CameraTreeWidgetItem::CameraTreeWidgetItem(CameraPropertiesPair *cameraPropertiesPair, QString name)
{
    this->cameraPropertiesPair = cameraPropertiesPair;
    this->setText(0, name);
}

CameraPropertiesPair *CameraTreeWidgetItem::getCameraPropertiesPair() const
{
    return cameraPropertiesPair;
}
