#ifndef CAMERAPROPERTIESPAIR_H
#define CAMERAPROPERTIESPAIR_H

#include "vtkCamera.h";
#include "QDockWidget";


class CameraPropertiesPair
{
public:
    CameraPropertiesPair(vtkCamera *camera, QDockWidget *propertiesDock);

    vtkCamera *getCamera() const;
    void setCamera(vtkCamera *value);

    QDockWidget *getPropertiesDock() const;
    void setPropertiesDock(QDockWidget *value);

private:
    QDockWidget *propertiesDock;
    vtkCamera *camera;
};

#endif // CAMERAPROPERTIESPAIR_H
