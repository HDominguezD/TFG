#include "camerabutton.h"

CameraButton::CameraButton(CameraPropertiesPair *cameraPropertiesPair, QWidget *parent)
{
    this->cameraPropertiesPair = cameraPropertiesPair;
    this->setParent(parent);
    connect(this, SIGNAL(clicked(bool)), this, SLOT(buttonClicked(bool)));
}

void CameraButton::buttonClicked(bool clicked)
{
    emit cameraButtonClicked(cameraPropertiesPair);
}
