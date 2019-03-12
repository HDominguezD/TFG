#ifndef CAMERABUTTON_H
#define CAMERABUTTON_H
#include "QPushButton"
#include "Pairs/camerapropertiespair.h"

class CameraButton : public QPushButton
{
    Q_OBJECT
public:
    CameraButton(CameraPropertiesPair *cameraPropertiesPair, QWidget *parent = nullptr);

private:
    CameraPropertiesPair *cameraPropertiesPair;

signals:
    void cameraButtonClicked(CameraPropertiesPair *cameraPropertiesPair);

private slots:
    void buttonClicked(bool clicked);
};

#endif // CAMERABUTTON_H
