#include "cameratreewidgetitem.h"

CameraTreeWidgetItem::CameraTreeWidgetItem(CameraPropertiesPair *cameraPropertiesPair)
{
    this->cameraPropertiesPair = cameraPropertiesPair;
    this->setText(0, "Camera");
}

CameraPropertiesPair *CameraTreeWidgetItem::getCameraPropertiesPair() const
{
    return cameraPropertiesPair;
}
