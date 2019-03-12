#include "camerapropertiespair.h"

CameraPropertiesPair::CameraPropertiesPair(vtkCamera *camera, QDockWidget *propertiesDock)
{
    this->camera = camera;
    this->propertiesDock = propertiesDock;
}

vtkCamera *CameraPropertiesPair::getCamera() const
{
    return camera;
}

void CameraPropertiesPair::setCamera(vtkCamera *value)
{
    camera = value;
}

QDockWidget *CameraPropertiesPair::getPropertiesDock() const
{
    return propertiesDock;
}

void CameraPropertiesPair::setPropertiesDock(QDockWidget *value)
{
    propertiesDock = value;
}
